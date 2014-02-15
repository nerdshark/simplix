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

#include <climits>

#include "stdlib.h"
#include "ctype.h"
#include "math.h"
#include "string.h"

static int char_to_value(char c)
{
    if (isdigit(c))
        return c - '0';

    if (islower(c))
        return c - 'a' + 10;

    if (isupper(c))
        return c - 'A' + 10;

    return -1;
}

uintmax_t strtoumax(const char *nptr, char **endptr, int base, Error &err)
{
    if ((base <= 2 || base >= 36) && base != 0) {
        err.set_code(Error::EINVAL);
        return -1;
    }

    while (isspace(*nptr))
        ++nptr;

    bool negative = false;

    switch (*nptr) {
    case '+':
        ++nptr;
        break;
    case '-':
        negative = true;
        ++nptr;
        break;
    default:
        break;
    }

    if (base == 16 && *nptr == '0' && (*(nptr+1) == 'x' || *(nptr+1) == 'X'))
        nptr += 2;

    if (base == 0) {
        switch (*nptr) {
        case '0':
            if (*(nptr+1) == 'x' || *(nptr+1) == 'X') {
                base = 16;
                nptr += 2;
            } else {
                base = 8;
                ++nptr;
            }
            break;
        default:
            base = 10;
            break;
        }
    }

    uintmax_t value = 0;
    size_t len = strlen(nptr)-1;

    for (; *nptr != '\0'; ++nptr) {
        int digit = char_to_value(*nptr);
        if (digit == -1 || digit >= base)
            break;

        uintmax_t val = digit * pow(base, len--);
        // check for overflow
        if (val > 0 && value > UINTMAX_MAX-val) {
            err.set_code(Error::ERANGE);
            return UINTMAX_MAX;
        }

        value += val;
    }

    if (negative)
        value *= (-1);

    if (endptr != nullptr)
        *endptr = (char *)nptr;

    return value;
}

intmax_t strtoimax(const char *nptr, char **endptr, int base, Error &err)
{
    if ((base <= 2 || base >= 36) && base != 0) {
        err.set_code(Error::EINVAL);
        return -1;
    }

    while (isspace(*nptr))
        ++nptr;

    bool negative = false;

    switch (*nptr) {
    case '+':
        ++nptr;
        break;
    case '-':
        negative = true;
        ++nptr;
        break;
    default:
        break;
    }

    if (base == 16 && *nptr == '0' && (*(nptr+1) == 'x' || *(nptr+1) == 'X'))
        nptr += 2;

    if (base == 0) {
        switch (*nptr) {
        case '0':
            if (*(nptr+1) == 'x' || *(nptr+1) == 'X') {
                base = 16;
                nptr += 2;
            } else {
                base = 8;
                ++nptr;
            }
            break;
        default:
            base = 10;
            break;
        }
    }

    intmax_t value = 0;
    size_t len = strlen(nptr)-1;

    for (; *nptr != '\0'; ++nptr) {
        int digit = char_to_value(*nptr);
        if (digit == -1 || digit >= base)
            break;

        intmax_t val = digit * pow(base, len--);
        if (val > 0 && value > INTMAX_MAX-val) {
            err.set_code(Error::ERANGE);
            return INTMAX_MAX;
        }

        value += val;
    }

    if (negative)
        value *= (-1);

    if (endptr != nullptr)
        *endptr = (char *)nptr;

    return value;
}

unsigned long long strtoull(const char *nptr, char **endptr, int base, Error &err)
{
    uintmax_t val = strtoumax(nptr, endptr, base, err);
    if (err.code() == Error::EINVAL)
        return val;

    if (val > ULLONG_MAX || err.code() == Error::ERANGE) {
        err.set_code(Error::ERANGE);
        return ULLONG_MAX;
    }

    return val;
}

long long strtoll(const char *nptr, char **endptr, int base, Error &err)
{
    intmax_t val = strtoimax(nptr, endptr, base, err);
    if (err.code() == Error::EINVAL)
        return val;

    if (val > LLONG_MAX || err.code() == Error::ERANGE) {
        err.set_code(Error::ERANGE);
        return LLONG_MAX;
    }
    if (val < LLONG_MIN || err.code() == Error::ERANGE) {
        err.set_code(Error::ERANGE);
        return LLONG_MIN;
    }

    return val;
}

long strtol(const char *nptr, char **endptr, int base, Error &err)
{
    intmax_t val = strtoimax(nptr, endptr, base, err);
    if (err.code() == Error::EINVAL)
        return val;

    if (val > LONG_MAX || err.code() == Error::ERANGE) {
        err.set_code(Error::ERANGE);
        return LONG_MAX;
    }
    if (val < LONG_MIN || err.code() == Error::ERANGE) {
        err.set_code(Error::ERANGE);
        return LONG_MIN;
    }

    return val;
}

unsigned long strtoul(const char *nptr, char **endptr, int base, Error &err)
{
    uintmax_t val = strtoumax(nptr, endptr, base, err);
    if (err.code() == Error::EINVAL)
        return val;

    if (val > ULONG_MAX || err.code() == Error::ERANGE) {
        err.set_code(Error::ERANGE);
        return ULONG_MAX;
    }

    return val;
}
