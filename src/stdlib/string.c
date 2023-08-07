#include "stddef.h"
#include "stdbool.h"

char *strcat(char *dest, const char *src)
{
    size_t i, j;
    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = 0; src[j] != '\0'; j++)
        dest[i + j] = src[j];
    dest[i + j] = '\0';
    return dest;
}

char *strcpy(char *dest, const char *src)
{
    char *temp = dest;
    while ((*dest++ = *src++))
        ; // or while((*dest++=*src++) != '\0');
    return temp;
} // https://stackoverflow.com/a/20190538

char *strncpy(char *s, const char *ct, size_t n)
{
    char *p;

    p = s;
    for (; n > 0 && *ct != '\0'; --n)
        *p++ = *ct++;
    for (; n > 0; --n)
        *p++ = '\0';
    return s;
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
