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
