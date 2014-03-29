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
