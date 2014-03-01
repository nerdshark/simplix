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

#include <cstddef>

char *strcpy(char *__restrict__ dest, const char *__restrict__ src);
char *strncpy(char *__restrict__ dest, const char *__restrict__ src, size_t n);

char *strcat(char *__restrict__ dest, const char *__restrict__ src);
char *strncat(char *__restrict__ dest, const char *__restrict__ src, size_t n);

size_t strlen(const char *s);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strchrnul(const char *s, int c);

size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);

char *strpbrk(const char *s, const char *accept);

char *strstr(const char *haystack, const char *needle);

void *memchr(const void *s, int c, size_t n);
void *memrchr(const void *s, int c, size_t n);
void *rawmemchr(const void *s, int c);

int memcmp(const void *s1, const void *s2, size_t n);

void *memset(void *s, int c, size_t n);

void *memcpy(void *__restrict__ dest, const void *__restrict__ src, size_t n);
