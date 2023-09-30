#ifndef SYS_CALLS_H
#define SYS_CALLS_H

#include <stddef.h>

#define s_SOUND 0x00
#define s_KEYBOARD 0x01
#define s_MEM 0x02
#define s_ERROR 0x69

/**
 * Executes a system call with the given syscall number and argument.
 *
 * @param syscall_num The number of the system call to execute.
 * @param arg The argument to pass to the system call.
 */
void syscall(unsigned int syscall_num, char arg);

/**
 * @brief Calls the system call with the error code and a message to be displayed.
 *
 * @param message The message to be displayed.
 */
void panic(char *message);

#endif // SYS_CALLS_H