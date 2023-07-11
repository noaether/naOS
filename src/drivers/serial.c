#include "../utils/io.h" /* io.h is implement in the section "Moving the cursor" */
#include "serial.h"
/* The I/O ports */

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
  outb(SERIAL_LINE_COMMAND_PORT(com),
       SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com),
       (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com),
       divisor & 0x00FF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 * @param config The configuration to use
 */
void serial_configure_line(unsigned short com, unsigned char config)
{
  outb(SERIAL_LINE_COMMAND_PORT(com), config); // config is 0x03 default
}

void serial_configure_fifo(unsigned short com, unsigned char config)
{
  outb(SERIAL_FIFO_CONTROL_PORT(com), config); // config is 0xC7 default
}