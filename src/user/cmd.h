#ifndef CMD_H
#define CMD_H

#include <stddef.h>

extern int since_enter;

void interpret(char string[], size_t len);
int calculateNthDigitOfPi(int n);

#endif // CMD_H