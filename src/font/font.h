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

#include <stdint.h>

/*
 * Each glyph in the framebuffer is 8x16 pixels.
 * We store 1 glyph as 16 bytes, where each set bit indicates a pixel to draw.
 */
struct font_glyph {
    uint8_t data[16];
};

/*
 * Either returns a non-nullptr pointer to a read-only struct Glyph if c is
 * valid (>0), or nullptr otherwise.
 */
const struct font_glyph *font_get_glyph(char c);
