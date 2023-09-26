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

  // Now, you can use the values in eax and ebx as needed.

  // Trigger interrupt 0x29 (this may vary depending on your specific OS/assembly environment)
  asm volatile(
      "int $0x29");
}