#include "clocks.h"
#include "../utils/io.h"

void pit_init(int hz)
{
  if (hz == 0 || hz > 1000 || hz < 18)
  {
    return;
  }

  asm volatile("cli");

  int div = 1193180 / hz;
  char low_byte = (char)(div & 0xFF);
  char high_byte = (char)((div >> 8) & 0xFF);

  // Set PIT in mode 3 (square wave generator) and set the channel 0
  outb(PIT_COMMAND_PORT, 0x36);

  // Send the divisor value to PIT
  outb(PIT_CHANNEL_0, low_byte);
  outb(PIT_CHANNEL_0, high_byte);

  asm volatile("sti");
};

void set_pit(int hz) // alias for pit_init,
{
  pit_init(hz);
}