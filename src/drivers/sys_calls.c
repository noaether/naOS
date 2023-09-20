#include "sys_calls.h"

void syscall(unsigned int syscall_num, ...) {
  char* args[6];
  for (int i = 0; i < 6; i++) {
    void *arg = (void *)(&syscall + i + 1);
    args[i] = arg;
  }

  asm("mov %%eax, %0" : : "r"(syscall_num));
  asm("mov %%ebx, %0" : : "r"(args[0]));
  asm volatile("int $0x29");
}