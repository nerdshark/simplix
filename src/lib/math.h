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

#include <climits>
#include <cstdint>
#include <lib/error.h>

int pow(int x, unsigned int y, Error::Code &err);

int abs(int i);
long labs(long i);
long long llabs(long long i);
intmax_t imaxabs(intmax_t i);

template<typename T, typename U>
constexpr bool multiply_would_overflow(T val1, U val2, uintmax_t max)
{
    return (val1 > 0 && val2 > 0 && val1 > max / val2)
        || (val1 <= 0 && val2 <= 0 && val1 != 0 && val2 < max / val1);
}

template<typename T, typename U>
constexpr bool multiply_would_underflow(T val1, U val2, intmax_t min)
{
    return (val1 > 0 && val2 <= 0 && val2 < min / val1)
        || (val1 <= 0 && val2 > 0 && val1 < min / val2);
}

template <typename T, typename U>
constexpr bool add_would_overflow(T val1, U val2, uintmax_t max)
{
    return val2 > 0 && val1 > max - val2;
}

template <typename T, typename U>
constexpr bool add_would_underflow(T val1, U val2, intmax_t min)
{
    return val2 < 0 && val1 < min - val2;
}
