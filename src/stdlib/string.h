#ifndef STRING_H
#define STRING_H

#include "stddef.h"

char *strcat(char *dest, const char *src);
char *strncat(char *dest, char *src, size_t n);
char *strcpy(char *dest, const char *src);
char *strncpy(char *s, const char *ct, size_t n);
size_t strlen(const char *str);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

char *citoa(int num, char *str, int base);
void reverse(char str[], int length);

typedef char char_t;
typedef unsigned char uchar_t;

#endif // STRING_H