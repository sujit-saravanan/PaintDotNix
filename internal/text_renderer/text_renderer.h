#pragma once
#include <harfbuzz/hb.h>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <vector>
#include <ranges>

typedef std::ranges::zip_view<std::ranges::subrange<hb_glyph_info_t*>, std::ranges::subrange<hb_glyph_position_t*>> glyphs_view;

namespace PDN::UI::Text {
        class Buffer {
        public: // Public Constructors/Destructors/Overloads (Rule of 5)
                explicit Buffer(const char *text = "", int32_t text_length = -1, uint32_t item_offset = 0, int32_t item_length = -1) noexcept;
                ~Buffer() noexcept; // 1. Destructor
                Buffer(const Buffer &other) noexcept; // 2. Copy Constructor
                Buffer(Buffer &&other) noexcept; // 3. Move Constructor
                Buffer &operator=(const Buffer &other) noexcept; // 4. Copy Assignment
                Buffer &operator=(Buffer &&other) noexcept; // 5. Move Assignment
                Buffer &operator+=(const Buffer &rhs);
                Buffer &operator+=(const char *rhs);
        
        public: // Public Member Functions
                Buffer &appendText(const char *text, int32_t text_length = -1, uint32_t item_offset = 0, int32_t item_length = -1) noexcept;
                Buffer &appendBuffer(const Buffer &buffer) noexcept;
                
                [[nodiscard]] size_t length() const noexcept;
                [[nodiscard]] bool isEmpty() const noexcept;
                [[nodiscard]] hb_buffer_t *buffer() const noexcept;
                
                [[nodiscard]] glyphs_view glyphs() noexcept;
        
        private: // Private Member Functions
                inline void guessSegmentPropertiesIfEmpty() noexcept;
        
        private: // Private Member Variables
                hb_buffer_t *m_buf{nullptr};
        };
        
        
        Buffer operator+(const Buffer &lhs, const Buffer &rhs);
        Buffer operator+(const Buffer &lhs, const char *rhs);
        
        
        class Font {
        public: // Public Constructors/Destructors/Overloads (Rule of 5)
                explicit Font(const char *font_filepath, int font_size = 12, uint32_t blob_face_index = 0);
                ~Font() noexcept; // 1. Destructor
                Font(const Font &other) noexcept; // 2. Copy Constructor
                Font(Font &&other) noexcept; // 3. Move Constructor
                Font &operator=(const Font &other) noexcept; // 4. Copy Assignment
                Font &operator=(Font &&other) noexcept; // 5. Move Assignment
        
        public: // Public Member Functions
                void shape(const Buffer &buffer) noexcept;
        public: // Public Member Variables
        private: // Private Member Functions
        private: // Private Member Variables
                hb_font_t *m_font;
        };
}