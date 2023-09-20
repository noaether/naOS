#include "sys_calls.h"

void syscall(unsigned int syscall_num, ...) {
  char* args[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  for (int i = 0; i < 6; i++) {
    void *arg = (void *)(&syscall + i + 1);
    args[i] = arg;
  }

  asm volatile("mov %0, %%eax" : : "r"(syscall_num));
  asm volatile("mov %0, %%ebx" : : "r"(args[0]));
  asm volatile("int $0x29");
}