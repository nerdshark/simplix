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

#pragma once

#include <cstdint>
#include <cstddef>
#include <uefi/protocols/console/gop.h>

namespace Framebuffer {

// We support only the basic colors for now
enum class Color {
    BLACK,
    WHITE,
    RED,
    LIME,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    SILVER,
    GRAY,
    MAROON,
    OLIVE,
    GREEN,
    PURPLE,
    TEAL,
    NAVY
};

// Call that the first time before doing anything with the framebuffer!
void init(const EFI_GRAPHICS_OUTPUT_PROTOCOL &gop);

// Clears the screen (yes, really)
void clear_screen();

// Puts a character on screen
int put_char(char c, Color fg, Color bg);

// Puts a zero-terminated string on screen
int put_string(const char *s, Color fg, Color bg);

} // namespace Framebuffer end
