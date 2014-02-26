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

// Assuming RGB for now
enum Color : uint32_t {
    BLACK = 0x00000000,
    WHITE = 0x00ffffff,
    RED = 0x000000ff,
    LIME = 0x0000ff00,
    BLUE = 0x00ff0000,
    YELLOW = 0x0000ffff,
    CYAN = 0x00ffff00,
    MAGENTA = 0x00ff00ff,
    SILVER = 0x00c0c0c0,
    GRAY = 0x00808080,
    MAROON = 0x00000080,
    OLIVE = 0x00008080,
    GREEN = 0x00008000,
    PURPLE = 0x00800080,
    TEAL = 0x00808000,
    NAVY = 0x00800000
};

// Call that the first time before doing anything with the framebuffer!
void init(const EFI_GRAPHICS_OUTPUT_PROTOCOL *gop);

int put_string(const char *s, Color fg, Color bg);
int put_string(const char *s);

}
