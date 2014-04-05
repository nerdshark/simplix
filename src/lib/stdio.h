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
__attribute((format(gnu_printf, 1, 0)));

int vsprintf(char *__restrict str, const char *__restrict format, va_list ap)
__attribute((format(gnu_printf, 2, 0)));

int vsnprintf(char *__restrict str, size_t size, const char *__restrict format, va_list ap)
__attribute((format(gnu_printf, 3, 0)));

int printf(const char *__restrict format, ...)
__attribute((format(gnu_printf, 1, 2)));

int sprintf(char *__restrict str, const char *__restrict format, ...)
__attribute((format(gnu_printf, 2, 3)));

int snprintf(char *__restrict str, size_t size, const char *__restrict format, ...)
__attribute((format(gnu_printf, 3, 4)));
