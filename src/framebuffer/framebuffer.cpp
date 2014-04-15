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
#include <misc.h>
#include <lib/assert.h>

// Framebuffer start address
static uint32_t *g_framebuffer;

// Size of the framebuffer in bytes
static size_t g_framebuffer_size;

// max visible horizontal pixels
static unsigned int g_max_width;
// max vertical pixels
static unsigned int g_max_height;
// actual amount of horizontal pixels
static unsigned int g_pixels_per_scan_line;

static unsigned int g_current_width;
static unsigned int g_current_height;

static uint32_t g_color_array[to_underlying_type(Framebuffer::Color::NAVY)+1] = { };

void Framebuffer::init(const EFI_GRAPHICS_OUTPUT_PROTOCOL &gop)
{
    g_framebuffer = (uint32_t *)gop.Mode->FrameBufferBase;
    g_framebuffer_size = gop.Mode->FrameBufferSize;
    g_max_width = gop.Mode->Info->HorizontalResolution;
    g_max_height = gop.Mode->Info->VerticalResolution;
    g_pixels_per_scan_line = gop.Mode->Info->PixelsPerScanLine;
    g_current_width = 0;
    g_current_height = 0;

    switch (gop.Mode->Info->PixelFormat) {
    case PixelRedGreenBlueReserved8BitPerColor:
        g_color_array[to_underlying_type(Framebuffer::Color::BLACK)] = 0x00000000;
        g_color_array[to_underlying_type(Framebuffer::Color::WHITE)] = 0x00ffffff;
        g_color_array[to_underlying_type(Framebuffer::Color::RED)] = 0x000000ff;
        g_color_array[to_underlying_type(Framebuffer::Color::LIME)] = 0x0000ff00;
        g_color_array[to_underlying_type(Framebuffer::Color::BLUE)] = 0x00ff0000;
        g_color_array[to_underlying_type(Framebuffer::Color::YELLOW)] = 0x0000ffff;
        g_color_array[to_underlying_type(Framebuffer::Color::CYAN)] = 0x00ffff00;
        g_color_array[to_underlying_type(Framebuffer::Color::MAGENTA)] = 0x00ff00ff;
        g_color_array[to_underlying_type(Framebuffer::Color::SILVER)] = 0x00c0c0c0;
        g_color_array[to_underlying_type(Framebuffer::Color::GRAY)] = 0x00808080;
        g_color_array[to_underlying_type(Framebuffer::Color::MAROON)] = 0x00000080;
        g_color_array[to_underlying_type(Framebuffer::Color::OLIVE)] = 0x00008080;
        g_color_array[to_underlying_type(Framebuffer::Color::GREEN)] = 0x00008000;
        g_color_array[to_underlying_type(Framebuffer::Color::PURPLE)] = 0x00800080;
        g_color_array[to_underlying_type(Framebuffer::Color::TEAL)] = 0x00808000;
        g_color_array[to_underlying_type(Framebuffer::Color::NAVY)] = 0x00800000;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        g_color_array[to_underlying_type(Framebuffer::Color::BLACK)] = 0x00000000;
        g_color_array[to_underlying_type(Framebuffer::Color::WHITE)] = 0x00ffffff;
        g_color_array[to_underlying_type(Framebuffer::Color::RED)] = 0x00ff0000;
        g_color_array[to_underlying_type(Framebuffer::Color::LIME)] = 0x0000ff00;
        g_color_array[to_underlying_type(Framebuffer::Color::BLUE)] = 0x000000ff;
        g_color_array[to_underlying_type(Framebuffer::Color::YELLOW)] = 0x00ffff00;
        g_color_array[to_underlying_type(Framebuffer::Color::CYAN)] = 0x0000ffff;
        g_color_array[to_underlying_type(Framebuffer::Color::MAGENTA)] = 0x00ff00ff;
        g_color_array[to_underlying_type(Framebuffer::Color::SILVER)] = 0x00c0c0c0;
        g_color_array[to_underlying_type(Framebuffer::Color::GRAY)] = 0x00808080;
        g_color_array[to_underlying_type(Framebuffer::Color::MAROON)] = 0x00800000;
        g_color_array[to_underlying_type(Framebuffer::Color::OLIVE)] = 0x00808000;
        g_color_array[to_underlying_type(Framebuffer::Color::GREEN)] = 0x00008000;
        g_color_array[to_underlying_type(Framebuffer::Color::PURPLE)] = 0x00800080;
        g_color_array[to_underlying_type(Framebuffer::Color::TEAL)] = 0x00008080;
        g_color_array[to_underlying_type(Framebuffer::Color::NAVY)] = 0x00000080;
        break;
    default:
        break;
    }
}

// Move every line until the current one up, make current row blank
static void scroll()
{
    const auto limit = g_current_height * g_pixels_per_scan_line;
    const auto font_line_size = Font::Glyph::HEIGHT * g_pixels_per_scan_line;

    for (unsigned int i = 0; i < limit; ++i)
        g_framebuffer[i] = g_framebuffer[i + font_line_size];

    for (unsigned int i = 0; i < font_line_size; ++i)
        g_framebuffer[limit + i] = 0;
}

static void newline()
{
    g_current_width = 0;

    if (g_current_height + Font::Glyph::HEIGHT > g_max_height - Font::Glyph::HEIGHT)
        scroll();
    else
        g_current_height += Font::Glyph::HEIGHT;
}

static void put_glyph(const Font::Glyph &glyph, Framebuffer::Color fg,
                      Framebuffer::Color bg)
{
    for (unsigned int i = 0; i < Font::Glyph::HEIGHT; ++i) {
        const auto height = g_current_height + i;

        for (unsigned int j = 0; j < Font::Glyph::WIDTH; ++j) {
            const auto width = g_current_width + j;
            const auto idx = height * g_pixels_per_scan_line + width;

            if (glyph.data[i] & (0x80 >> j))
                g_framebuffer[idx] = g_color_array[to_underlying_type(fg)];
            else
                g_framebuffer[idx] = g_color_array[to_underlying_type(bg)];
        }
    }
}

void Framebuffer::put_char(char c, Framebuffer::Color fg, Framebuffer::Color bg)
{
    if (c == '\n') {
        newline();
        return;
    }

    if (g_current_width + Font::Glyph::WIDTH > g_max_width)
        newline();

    put_glyph(Font::get_glyph(c), fg, bg);

    g_current_width += Font::Glyph::WIDTH;
}

void Framebuffer::put_string(const char *s, Framebuffer::Color fg, Framebuffer::Color bg)
{
    assert(s != nullptr);

    for (; *s != '\0'; ++s)
        Framebuffer::put_char(*s, fg, bg);
}

void Framebuffer::clear_screen()
{
    memset(g_framebuffer, 0, g_framebuffer_size);
    g_current_height = g_current_width = 0;
}
