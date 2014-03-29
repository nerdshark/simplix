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

#include <lib/math.h>

int pow(int x, unsigned int y, Error::Code &err)
{
    if (y == 0)
        return 1;

    int a = x;
    for (unsigned int i = 1; i < y; ++i) {
        if (multiply_would_overflow(a, x, INT_MAX)) {
            err= Error::Code::ERANGE;
            return INT_MAX;
        }
        if (multiply_would_underflow(a, x, INT_MIN)) {
            err = Error::Code::ERANGE;
            return INT_MIN;
        }

        a *= x;
    }

    return a;
}

int abs(int i)
{
    return i < 0 ? -i : i;
}

long labs(long i)
{
    return i < 0 ? -i : i;
}

long long llabs(long long i)
{
    return i < 0 ? -i : i;
}

intmax_t imaxabs(intmax_t i)
{
    return i < 0 ? -i : i;
}
