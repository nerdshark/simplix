/*
 * Copyright (c) 2014 Thorben Hasenpusch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <framebuffer/framebuffer.h>
#include <font/font.h>
#include <lib/string.h>
#include <misc.h>

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

static uint32_t color_array[to_underlying_type(Framebuffer::Color::NAVY)+1] = { };

void Framebuffer::init(const EFI_GRAPHICS_OUTPUT_PROTOCOL &gop)
{
    base_address = (uint32_t *)gop.Mode->FrameBufferBase;
    size = gop.Mode->FrameBufferSize;
    max_width = gop.Mode->Info->HorizontalResolution;
    max_height = gop.Mode->Info->VerticalResolution;
    pixels_per_scan_line = gop.Mode->Info->PixelsPerScanLine;
    current_width = 0;
    current_height = 0;

    switch (gop.Mode->Info->PixelFormat) {
    case PixelRedGreenBlueReserved8BitPerColor:
        color_array[to_underlying_type(Framebuffer::Color::BLACK)] = 0x00000000;
        color_array[to_underlying_type(Framebuffer::Color::WHITE)] = 0x00ffffff;
        color_array[to_underlying_type(Framebuffer::Color::RED)] = 0x000000ff;
        color_array[to_underlying_type(Framebuffer::Color::LIME)] = 0x0000ff00;
        color_array[to_underlying_type(Framebuffer::Color::BLUE)] = 0x00ff0000;
        color_array[to_underlying_type(Framebuffer::Color::YELLOW)] = 0x0000ffff;
        color_array[to_underlying_type(Framebuffer::Color::CYAN)] = 0x00ffff00;
        color_array[to_underlying_type(Framebuffer::Color::MAGENTA)] = 0x00ff00ff;
        color_array[to_underlying_type(Framebuffer::Color::SILVER)] = 0x00c0c0c0;
        color_array[to_underlying_type(Framebuffer::Color::GRAY)] = 0x00808080;
        color_array[to_underlying_type(Framebuffer::Color::MAROON)] = 0x00000080;
        color_array[to_underlying_type(Framebuffer::Color::OLIVE)] = 0x00008080;
        color_array[to_underlying_type(Framebuffer::Color::GREEN)] = 0x00008000;
        color_array[to_underlying_type(Framebuffer::Color::PURPLE)] = 0x00800080;
        color_array[to_underlying_type(Framebuffer::Color::TEAL)] = 0x00808000;
        color_array[to_underlying_type(Framebuffer::Color::NAVY)] = 0x00800000;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        color_array[to_underlying_type(Framebuffer::Color::BLACK)] = 0x00000000;
        color_array[to_underlying_type(Framebuffer::Color::WHITE)] = 0x00ffffff;
        color_array[to_underlying_type(Framebuffer::Color::RED)] = 0x00ff0000;
        color_array[to_underlying_type(Framebuffer::Color::LIME)] = 0x0000ff00;
        color_array[to_underlying_type(Framebuffer::Color::BLUE)] = 0x000000ff;
        color_array[to_underlying_type(Framebuffer::Color::YELLOW)] = 0x00ffff00;
        color_array[to_underlying_type(Framebuffer::Color::CYAN)] = 0x0000ffff;
        color_array[to_underlying_type(Framebuffer::Color::MAGENTA)] = 0x00ff00ff;
        color_array[to_underlying_type(Framebuffer::Color::SILVER)] = 0x00c0c0c0;
        color_array[to_underlying_type(Framebuffer::Color::GRAY)] = 0x00808080;
        color_array[to_underlying_type(Framebuffer::Color::MAROON)] = 0x00800000;
        color_array[to_underlying_type(Framebuffer::Color::OLIVE)] = 0x00808000;
        color_array[to_underlying_type(Framebuffer::Color::GREEN)] = 0x00008000;
        color_array[to_underlying_type(Framebuffer::Color::PURPLE)] = 0x00800080;
        color_array[to_underlying_type(Framebuffer::Color::TEAL)] = 0x00008080;
        color_array[to_underlying_type(Framebuffer::Color::NAVY)] = 0x00000080;
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

    if (current_height + Font::GLYPH_HEIGHT > max_height) {
        scroll();
        current_height = max_height-1;
    } else
        current_height += Font::GLYPH_HEIGHT;
}

static void put_glyph(const Font::Glyph &glyph, Framebuffer::Color fg,
                      Framebuffer::Color bg)
{
    for (unsigned int i = 0; i < Font::GLYPH_HEIGHT; ++i) {
        int height = current_height + i;

        for (unsigned int j = 0; j < Font::GLYPH_WIDTH; ++j) {
            int width = current_width + j;
            auto idx = height * pixels_per_scan_line + width;

            if (glyph.data[i] & (0x80 >> j))
                base_address[idx] = color_array[to_underlying_type(fg)];
            else
                base_address[idx] = color_array[to_underlying_type(bg)];
        }
    }
}

int Framebuffer::put_char(char c, Framebuffer::Color fg, Framebuffer::Color bg)
{
    if (c == '\n') {
        newline();
        return 0;
    }

    if (current_width + Font::GLYPH_WIDTH > max_width)
        newline();

    put_glyph(Font::get_glyph(c), fg, bg);

    current_width += Font::GLYPH_WIDTH;

    return 0;
}

int Framebuffer::put_string(const char *s, Framebuffer::Color fg, Framebuffer::Color bg)
{
    for (; *s != '\0'; ++s)
        if (Framebuffer::put_char(*s, fg, bg) == -1)
            return -1;

    return 0;
}

void Framebuffer::clear_screen()
{
    memset(base_address, 0, size);
    current_height = current_width = 0;
}
