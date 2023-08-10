#ifndef MEMORY_H
#define MEMORY_H

#include "stdlib/types.h"

void memcpy(void *dest, void *src, size_t n);
void *memset(void *s, int c, size_t n); // https://aticleworld.com/memset-in-c/
void clear(void *dest, size_t n);

void *malloc(size_t size); // https://stackoverflow.com/a/5422447/17631126
void free(void *ptr); // https://stackoverflow.com/a/5422447/17631126

#endif // MEMORY_H