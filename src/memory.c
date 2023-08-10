#include "memory.h"
#include "stdlib/types.h"

typedef struct free_block
{
  size_t size;
  struct free_block *next;
} free_block;

uintptr_t current_break; // Some global variable for your application.
                         // This would probably be properly tracked by the OS for the process
void *sbrk(intptr_t incr)
{
  uintptr_t old_break = current_break;
  current_break += incr;
  return (void *)old_break;
} // https://stackoverflow.com/a/2076547/17631126

void memcpy(void *dest, void *src, size_t n)
{
  // Typecast src and dest addresses to (char *)
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  // Copy contents of src[] to dest[]
  for (unsigned int i = 0; i < n; i++)
    cdest[i] = csrc[i];
}

void *memset(void *s, int c, size_t n)
{
  unsigned char *p = s;
  while (n--)
  {
    *p++ = (unsigned char)c;
  }
  return s;
} // https://aticleworld.com/memset-in-c/

void clear(void *dest, size_t n)
{
  memset(dest, 0, n);
}

static free_block free_block_list_head = {0, 0}; // https://stackoverflow.com/a/5422447/17631126
//static const size_t overhead = sizeof(size_t);   // https://stackoverflow.com/a/5422447/17631126
static const size_t align_to = 16;               // https://stackoverflow.com/a/5422447/17631126

void *malloc(size_t size)
{
  size = (size + sizeof(size_t) + (align_to - 1)) & ~(align_to - 1);
  free_block *block = free_block_list_head.next;
  free_block **head = &(free_block_list_head.next);
  while (block != 0)
  {
    if (block->size >= size)
    {
      *head = block->next;
      return ((char *)block) + sizeof(size_t);
    }
    head = &(block->next);
    block = block->next;
  }

  block = (free_block *)sbrk(size);
  block->size = size;

  return ((char *)block) + sizeof(size_t);
} // https://stackoverflow.com/a/5422447/17631126

void free(void *ptr)
{
  free_block *block = (free_block *)(((char *)ptr) - sizeof(size_t));
  block->next = free_block_list_head.next;
  free_block_list_head.next = block;
} // https://stackoverflow.com/a/5422447/17631126

// okay I've put the link a bunch of time but yeah thanks a lot to the guy who wrote this https://stackoverflow.com/a/5422447/17631126
// i can't even act like i can understand this (i understand the logic behind it but i don't understand how you can come up with this)