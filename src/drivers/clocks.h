#ifndef CLOCKS_H
#define CLOCKS_H

#define PIT_CHANNEL_0 0x40
#define PIT_COMMAND_PORT 0x43

void pit_init(int hz);

#endif // CLOCKS_H