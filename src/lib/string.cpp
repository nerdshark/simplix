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

#include <lib/string.h>

char *strcpy(char *__restrict__ dest, const char *__restrict__ src)
{
    char *tmp = dest;
    while ((*tmp++ = *src++) != '\0')
        ;

    return dest;
}

char *strncpy(char *__restrict__ dest, const char *__restrict__ src, size_t n)
{
    size_t i = 0;
    for (; i < n && src[i] != '\0'; ++i)
        dest[i] = src[i];
    for (; i < n; ++i)
        dest[i] = '\0';

    return dest;
}

size_t strlen(const char *s)
{
    size_t len = 0;
    while (*s != '\0') {
        ++len;
        ++s;
    }

    return len;
}

char *strcat(char *__restrict__ dest, const char *__restrict__ src)
{
    char *tmp = dest;

    while (*tmp != '\0')
        ++tmp;

    while ((*dest++ = *src++) != '\0')
        ;

    return dest;
}

char *strncat(char *__restrict__ dest, const char *__restrict__ src, size_t n)
{
    char *tmp = dest;

    while (*tmp != '\0')
        ++tmp;

    for (size_t i = 0; i < n && src[i] != '\0'; ++i)
        *tmp++ = src[i];

    *tmp = '\0';

    return dest;
}

int strcmp(const char *s1, const char *s2)
{
    for (; *s1 != '\0' && *s2 != '\0'; ++s1, ++s2) {
        if (*s1 > *s2)
            return 1;
        if (*s1 < *s2)
            return -1;
    }

    if (*s1 != '\0' && *s2 == '\0')
        return 1;
    if (*s1 == '\0' && *s2 != '\0')
        return -1;

    return 0;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    for (; i < n && s1[i] != '\0' && s2[i] != '\0'; ++i) {
        if (s1[i] > s2[i])
            return 1;
        if (s1[i] < s2[i])
            return -1;
    }

    if (s1[i] != '\0' && s2[i] == '\0')
        return 1;
    if (s1[i] == '\0' && s2[i] != '\0')
        return -1;

    return 0;
}

static const char *_strchr(const char *s, int c)
{
    for (; *s != '\0'; ++s)
        if (*s == c)
            return s;

    return nullptr;
}

const char *strchr(const char *s, int c)
{
    return _strchr(s, c);
}

char *strchr(char *s, int c)
{
    return (char *)_strchr(s, c);
}

static const char *_strrchr(const char *s, int c)
{
    const char *p = nullptr;
    while ((s = strchr(s, c)) != nullptr)
        p = s;

    return p;
}

const char *strrchr(const char *s, int c)
{
    return _strrchr(s, c);
}

char *strrchr(char *s, int c)
{
    return (char *)_strrchr(s, c);
}

static const char *_strchrnul(const char *s, int c)
{
    for (; *s != '\0' && *s != c; ++s)
        ;

    return s;
}

const char *strchrnul(const char *s, int c)
{
    return _strchrnul(s, c);
}

char *strchrnul(char *s, int c)
{
    return (char *)_strchrnul(s, c);
}

size_t strspn(const char *s, const char *accept)
{
    s = strpbrk(s, accept);
    if (s == nullptr)
        return 0;

    size_t len = 0;
    while (strchr(accept, *s++) != nullptr)
        ++len;

    return len;
}

size_t strcspn(const char *s, const char *reject)
{
    const char *p = strpbrk(s, reject);
    if (p != nullptr && *p == *s)
        return 0;

    size_t len = 0;
    while (strchr(reject, *s++) == nullptr)
        ++len;

    return len;
}

static const char *_strpbrk(const char *s, const char *accept)
{
    for (; *s != '\0'; ++s)
        if (strchr(accept, *s) != nullptr)
            return s;

    return nullptr;
}

const char *strpbrk(const char *s, const char *accept)
{
    return _strpbrk(s, accept);
}

char *strpbrk(char *s, const char *accept)
{
    return (char *)_strpbrk(s, accept);
}

static const char *_strstr(const char *haystack, const char *needle)
{
    for (; *haystack != '\0'; ++haystack)
        if (strcmp(haystack, needle) == 0)
            return haystack;

    return nullptr;
}

const char *strstr(const char *haystack, const char *needle)
{
    return _strstr(haystack, needle);
}

char *strstr(char *haystack, const char *needle)
{
    return (char *)_strstr(haystack, needle);
}

static const void *_memchr(const void *s, int c, size_t n)
{
    const unsigned char *t = (const unsigned char *)s;

    for (size_t i = 0; i < n; ++i)
        if (t[i] == c)
            return t+i;

    return nullptr;
}

const void *memchr(const void *s, int c, size_t n)
{
    return _memchr(s, c, n);
}

void *memchr(void *s, int c, size_t n)
{
    return (void *)_memchr(s, c, n);
}

static const void *_memrchr(const void *s, int c, size_t n)
{
    const unsigned char *t = (const unsigned char *)s;

    for (size_t i = n; i > 0; --i)
        if (t[i-1] == c)
            return t+i-1;

    return nullptr;
}

const void *memrchr(const void *s, int c, size_t n)
{
    return _memrchr(s, c, n);
}

void *memrchr(void *s, int c, size_t n)
{
    return (void *)_memrchr(s, c, n);
}

static const void *_rawmemchr(const void *s, int c)
{
    const unsigned char *t = (const unsigned char *)s;

    while (*t != c)
        ++t;

    return t;
}

const void *rawmemchr(const void *s, int c)
{
    return _rawmemchr(s, c);
}

void *rawmemchr(void *s, int c)
{
    return (void *)_rawmemchr(s, c);
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *t1 = (const unsigned char *)s1;
    const unsigned char *t2 = (const unsigned char *)s2;

    for (size_t i = 0; i < n; ++i) {
        if (t1[i] > t2[i])
            return 1;
        if (t1[i] < t2[i])
            return -1;
    }

    return 0;
}

void *memset(void *s, int c, size_t n)
{
    unsigned char *t = (unsigned char *)s;

    for (size_t i = 0; i < n; ++i)
        t[i] = c;

    return s;
}

void *memcpy(void *__restrict__ dest, const void *__restrict__ src, size_t n)
{
    unsigned char *t1 = (unsigned char *)dest;
    const unsigned char *t2 = (const unsigned char *)src;

    for (size_t i = 0; i < n; ++i)
        t1[i] = t2[i];

    return dest;
}
