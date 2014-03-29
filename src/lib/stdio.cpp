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
#include <lib/math.h>
#include <framebuffer/framebuffer.h>

enum CaseSensitivity {
    UPPERCASE,
    LOWERCASE
};

static int digit_to_char(int x, CaseSensitivity case_sensitivity);
static void *mem_reverse_inplace(void *s, size_t size);
static int signed_num_to_str(char *str, size_t size, intmax_t x, int base,
                             CaseSensitivity case_sensitivity);
static int unsigned_num_to_str(char *str, size_t size, uintmax_t x, int base,
                               CaseSensitivity case_sensitivity);

int vprintf(const char *__restrict format, va_list ap)
{
    // You may ask yourself: why 3920???
    // answer: that's the amount I can allocate here without causing
    // an 'undefined blabla ___chkstk_ms' gcc failure.
    // My only theory is that, as soon as a stack frame reaches a certain size,
    // gcc tries to run some stack-checking code on it, which for whatever
    // reason(freestanding?) is not there.
    char buf[3920];
    int ret = vsnprintf(buf, sizeof(buf), format, ap);
    if (ret == -1)
        return -1;
    ret = Framebuffer::put_string(buf, Framebuffer::Color::WHITE,
                                  Framebuffer::Color::BLACK);
    return ret;
}

int printf(const char *__restrict format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vprintf(format, ap);
    va_end(ap);
    return ret;
}

int sprintf(char *__restrict str, const char *__restrict format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vsnprintf(str, INT_MAX, format, ap);
    va_end(ap);
    return ret;
}

int snprintf(char *__restrict str, size_t size, const char *__restrict format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = vsnprintf(str, size, format, ap);
    va_end(ap);
    return ret;
}

int vsprintf(char *__restrict str, const char *__restrict format, va_list ap)
{
    return vsnprintf(str, INT_MAX, format, ap);
}

int vsnprintf(char *__restrict str, size_t size, const char *__restrict format, va_list ap)
{
    int cnt = 0;

    while (*format != '\0') {
        if (*format != '%') {
            if ((size_t)cnt < size)
                str[cnt] = *format;
            ++cnt;
            ++format;
            continue;
        }

        ++format;

        switch (*format) {
        case 'h':
            ++format;
            switch (*format) {
            case 'h':
                ++format;
                switch (*format) {
                case 'd':
                case 'i': {
                    ++format;
                    signed char val = va_arg(ap, int);
                    int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'o': {
                    ++format;
                    unsigned char val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'u': {
                    ++format;
                    unsigned char val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'x': {
                    ++format;
                    unsigned char val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'X': {
                    ++format;
                    unsigned char val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                default:
                    return -1;
                }
                break;
            default:
                switch (*format) {
                case 'd':
                case 'i': {
                    ++format;
                    signed short val = va_arg(ap, int);
                    int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'o': {
                    ++format;
                    unsigned short val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'u': {
                    ++format;
                    unsigned short val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'x': {
                    ++format;
                    unsigned short val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'X': {
                    ++format;
                    unsigned short val = va_arg(ap, int);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                default:
                    return -1;
                }
                break;
            }
            break;
        case 'l':
            ++format;
            switch (*format) {
            case 'l':
                ++format;
                switch (*format) {
                case 'd':
                case 'i': {
                    ++format;
                    long long val = va_arg(ap, long long);
                    int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'o': {
                    ++format;
                    unsigned long long val = va_arg(ap, unsigned long long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'u': {
                    ++format;
                    unsigned long long val = va_arg(ap, unsigned long long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'x': {
                    ++format;
                    unsigned long long val = va_arg(ap, unsigned long long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret;
                    break; }
                case 'X': {
                    ++format;
                    unsigned long long val = va_arg(ap, unsigned long long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                default:
                    return -1;
                }
                break;
            default:
                switch (*format) {
                case 'd':
                case 'i': {
                    ++format;
                    long val = va_arg(ap, long);
                    int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'o': {
                    ++format;
                    unsigned long val = va_arg(ap, unsigned long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'u': {
                    ++format;
                    unsigned long val = va_arg(ap, unsigned long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                    if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'x': {
                    ++format;
                    unsigned long val = va_arg(ap, unsigned long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                case 'X': {
                    ++format;
                    unsigned long val = va_arg(ap, unsigned long);
                    int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
                    if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                        return -1;
                    cnt += ret; }
                    break;
                default:
                    return -1;
                }
                break;
            }

            break;
        case 'j':
            ++format;
            switch (*format) {
            case 'd':
            case 'i': {
                ++format;
                intmax_t val = va_arg(ap, intmax_t);
                int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'o': {
                ++format;
                uintmax_t val = va_arg(ap, uintmax_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'u': {
                ++format;
                uintmax_t val = va_arg(ap, uintmax_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'x': {
                ++format;
                uintmax_t val = va_arg(ap, uintmax_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'X': {
                ++format;
                uintmax_t val = va_arg(ap, uintmax_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            default:
                return -1;
            }
            break;
        case 'z':
            ++format;
            switch (*format) {
            case 'o': {
                ++format;
                size_t val = va_arg(ap, size_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'u': {
                ++format;
                size_t val = va_arg(ap, size_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'x': {
                ++format;
                size_t val = va_arg(ap, size_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            case 'X': {
                ++format;
                size_t val = va_arg(ap, size_t);
                int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            default:
                return -1;
            }
            break;
        case 't':
            ++format;
            switch (*format) {
            case 'd':
            case 'i': {
                ++format;
                ptrdiff_t val = va_arg(ap, ptrdiff_t);
                int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
                if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                    return -1;
                cnt += ret; }
                break;
            default:
                return -1;
            }
            break;
        case 'd':
        case 'i': {
            ++format;
            int val = va_arg(ap, int);
            int ret = signed_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
            if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                return -1;
            cnt += ret; }
            break;
        case 'o': {
            ++format;
            unsigned val = va_arg(ap, unsigned);
            int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 8, LOWERCASE);
            if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                return -1;
            cnt += ret; }
            break;
        case 'u': {
            ++format;
            unsigned val = va_arg(ap, unsigned);
            int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 10, LOWERCASE);
            if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                return -1;
            cnt += ret; }
            break;
        case 'x': {
            ++format;
            unsigned val = va_arg(ap, unsigned);
            int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, LOWERCASE);
            if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                return -1;
            cnt += ret; }
            break;
        case 'X': {
            ++format;
            unsigned val = va_arg(ap, unsigned);
            int ret = unsigned_num_to_str(str+cnt, size-cnt, val, 16, UPPERCASE);
            if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                return -1;
            cnt += ret; }
            break;
        case 'c': {
            ++format;
            unsigned char val = va_arg(ap, int);
            if ((size_t)cnt < size)
                str[cnt] = val;
            ++cnt; }
            break;
        case 's': {
            ++format;
            char *val = va_arg(ap, char *);
            for (; *val != '\0'; ++val) {
                if ((size_t)cnt < size)
                    str[cnt] = *val;
                ++cnt;
            } }
            break;
        case 'p': {
            ++format;
            void *val = va_arg(ap, void *);
            int ret = unsigned_num_to_str(str+cnt, size-cnt, (uintmax_t)val, 16, LOWERCASE);
            if (ret == -1 || add_would_overflow(cnt, ret, INT_MAX))
                return -1;
            cnt += ret; }
            break;
        case '%':
            ++format;
            if ((size_t)cnt < size)
                str[cnt] = '%';
            ++cnt;
            break;
        default:
            return -1;
            break;
        }
    }

    str[cnt] = '\0';

    return cnt;
}

int signed_num_to_str(char *str, size_t size, intmax_t x, int base,
                      CaseSensitivity case_sensitivity)
{
    int cnt = 0;

    if (x < 0) {
        if ((size_t)cnt < size)
            str[cnt] = '-';
        ++cnt;
    }

    uintmax_t abs_arg = x < 0 ? -x : x;

    int ret = unsigned_num_to_str(str+cnt, size-cnt, abs_arg, base, case_sensitivity);
    if (ret == -1 || add_would_overflow(ret, cnt, INT_MAX))
        return -1;

    return cnt + ret;
}

int unsigned_num_to_str(char *str, size_t size, uintmax_t x, int base,
                        CaseSensitivity case_sensitivity)
{
    int cnt = 0;

    do {
        if ((size_t)cnt < size) {
            int ret = digit_to_char(x % base, case_sensitivity);
            if (ret == -1)
                return -1;
            str[cnt] = ret;
        }
        ++cnt;
        x /= base;
    } while (x != 0);

    mem_reverse_inplace(str, cnt);

    return cnt;
}

int digit_to_char(int x, CaseSensitivity case_sensitivity)
{
    if (x >= 0 && x <= 9)
        return x + '0';

    if (x >= 10 && x <= 35)
        return x + (case_sensitivity == UPPERCASE ? 'A' : 'a') - 10;

    return -1;
}

void *mem_reverse_inplace(void *s, size_t size)
{
    unsigned char *p = (unsigned char *)s;
    for (size_t i = size-1, j = 0; j < i; --i, ++j) {
        unsigned char c = p[i];
        p[i] = p[j];
        p[j] = c;
    }

    return s;
}
