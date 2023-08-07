#include "memory.h"

void memcpy(void *dest, void *src, size_t n)
{
  // Typecast src and dest addresses to (char *)
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  // Copy contents of src[] to dest[]
  for (unsigned int i = 0; i < n; i++)
    cdest[i] = csrc[i];
}

void *memset(void *s, int c, size_t n) // https://aticleworld.com/memset-in-c/
{
    unsigned char* p=s;
    while(n--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

void clear(void *dest, size_t n)
{
  memset(dest, 0, n);
}