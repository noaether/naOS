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
};

enum
{
  cmos_address = 0x70,
  cmos_data = 0x71
};
int cmos_ready()
{
  outb(cmos_address, 10);
  return (inb(cmos_data) & 0x80);
};


// TODO : MAKE IT ACTUALLY WORK
char *read_rtc() // https://wiki.osdev.org/Talk:CMOS#Reading_and_sanitizing_the_RTC
{
  char *time = malloc(10);

  while (cmos_ready())
    ;
  outb(cmos_address, 0x00);
  time[0] = inb(cmos_data);
  outb(cmos_address, 0x02);
  time[1] = inb(cmos_data);
  outb(cmos_address, 0x04);
  time[2] = inb(cmos_data);
  outb(cmos_address, 0x06);
  time[3] = inb(cmos_data);
  outb(cmos_address, 0x07);
  time[4] = inb(cmos_data);
  outb(cmos_address, 0x08);
  time[5] = inb(cmos_data) - 1;
  outb(cmos_address, 0x09);
  time[6] = inb(cmos_data);
  outb(cmos_address, 0x32);
  time[7] = inb(cmos_data);
  outb(cmos_address, 0x0a);
  time[8] = inb(cmos_data);
  outb(cmos_address, 0x0b);
  time[9] = inb(cmos_data);
  // 12 hour clock
  if (!(time[9] & 2) && (time[2] & 0x80))
  {
    time[2] = ((time[2] & 0x80) + 12) % 24;
  }
  // decimal stuff
  if (!(time[9] & 4))
  {
    time[0] = (time[0] & 0xf) + ((time[0] / 16) * 10);
    time[1] = (time[1] & 0xf) + ((time[1] / 16) * 10);
    time[2] = (time[2] & 0xf) + ((time[2] / 16) * 10);
    time[5] = (time[5] & 0xf) + ((time[5] / 16) * 10);
  }
  time[3] = (time[3] + 5) % 7;

  return time;
}
