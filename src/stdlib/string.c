#include "stddef.h"

char * strcat(char *dest, const char *src)
{
    size_t i, j;
    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = 0; src[j] != '\0'; j++)
        dest[i + j] = src[j];
    dest[i + j] = '\0';
    return dest;
}

char * strcpy(char *dest, const char *src)
{
    char *temp = dest;
    while( (*dest++ = *src++) ); // or while((*dest++=*src++) != '\0');
    return temp;
} // https://stackoverflow.com/a/20190538

size_t strlen(const char *str)
{
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
