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

#include <limits.h>
#include <stdint.h>
#include <lib/error.h>

long strtol(const char *__restrict nptr, char **__restrict endptr,
            int base, Error::Error &err);
long long strtoll(const char *__restrict nptr, char **__restrict endptr,
                  int base, Error::Error &err);
intmax_t strtoimax(const char *__restrict nptr, char **__restrict endptr,
                   int base, Error::Error &err);

unsigned long strtoul(const char *__restrict nptr, char **__restrict endptr,
                      int base, Error::Error &err);
unsigned long long strtoull(const char *__restrict nptr, char **__restrict endptr,
                            int base, Error::Error &err);
uintmax_t strtoumax(const char *__restrict nptr, char **__restrict endptr,
                    int base, Error::Error &err);
