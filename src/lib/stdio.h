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

#pragma once

#include <cstdarg>
#include <cstddef>

/*
 * These functions work just like their std counterpart.
 * However, not all features of a standard-conforming printf() are supported
 * at the moment.
 * Supported at the moment are:
 * - length-modifiers
 * - all conversion specifiers _except_ the floating-point ones.
 *
 * Currently, (v)printf() unconditionally prints to the framebuffer,
 * so do not call printf before the framebuffer is initialized!
 */

int vprintf(const char *__restrict format, va_list ap)
__attribute((format(printf, 1, 0)));

int vsprintf(char *__restrict str, const char *__restrict format, va_list ap)
__attribute((format(printf, 2, 0)));

int vsnprintf(char *__restrict str, size_t size, const char *__restrict format, va_list ap)
__attribute((format(printf, 3, 0)));

int printf(const char *__restrict format, ...)
__attribute((format(printf, 1, 2)));

int sprintf(char *__restrict str, const char *__restrict format, ...)
__attribute((format(printf, 2, 3)));

int snprintf(char *__restrict str, size_t size, const char *__restrict format, ...)
__attribute((format(printf, 3, 4)));
