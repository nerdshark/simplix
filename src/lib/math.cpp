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
