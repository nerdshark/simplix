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

#include <cstddef>

char *strcpy(char *__restrict dest, const char *__restrict src);
char *strncpy(char *__restrict dest, const char *__restrict src, size_t n);

char *strcat(char *__restrict dest, const char *__restrict src);
char *strncat(char *__restrict dest, const char *__restrict src, size_t n);

size_t strlen(const char *s);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

const char *strchr(const char *s, int c);
char *strchr(char *s, int c);
const char *strrchr(const char *s, int c);
char *strrchr(char *s, int c);
const char *strchrnul(const char *s, int c);
char *strchrnul(char *s, int c);

size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);

const char *strpbrk(const char *s, const char *accept);
char *strpbrk(char *s, const char *accept);

const char *strstr(const char *haystack, const char *needle);
char *strstr(char *haystack, const char *needle);

const void *memchr(const void *s, int c, size_t n);
void *memchr(void *s, int c, size_t n);
const void *memrchr(const void *s, int c, size_t n);
void *memrchr(void *s, int c, size_t n);
const void *rawmemchr(const void *s, int c);
void *rawmemchr(void *s, int c);

int memcmp(const void *s1, const void *s2, size_t n);

void *memset(void *s, int c, size_t n);

void *memcpy(void *__restrict dest, const void *__restrict src, size_t n);
