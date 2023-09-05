#ifndef CLOCKS_H
#define CLOCKS_H

#define PIT_CHANNEL_0 0x40
#define PIT_CHANNEL_1 0x41
#define PIT_COMMAND_PORT 0x43

void pit_init(int hz);
void set_pit(int hz); // alias for pit_init

#define CURRENT_YEAR 2023 // Change this each year!

char* read_rtc();

#endif // CLOCKS_H