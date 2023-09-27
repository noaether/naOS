#ifndef SYS_CALLS_H
#define SYS_CALLS_H

#include "../stdlib/types.h"

#define s_SOUND 0x00
#define s_KEYBOARD 0x01
#define s_MEM 0x02
#define s_ERROR 0x69

void syscall(unsigned int syscall_num, char arg);
void panic(char *message);

#endif // SYS_CALLS_H