/*
 * Copyright © 2014 Thorben Hasenpusch <thorben.hasenpusch@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <framebuffer/framebuffer.h>
#include <font/font.h>
#include <lib/string.h>

namespace Framebuffer {

// Framebuffer start address
static uint32_t *base_address;

// Size of the framebuffer in bytes
static size_t size;

// max horizontal pixels
static unsigned int max_width;
// max vertical pixels
static unsigned int max_height;
// padding between pixels
static unsigned int pixels_per_scan_line;

static unsigned int current_width;
static unsigned int current_height;

// Our glyphs (defined in font/font.cpp) are all 9x16.
static constexpr unsigned int glyph_width = 8;
static constexpr unsigned int glyph_height = 16;

void init(const EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
    base_address = (uint32_t *)gop->Mode->FrameBufferBase;
    size = gop->Mode->FrameBufferSize;
    max_width = gop->Mode->Info->HorizontalResolution;
    max_height = gop->Mode->Info->VerticalResolution;
    pixels_per_scan_line = gop->Mode->Info->PixelsPerScanLine;
    current_width = 0;
    current_height = 0;
}

// Move every line except the first one up, make last row blank
static void scroll()
{
    for (unsigned int i = 0; i < max_height-1; ++i)
        memcpy(&base_address[i*max_width], &base_address[(i+1)*max_width], max_width);
    memset(&base_address[(max_height-1) * max_width], 0x00, max_width*4);
}

static void newline()
{
    current_width = 0;

    if (current_height + glyph_height > max_height) {
        scroll();
        current_height = max_height-1;
    } else
        current_height += glyph_height;
}

static void put_glyph(const Font::Glyph *glyph, Color fg, Color bg)
{
    for (unsigned int i = 0; i < glyph_height; ++i) {
        int height = current_height + i;

        for (unsigned int j = 0; j < glyph_width; ++j) {
            int width = current_width + j;

            if (glyph->data[i] & (0x80 >> j))
                base_address[height * max_width + width] = fg;
            else
                base_address[height * max_width + width] = bg;
        }
    }
}

int put_string(const char *s, Color fg, Color bg)
{
    for (; *s != '\0'; ++s) {
        if (*s == '\n') {
            newline();
            continue;
        }

        if (current_width + glyph_width > max_width)
            newline();

        const Font::Glyph *glyph = Font::get_glyph(*s);
        if (glyph == nullptr)
            return -1;

        put_glyph(glyph, fg, bg);

        current_width += glyph_width;
    }

    return 0;
}

int put_string(const char *s)
{
    return put_string(s, WHITE, BLACK);
}

}
