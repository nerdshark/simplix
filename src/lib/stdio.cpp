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

#include <lib/stdio.h>

int snprintf(char *__restrict__ str, size_t size,
             const char *__restrict__ format)
{
    int cnt = 0;

    while (*format != '\0') {
        if ((size_t)cnt < size)
            str[cnt] = *format;
        ++cnt;
        ++format;
    }

    str[cnt] = '\0';

    return cnt;
}
