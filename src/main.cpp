#include <iostream>
#include <harfbuzz/hb.h>
#include <glm/glm.hpp>
#include "text_renderer.h"

#define FONT_SIZE 36
#define MARGIN (FONT_SIZE * .5)

int main(int argc, char *argv[]) {
        // Step 1: Create a font
        PDN::UI::Text::Font roboto("assets/fonts/Roboto-Regular.ttf");
        
        // Step 2: Create a buffer
        PDN::UI::Text::Buffer buffer("Hello");
        buffer = buffer + " " + "World";
        
        // Step 3: Shape the buffer
        roboto.shape(buffer);
        
        // Step 4: Get glyph and position info
        auto glyph_infos = buffer.glyphInfos();
        auto glyph_positions = buffer.glyphPositions();
        
        // Step 5: Iterate over all the glyphs and draw
        glm::vec2 cursor{0, 0};
        for (int i = 0; i < glyph_infos.size(); i++) {
                uint32_t glyph_id = glyph_infos[i].codepoint;
                
                glm::vec2 advance{glyph_positions[i].x_advance / 64.0, glyph_positions[i].y_advance / 64.0};
                glm::vec2 offset{glyph_positions[i].x_offset / 64.0, glyph_positions[i].y_offset / 64.0};
                
                glm::vec2 position = cursor + offset;
                //draw_glyph(glyphid, position.x, position.y)
                std::cout << static_cast<uint8_t>(glyph_id + 28) << ": " << position.x << ", " << position.y << "\n";
                
                cursor += advance;
        }
        
        return 0;
}