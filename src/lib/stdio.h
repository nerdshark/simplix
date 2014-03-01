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

// (v)printf() currently just prints to the framebuffer

int vprintf(const char *__restrict__ format, va_list ap);
int vsprintf(char *__restrict__ str, const char *__restrict__ format,
             va_list ap);
int vsnprintf(char *__restrict__ str, size_t size,
              const char *__restrict__ format, va_list ap);

int printf(const char *__restrict__ format, ...);
int sprintf(char *__restrict__ str, const char *__restrict__ format, ...);
int snprintf(char *__restrict__ str, size_t size,
             const char *__restrict__ format, ...);
