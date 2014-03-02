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

// Framebuffer start address
static uint32_t *base_address;

// Size of the framebuffer in bytes
static size_t size;

// max visible horizontal pixels
static unsigned int max_width;
// max vertical pixels
static unsigned int max_height;
// actual amount of horizontal pixels
static unsigned int pixels_per_scan_line;

static unsigned int current_width;
static unsigned int current_height;

// Our glyphs (defined in font/font.cpp) are all 8x16.
#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 16

static uint32_t color_array[NAVY+1] = { };

void framebuffer_init(const EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
    base_address = (uint32_t *)gop->Mode->FrameBufferBase;
    size = gop->Mode->FrameBufferSize;
    max_width = gop->Mode->Info->HorizontalResolution;
    max_height = gop->Mode->Info->VerticalResolution;
    pixels_per_scan_line = gop->Mode->Info->PixelsPerScanLine;
    current_width = 0;
    current_height = 0;

    switch (gop->Mode->Info->PixelFormat) {
    case PixelRedGreenBlueReserved8BitPerColor:
        color_array[BLACK] = 0x00000000;
        color_array[WHITE] = 0x00ffffff;
        color_array[RED] = 0x000000ff;
        color_array[LIME] = 0x0000ff00;
        color_array[BLUE] = 0x00ff0000;
        color_array[YELLOW] = 0x0000ffff;
        color_array[CYAN] = 0x00ffff00;
        color_array[MAGENTA] = 0x00ff00ff;
        color_array[SILVER] = 0x00c0c0c0;
        color_array[GRAY] = 0x00808080;
        color_array[MAROON] = 0x00000080;
        color_array[OLIVE] = 0x00008080;
        color_array[GREEN] = 0x00008000;
        color_array[PURPLE] = 0x00800080;
        color_array[TEAL] = 0x00808000;
        color_array[NAVY] = 0x00800000;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        color_array[BLACK] = 0x00000000;
        color_array[WHITE] = 0x00ffffff;
        color_array[RED] = 0x00ff0000;
        color_array[LIME] = 0x0000ff00;
        color_array[BLUE] = 0x000000ff;
        color_array[YELLOW] = 0x00ffff00;
        color_array[CYAN] = 0x0000ffff;
        color_array[MAGENTA] = 0x00ff00ff;
        color_array[SILVER] = 0x00c0c0c0;
        color_array[GRAY] = 0x00808080;
        color_array[MAROON] = 0x00800000;
        color_array[OLIVE] = 0x00808000;
        color_array[GREEN] = 0x00008000;
        color_array[PURPLE] = 0x00800080;
        color_array[TEAL] = 0x00008080;
        color_array[NAVY] = 0x00000080;
        break;
    default:
        break;
    }
}

// Move every line except the first one up, make last row blank
static void scroll()
{
    for (unsigned int i = 0; i < max_height-1; ++i)
        memcpy(&base_address[i*pixels_per_scan_line],
                &base_address[(i+1)*pixels_per_scan_line], max_width*4);
    memset(&base_address[(max_height-1) * pixels_per_scan_line], 0x00,
            max_width*4*4);
}

static void newline()
{
    current_width = 0;

    if (current_height + GLYPH_HEIGHT > max_height) {
        scroll();
        current_height = max_height-1;
    } else
        current_height += GLYPH_HEIGHT;
}

static void put_glyph(const struct font_glyph *glyph, framebuffer_color_t fg,
                      framebuffer_color_t bg)
{
    for (unsigned int i = 0; i < GLYPH_HEIGHT; ++i) {
        int height = current_height + i;

        for (unsigned int j = 0; j < GLYPH_WIDTH; ++j) {
            int width = current_width + j;

            if (glyph->data[i] & (0x80 >> j))
                base_address[height * pixels_per_scan_line + width] = color_array[fg];
            else
                base_address[height * pixels_per_scan_line + width] = color_array[bg];
        }
    }
}

int framebuffer_put_string(const char *s, framebuffer_color_t fg,
                           framebuffer_color_t bg)
{
    for (; *s != '\0'; ++s) {
        if (*s == '\n') {
            newline();
            continue;
        }

        if (current_width + GLYPH_WIDTH > max_width)
            newline();

        const struct font_glyph *glyph = font_get_glyph(*s);
        if (glyph == NULL)
            return -1;

        put_glyph(glyph, fg, bg);

        current_width += GLYPH_WIDTH;
    }

    return 0;
}
