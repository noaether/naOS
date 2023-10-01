#include "../utils/io.h" /* io.h is implemented in the section "Moving the cursor" */
#include "serial.h"

#include <stddef.h>
#include <naOS/string.h>
/* The I/O ports */

void serial_setup(unsigned short com)
{
  serial_configure_baud_rate(com, 1);
  serial_configure_line(com, 0x03);
  serial_configure_fifo(com, 0xC7);
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

void serial_write(char *buf)
{

  size_t i;
  for (i = 0; strlen(buf) > i; i++)
  {
    while (serial_is_transmit_fifo_empty(SERIAL_COM1_BASE) == 0)
    {
      ioport_out(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
    }
  }
}

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
  outb(SERIAL_LINE_COMMAND_PORT(com),
       SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com),
       (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com),
       divisor & 0x00FF);
}

void serial_configure_line(unsigned short com, unsigned char config)
{
  outb(SERIAL_LINE_COMMAND_PORT(com), config); // config is 0x03 default
}

void serial_configure_fifo(unsigned short com, unsigned char config)
{
  outb(SERIAL_FIFO_COMMAND_PORT(com), config);
}

int serial_is_transmit_fifo_empty(unsigned int com)
{
  /* 0x20 = 0010 0000 */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}
