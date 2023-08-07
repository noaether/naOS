#ifndef MEMORY_H
#define MEMORY_H

#include "stdlib/types.h"

void memcpy(void *dest, void *src, size_t n);
void *memset(void *s, int c, size_t n); // https://aticleworld.com/memset-in-c/
void clear(void *dest, size_t n);

#endif // MEMORY_H