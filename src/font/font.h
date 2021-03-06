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

namespace Font {

/*
 * Each glyph in the framebuffer is 8x16 pixels.
 * We store 1 glyph as 16 bytes, where each set bit indicates a pixel to draw.
 */
struct Glyph {
    uint8_t data[16];
    constexpr static size_t WIDTH = 8;
    constexpr static size_t HEIGHT = 16;
};

/*
 * Returns a const-reference to the glyph corresponding to the character c.
 * @c is expected to be >= 0.
 */
const Glyph &get_glyph(char c);

} // namespace Font end
