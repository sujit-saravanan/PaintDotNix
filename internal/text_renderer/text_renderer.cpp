#include <utility>
#include "text_renderer.h"


PDN::UI::Text::Buffer::Buffer(const char *text, int32_t text_length, uint32_t item_offset, int32_t item_length) noexcept {
        m_buf = hb_buffer_create();
        hb_buffer_add_utf8(m_buf, text, text_length, item_offset, item_length);
        hb_buffer_guess_segment_properties(m_buf);
}

PDN::UI::Text::Buffer::~Buffer() noexcept { // 1. Destructor
        hb_buffer_destroy(m_buf);
}

PDN::UI::Text::Buffer::Buffer(const PDN::UI::Text::Buffer &other) noexcept { // 2. Copy Constructor
        m_buf = other.m_buf;
}

PDN::UI::Text::Buffer::Buffer(PDN::UI::Text::Buffer &&other) noexcept { // 3. Move Constructor
        m_buf = std::exchange(other.m_buf, nullptr);
}

PDN::UI::Text::Buffer &PDN::UI::Text::Buffer::operator=(const PDN::UI::Text::Buffer &other) noexcept { // 4. Copy Assignment
        m_buf = other.m_buf;
        return *this;
}

PDN::UI::Text::Buffer &PDN::UI::Text::Buffer::operator=(PDN::UI::Text::Buffer &&other) noexcept { // 5. Move Assignment
        m_buf = std::exchange(other.m_buf, nullptr);
        return *this;
}

PDN::UI::Text::Buffer PDN::UI::Text::operator+(const PDN::UI::Text::Buffer &lhs, const PDN::UI::Text::Buffer &rhs) {
        Buffer new_buffer;
        new_buffer.appendBuffer(lhs);
        new_buffer.appendBuffer(rhs);
        return new_buffer;
}

PDN::UI::Text::Buffer PDN::UI::Text::operator+(const PDN::UI::Text::Buffer &lhs, const char *rhs) {
        Buffer new_buffer;
        new_buffer.appendBuffer(lhs);
        new_buffer.appendText(rhs);
        return new_buffer;
}

PDN::UI::Text::Buffer &PDN::UI::Text::Buffer::operator+=(const PDN::UI::Text::Buffer &rhs) {
        return this->appendBuffer(rhs);
}

PDN::UI::Text::Buffer &PDN::UI::Text::Buffer::operator+=(const char *rhs) {
        return this->appendText(rhs);
}




inline void PDN::UI::Text::Buffer::guessSegmentPropertiesIfEmpty() noexcept {
        if (isEmpty()) [[unlikely]] {
                hb_buffer_guess_segment_properties(m_buf);
        }
}

PDN::UI::Text::Buffer &PDN::UI::Text::Buffer::appendText(const char *text, int32_t text_length, uint32_t item_offset, int32_t item_length) noexcept {
        guessSegmentPropertiesIfEmpty();
        hb_buffer_add_utf8(m_buf, text, text_length, item_offset, item_length);
        return *this;
}

PDN::UI::Text::Buffer &PDN::UI::Text::Buffer::appendBuffer(const PDN::UI::Text::Buffer &buffer) noexcept {
        guessSegmentPropertiesIfEmpty();
        hb_buffer_append(m_buf, buffer.m_buf, 0, HB_FEATURE_GLOBAL_END);
        return *this;
}


size_t PDN::UI::Text::Buffer::length() const noexcept {
        return hb_buffer_get_length(m_buf);
}

bool PDN::UI::Text::Buffer::isEmpty() const noexcept {
        return length() == 0;
}

hb_buffer_t *PDN::UI::Text::Buffer::buffer() const noexcept {
        return m_buf;
}

glyphs_view PDN::UI::Text::Buffer::glyphs() noexcept {
        uint32_t glyph_count;
        hb_glyph_info_t *glyph_infos = hb_buffer_get_glyph_infos(m_buf, &glyph_count);
        hb_glyph_position_t *glyph_positions = hb_buffer_get_glyph_positions(m_buf, &glyph_count);
        return std::views::zip(std::ranges::subrange(glyph_infos, glyph_infos + glyph_count), std::ranges::subrange(glyph_positions, glyph_positions + glyph_count));
}




PDN::UI::Text::Font::Font(const char *font_filepath, int font_size, uint32_t blob_face_index) {
        hb_blob_t *blob = hb_blob_create_from_file(font_filepath);
        hb_face_t *face = hb_face_create(blob, blob_face_index);
        m_font = hb_font_create(face);
        hb_font_set_scale(m_font, font_size * 64, font_size * 64);
        
        hb_face_destroy(face);
        hb_blob_destroy(blob);
}

PDN::UI::Text::Font::~Font() noexcept {
        hb_font_destroy(m_font);
}

PDN::UI::Text::Font::Font(const PDN::UI::Text::Font &other) noexcept {
        m_font = other.m_font;
}

PDN::UI::Text::Font::Font(PDN::UI::Text::Font &&other) noexcept {
        m_font = std::exchange(other.m_font, nullptr);
}

PDN::UI::Text::Font &PDN::UI::Text::Font::operator=(const PDN::UI::Text::Font &other) noexcept {
        m_font = other.m_font;
        return *this;
}

PDN::UI::Text::Font &PDN::UI::Text::Font::operator=(PDN::UI::Text::Font &&other) noexcept {
        m_font = std::exchange(other.m_font, nullptr);
        return *this;
}

void PDN::UI::Text::Font::shape(const PDN::UI::Text::Buffer &buffer) noexcept {
        hb_shape(m_font, buffer.buffer(), nullptr, 0);
}
