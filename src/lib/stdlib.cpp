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
#include <lib/stdlib.h>
#include <lib/ctype.h>
#include <lib/math.h>
#include <lib/string.h>

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

uintmax_t strtoumax(const char *__restrict__ nptr, char **__restrict__ endptr,
                    int base, Error &err)
{
    if ((base <= 2 || base >= 36) && base != 0) {
        err.set_code(Error::EINVAL);
        return 0;
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

    if (base == 0 || base == 16) {
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
    size_t position = strlen(nptr)-1;

    for (; *nptr != '\0'; ++nptr, --position) {
        int digit = char_to_value(*nptr);
        if (digit == -1 || digit >= base)
            goto end;

        Error err2 = Error::SUCCESS;
        unsigned int place_value = pow(base, position, err2);
        if (err2.code() != Error::SUCCESS) {
            err.set_code(Error::ERANGE);
            return UINTMAX_MAX;
        }

        if (multiply_would_overflow(digit, place_value, UINTMAX_MAX)) {
            err.set_code(Error::ERANGE);
            return UINTMAX_MAX;
        }

        uintmax_t digit_value = digit * place_value;

        if (add_would_overflow(value, digit_value, UINTMAX_MAX)) {
            err.set_code(Error::ERANGE);
            return UINTMAX_MAX;
        }

        value += digit_value;
    }

end:
    if (negative)
        value *= (-1); // Apparently, letting it underflow here is OK

    if (endptr != nullptr)
        *endptr = (char *)nptr;

    return value;
}

intmax_t strtoimax(const char *__restrict__ nptr, char **__restrict__ endptr,
                   int base, Error &err)
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

    if (base == 0 || base == 16) {
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
    size_t position = strlen(nptr)-1;

    for (; *nptr != '\0'; ++nptr, --position) {
        int digit = char_to_value(*nptr);
        if (digit == -1 || digit >= base)
            goto end;

        Error err2 = Error::SUCCESS;
        unsigned int place_value = pow(base, position, err2);
        if (err2.code() != Error::SUCCESS) {
            err.set_code(Error::ERANGE);
            if (negative)
                return INTMAX_MIN;
            return INTMAX_MAX;
        }

        if (multiply_would_overflow(digit, place_value, INTMAX_MAX)) {
            err.set_code(Error::ERANGE);
            if (negative)
                return INTMAX_MIN;
            return INTMAX_MAX;
        }

        intmax_t digit_value = digit * place_value;

        if (add_would_overflow(value, digit_value, INTMAX_MAX)) {
            err.set_code(Error::ERANGE);
            if (negative)
                return INTMAX_MIN;
            return INTMAX_MAX;
        }

        value += digit_value;
    }

end:
    if (negative) {
        if (multiply_would_underflow(value, -1, INTMAX_MIN)) {
            err.set_code(Error::ERANGE);
            return INTMAX_MIN;
        }
        value *= -1;
    }

    if (endptr != nullptr)
        *endptr = (char *)nptr;

    return value;
}

unsigned long long strtoull(const char *__restrict__ nptr,
                            char **__restrict__ endptr, int base, Error &err)
{
    uintmax_t val = strtoumax(nptr, endptr, base, err);

    if (val > ULLONG_MAX) {
        err.set_code(Error::ERANGE);
        return ULLONG_MAX;
    }

    return val;
}

long long strtoll(const char *__restrict__ nptr, char **__restrict__ endptr,
                  int base, Error &err)
{
    intmax_t val = strtoimax(nptr, endptr, base, err);

    if (val > LLONG_MAX) {
        err.set_code(Error::ERANGE);
        return LLONG_MAX;
    }
    if (val < LLONG_MIN) {
        err.set_code(Error::ERANGE);
        return LLONG_MIN;
    }

    return val;
}

long strtol(const char *__restrict__ nptr, char **__restrict__ endptr, int base,
            Error &err)
{
    intmax_t val = strtoimax(nptr, endptr, base, err);

    if (val > LONG_MAX) {
        err.set_code(Error::ERANGE);
        return LONG_MAX;
    }
    if (val < LONG_MIN) {
        err.set_code(Error::ERANGE);
        return LONG_MIN;
    }

    return val;
}

unsigned long strtoul(const char *__restrict__ nptr, char **__restrict__ endptr,
                      int base, Error &err)
{
    uintmax_t val = strtoumax(nptr, endptr, base, err);

    if (val > ULONG_MAX) {
        err.set_code(Error::ERANGE);
        return ULONG_MAX;
    }

    return val;
}
