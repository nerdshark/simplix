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

#pragma once

#include <cstdint>
#include <cstddef>

namespace Font {

constexpr size_t GLYPH_WIDTH = 8;
constexpr size_t GLYPH_HEIGHT = 16;

/*
 * Each glyph in the framebuffer is 8x16 pixels.
 * We store 1 glyph as 16 bytes, where each set bit indicates a pixel to draw.
 */
struct Glyph {
    uint8_t data[16];
};

/*
 * Returns a const-reference to the glyph corresponding to the character c.
 * @c is expected to be >= 0.
 */
const Glyph &get_glyph(char c);

} // namespace Font end
