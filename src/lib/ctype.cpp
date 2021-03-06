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

#include <lib/ctype.h>

int isblank(int c)
{
    return c == ' ' || c == '\t';
}

int iscntrl(int c)
{
    return (c <= 31 && c >= 0) || c == 127;
}

int isdigit(int c)
{
    return c >= '0' && c <= '9';
}

int isgraph(int c)
{
    return isalnum(c) || ispunct(c);
}

int islower(int c)
{
    return c >= 'a' && c <= 'z';
}

int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

int isalpha(int c)
{
    return isupper(c) || islower(c);
}

int isalnum(int c)
{
    return isalpha(c) || isdigit(c);
}

int isprint(int c)
{
    return isgraph(c) || c  == ' ';
}

int isxdigit(int c)
{
    return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

int isspace(int c)
{
    return c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
        || c == ' ';
}

int ispunct(int c)
{
    return isprint(c) && !isspace(c) && !isalnum(c);
}

int toupper(char c)
{
    if (islower(c))
        return c - ('a' - 'A');
    return c;
}

int tolower(char c)
{
    if (isupper(c))
        return c + ('a' - 'A');
    return c;
}
