#include "stddef.h"
#include "stdbool.h"
#include "../memory.h"

char *strcat(char *dest, const char *src)
{
    char *rdest = dest;

    while (*dest)
        dest++;
    while ((*dest++ = *src++))
        ;
    return rdest;
}

char *strncat(char *dest, char *src, size_t n)
{
    while (*dest)
        dest++;

    while (n-- && *src)
        *dest = *src, dest++, src++;

    *dest = '\0';
    return dest;
} // https://stackoverflow.com/q/1996950/17631126

char *strcpy(char *dest, const char *src)
{
    char *temp = dest;
    while ((*dest++ = *src++))
        ; // or while((*dest++=*src++) != '\0');
    return temp;
} // https://stackoverflow.com/a/20190538

char *strncpy(char *dest, const char *src, size_t n)
{
    char *p;

    p = dest;
    for (; n > 0 && *src != '\0'; --n)
        *p++ = *src++;
    for (; n > 0; --n)
        *p++ = '\0';
    return dest;
} // https://clc-wiki.net/wiki/K&R2_solutions:Chapter_5:Exercise_5 https://stackoverflow.com/a/1996991/17631126

size_t strlen(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

int strcmp(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 && *p1 == *p2)
        ++p1, ++p2;

    return (*p1 > *p2) - (*p2 > *p1);
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

// A utility function to reverse a string
void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}
// Implementation of citoa()
char *citoa(int num, char *str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

#define DICT_LEN 256

int *create_delim_dict(char *delim)
{
    int *d = (int *)malloc(sizeof(int) * DICT_LEN);
    memset((void *)d, 0, sizeof(int) * DICT_LEN);

    size_t i;
    for (i = 0; i < strlen(delim); i++)
    {
        d[(unsigned int) delim[i]] = 1;
    }
    return d;
}

char *strtok(char *str, char *delim)
{

    static char *last, *to_free;
    int *deli_dict = create_delim_dict(delim);

    if (!deli_dict)
    {
        return NULL;
    }

    if (str)
    {
        last = (char *)malloc(strlen(str) + 1);
        if (!last)
        {
            free(deli_dict);
        }
        to_free = last;
        strcpy(last, str);
    }

    while (deli_dict[(unsigned int) *last] && *last != '\0')
    {
        last++;
    }
    str = last;
    if (*last == '\0')
    {
        free(deli_dict);
        free(to_free);
        return NULL;
    }
    while (*last != '\0' && !deli_dict[(unsigned int) *last])
    {
        last++;
    }

    *last = '\0';
    last++;

    free(deli_dict);
    return str;
}