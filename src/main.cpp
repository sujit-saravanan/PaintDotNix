#include <iostream>
#include <glm/glm.hpp>
#include "text_renderer.h"

#define FONT_SIZE 36
#define MARGIN (FONT_SIZE * .5)

int main(int argc, char *argv[]) {
        // Step 1: Create a font
        PDN::UI::Text::Font roboto("assets/fonts/Roboto-Regular.ttf", 20);
        
        // Step 2: Create a buffer
        PDN::UI::Text::Buffer buffer("Hello");
        buffer += " World";
        
        // Step 3: Shape the buffer
        roboto.shape(buffer);

        // Step 4: Iterate over all the glyphs and draw
        glm::vec2 cursor{0, 0};
        for (auto&& [glyph_info, glyph_position] : buffer.glyphs()) {
                uint32_t glyph_id = glyph_info.codepoint;
                
                glm::vec2 advance{glyph_position.x_advance / 64.0, glyph_position.y_advance / 64.0};
                glm::vec2 offset{glyph_position.x_offset / 64.0, glyph_position.y_offset / 64.0};
                
                glm::vec2 position = cursor + offset;
                std::cout << static_cast<uint8_t>(glyph_id + 28) << ": " << position.x << ", " << position.y << "\n";
                
                cursor += advance;
        }
        
        return 0;
}