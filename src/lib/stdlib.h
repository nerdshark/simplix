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

long strtol(const char *restrict nptr, char **restrict endptr,
            int base, error_code_t *err);
long long strtoll(const char *restrict nptr, char **restrict endptr,
                  int base, error_code_t *err);
intmax_t strtoimax(const char *restrict nptr, char **restrict endptr,
                   int base, error_code_t *err);

unsigned long strtoul(const char *restrict nptr,
                      char **restrict endptr, int base, error_code_t *err);
unsigned long long strtoull(const char *restrict nptr,
                            char **restrict endptr, int base, error_code_t *err);
uintmax_t strtoumax(const char *restrict nptr, char **restrict endptr,
                    int base, error_code_t *err);
