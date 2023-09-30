#include "sys_calls.h"

void syscall(unsigned int syscall_num, char arg)
{
  asm volatile(
      "mov %[a], %%eax\n\t"
      "mov %[b], %%ebx"
      : /* output operands */
      : [a] "r"((unsigned int)arg), [b] "r"(syscall_num)
      : /* clobbered registers */
  );

  // Trigger interrupt 0x29
  asm volatile(
      "int $0x29");
}

void panic(char *message)
{
  syscall(s_ERROR, (intptr_t)message);
}