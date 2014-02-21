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

char *strcpy(char *restrict dest, const char *restrict src)
{
    char *tmp = dest;
    while ((*tmp++ = *src++) != '\0')
        ;

    return dest;
}

char *strncpy(char *restrict dest, const char *restrict src, size_t n)
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

char *strcat(char *restrict dest, const char *restrict src)
{
    char *tmp = dest;

    while (*tmp != '\0')
        ++tmp;

    while ((*dest++ = *src++) != '\0')
        ;

    return dest;
}

char *strncat(char *restrict dest, const char *restrict src, size_t n)
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

char *strchr(const char *s, int c)
{
    for (; *s != '\0'; ++s)
        if (*s == c)
            return (char *)s;

    return NULL;
}

char *strrchr(const char *s, int c)
{
    char *p = NULL;
    while ((s = strchr(s, c)) != NULL)
        p = (char *)s;

    return p;
}

char *strchrnul(const char *s, int c)
{
    for (; *s != '\0' && *s != c; ++s)
        ;

    return (char *)s;
}

size_t strspn(const char *s, const char *accept)
{
    s = strpbrk(s, accept);
    if (s == NULL)
        return 0;

    size_t len = 0;
    while (strchr(accept, *s++) != NULL)
        ++len;

    return len;
}

size_t strcspn(const char *s, const char *reject)
{
    char *p = strpbrk(s, reject);
    if (p != NULL && *p == *s)
        return 0;

    size_t len = 0;
    while (strchr(reject, *s++) == NULL)
        ++len;

    return len;
}

char *strpbrk(const char *s, const char *accept)
{
    for (; *s != '\0'; ++s)
        if (strchr(accept, *s) != NULL)
            return (char *)s;

    return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
    for (; *haystack != '\0'; ++haystack)
        if (strcmp(haystack, needle) == 0)
            return (char *)haystack;

    return NULL;
}

void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *t = s;

    for (size_t i = 0; i < n; ++i)
        if (t[i] == c)
            return (void *)(t+i);

    return NULL;
}

void *memrchr(const void *s, int c, size_t n)
{
    const unsigned char *t = s;

    for (size_t i = n; i > 0; --i)
        if (t[i-1] == c)
            return (void *)(t+i-1);

    return NULL;
}

void *rawmemchr(const void *s, int c)
{
    const unsigned char *t = s;

    while (*t != c)
        ++t;

    return (void *)t;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *t1 = s1;
    const unsigned char *t2 = s2;

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
    unsigned char *t = s;

    for (size_t i = 0; i < n; ++i)
        t[i] = c;

    return s;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    unsigned char *t1 = dest;
    const unsigned char *t2 = src;

    for (size_t i = 0; i < n; ++i)
        t1[i] = t2[i];

    return dest;
}
