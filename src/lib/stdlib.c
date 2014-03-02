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

#include <limits.h>
#include <lib/stdlib.h>
#include <lib/ctype.h>
#include <lib/math.h>
#include <lib/string.h>
#include <lib/error.h>

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

uintmax_t strtoumax(const char *restrict nptr, char **restrict endptr,
                    int base, error_code_t *err)
{
    if ((base < 2 || base > 36) && base != 0) {
        *err = EINVAL;
        return 0;
    }

    while (isspace(*nptr))
        ++nptr;

    int negative = 0;

    switch (*nptr) {
    case '+':
        ++nptr;
        break;
    case '-':
        negative = 1;
        ++nptr;
        break;
    default:
        break;
    }

    if (base == 0 || base == 16) {
        switch (*nptr) {
        case '0':
            ++nptr;
            switch (*nptr) {
            case 'x':
            case 'X':
                ++nptr;
                base = 16;
                break;
            default:
                base = 8;
                break;
            }
            break;
        default:
            base = 10;
            break;
        }
    }

    uintmax_t value = 0;
    size_t position = strlen(nptr)-1;

    for (; *nptr != '\0'; ++nptr, --position) {
        int digit = char_to_value(*nptr);
        if (digit == -1 || digit >= base)
            goto end;

        error_code_t err2 = SUCCESS;
        unsigned int place_value = pow(base, position, &err2);
        if (err2 != SUCCESS) {
            *err = ERANGE;
            return UINTMAX_MAX;
        }

        if (MULTIPLY_WOULD_OVERFLOW(digit, place_value, UINTMAX_MAX)) {
            *err = ERANGE;
            return UINTMAX_MAX;
        }

        uintmax_t digit_value = digit * place_value;

        if (ADD_WOULD_OVERFLOW(value, digit_value, UINTMAX_MAX)) {
            *err = ERANGE;
            return UINTMAX_MAX;
        }

        value += digit_value;
    }

end:
    if (negative)
        value = -value; // Apparently, letting it underflow here is OK

    if (endptr != NULL)
        *endptr = (char *)nptr;

    return value;
}

intmax_t strtoimax(const char *restrict nptr, char **restrict endptr,
                   int base, error_code_t *err)
{
    if ((base < 2 || base > 36) && base != 0) {
        *err = EINVAL;
        return -1;
    }

    while (isspace(*nptr))
        ++nptr;

    int negative = 0;

    switch (*nptr) {
    case '+':
        ++nptr;
        break;
    case '-':
        negative = 1;
        ++nptr;
        break;
    default:
        break;
    }

    if (base == 0 || base == 16) {
        switch (*nptr) {
        case '0':
            ++nptr;
            switch (*nptr) {
            case 'x':
            case 'X':
                ++nptr;
                base = 16;
                break;
            default:
                base = 8;
                break;
            }
            break;
        default:
            base = 10;
            break;
        }
    }

    intmax_t value = 0;
    size_t position = strlen(nptr)-1;

    for (; *nptr != '\0'; ++nptr, --position) {
        int digit = char_to_value(*nptr);
        if (digit == -1 || digit >= base)
            goto end;

        error_code_t err2 = SUCCESS;
        unsigned int place_value = pow(base, position, &err2);
        if (err2 != SUCCESS) {
            *err = ERANGE;
            if (negative)
                return INTMAX_MIN;
            return INTMAX_MAX;
        }

        if (MULTIPLY_WOULD_OVERFLOW(digit, place_value, INTMAX_MAX)) {
            *err = ERANGE;
            if (negative)
                return INTMAX_MIN;
            return INTMAX_MAX;
        }

        intmax_t digit_value = digit * place_value;

        if (ADD_WOULD_OVERFLOW(value, digit_value, INTMAX_MAX)) {
            *err = ERANGE;
            if (negative)
                return INTMAX_MIN;
            return INTMAX_MAX;
        }

        value += digit_value;
    }

end:
    if (negative) {
        if (ADD_WOULD_UNDERFLOW(value, -1, INTMAX_MIN)) {
            *err = ERANGE;
            return INTMAX_MIN;
        }
        value = -value;
    }

    if (endptr != NULL)
        *endptr = (char *)nptr;

    return value;
}

unsigned long long strtoull(const char *restrict nptr, char **restrict endptr,
                            int base, error_code_t *err)
{
    uintmax_t val = strtoumax(nptr, endptr, base, err);

    if (val > ULLONG_MAX) {
        *err = ERANGE;
        return ULLONG_MAX;
    }

    return val;
}

long long strtoll(const char *restrict nptr, char **restrict endptr,
                  int base, error_code_t *err)
{
    intmax_t val = strtoimax(nptr, endptr, base, err);

    if (val > LLONG_MAX) {
        *err = ERANGE;
        return LLONG_MAX;
    }
    if (val < LLONG_MIN) {
        *err = ERANGE;
        return LLONG_MIN;
    }

    return val;
}

long strtol(const char *restrict nptr, char **restrict endptr,
            int base, error_code_t *err)
{
    intmax_t val = strtoimax(nptr, endptr, base, err);

    if (val > LONG_MAX) {
        *err = ERANGE;
        return LONG_MAX;
    }
    if (val < LONG_MIN) {
        *err = ERANGE;
        return LONG_MIN;
    }

    return val;
}

unsigned long strtoul(const char *restrict nptr, char **restrict endptr,
                      int base, error_code_t *err)
{
    uintmax_t val = strtoumax(nptr, endptr, base, err);

    if (val > ULONG_MAX) {
        *err = ERANGE;
        return ULONG_MAX;
    }

    return val;
}
