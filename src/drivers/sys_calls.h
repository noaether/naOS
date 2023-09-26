#ifndef SYS_CALLS_H
#define SYS_CALLS_H

#include "../stdlib/types.h"

#define s_SOUND 0x00
#define s_KEYBOARD 0x01
#define s_MEM 0x02

#define s_FALSE 0x00
#define s_TRUE 0x01

void syscall(unsigned int syscall_num, char arg);

#endif // SYS_CALLS_H