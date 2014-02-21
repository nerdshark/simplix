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

#ifndef STDIO_H
#define STDIO_H

#include <lib/math.h>
#include <type_traits>

template<bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

int snprintf(char *str, size_t size, const char *format);

template<class T>
enable_if_t<std::is_integral<T>::value, int>
to_char(T x, bool uppercase)
{
    if (x >= 0 && x <= 9)
        return x + '0';

    if (x >= 10 && x <= 35)
        return x + (uppercase ? 'A' : 'a') - 10;

    return -1;
}

inline void *mem_reverse_inplace(void *s, size_t size)
{
    unsigned char *p = (unsigned char *)s;
    for (size_t i = size-1, j = 0; j < i; --i, ++j) {
        unsigned char c = p[i];
        p[i] = p[j];
        p[j] = c;
    }

    return s;
}

template <class T>
enable_if_t<std::is_integral<T>::value, int>
arg_to_string(char *str, size_t size, T arg)
{
    int cnt = 0;
    int base = 10;

    bool arg_negative = arg < 0;
    if (arg_negative) {
        if (cnt < size)
            str[cnt] = '-';
        ++cnt;
    }

    auto abs_arg = unsigned_abs(arg);

    do {
        if (cnt < size) {
            int character = to_char(abs_arg % base, true);
            if (character == -1)
                return -1;
            str[cnt] = character;
        }
        ++cnt;
        abs_arg /= base;
    } while (abs_arg != 0);

    if (arg_negative)
        mem_reverse_inplace(str + 1, cnt - 1); // skip the '-'
    else
        mem_reverse_inplace(str, cnt);

    return cnt;
}

template<class T, class ...U>
int snprintf(char *__restrict__ str, size_t size,
             const char *__restrict__ format, const T &arg, const U &...args)
{
    int cnt = 0;

    while (*format != '\0') {
        if (*format != '%') {
            if (cnt < size)
                str[cnt] = *format;
            ++cnt;
            ++format;
            continue;
        }

        int arg_cnt = arg_to_string(str + cnt, size - cnt, arg);
        if (arg_cnt == -1 || add_would_overflow(cnt, arg_cnt, INT_MAX))
            return -1;

        cnt += arg_cnt;
        ++format;

        int ret = snprintf(str + cnt, size - cnt, format, args...);
        if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
            return -1;

        return ret + cnt;
    }

    str[cnt] = '\0';

    return cnt;
}

#endif // STDIO_H
