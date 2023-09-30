#ifndef SERIAL_H
#define SERIAL_H

/**
 * @brief The base address of the first serial port (COM1).
 *
 * This macro defines the base address of the first serial port (COM1) as 0x3F8.
 *
 */
#define SERIAL_COM1_BASE 0x3F8

/**
 * @brief Macro to calculate the data port of the serial device.
 *
 * @param base The base address of the serial device.
 * @return The data port of the serial device.
 */
#define SERIAL_DATA_PORT(base) (base)

/**
 * @brief Macro to calculate the FIFO command port of the serial device.
 *
 * @param base The base address of the serial device.
 * @return The FIFO command port of the serial device.
 */
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)

/**
 * @brief Macro to calculate the line command port of the serial device.
 *
 * @param base The base address of the serial device.
 * @return The line command port of the serial device.
 */
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)

/**
 * @brief Macro to calculate the modem command port of the serial device.
 *
 * @param base The base address of the serial device.
 * @return The modem command port of the serial device.
 */
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)

/**
 * @brief Macro to calculate the line status port of the serial device.
 *
 * @param base The base address of the serial device.
 * @return The line status port of the serial device.
 */
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

/**
 * Configures the serial port with the given COM port number.
 *
 * @param com The COM port number to configure.
 */
void serial_setup(unsigned short com);

/**
 * Writes a string to the serial port.
 *
 * @param buf The string to write.
 */
void serial_write(char *buf);

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 * @param config The configuration to use
 */
void serial_configure_line(unsigned short com, unsigned char config);

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/**
 * Configures the FIFO (First In First Out) buffer of a serial port.
 *
 * @param com The serial port number to configure.
 * @param config The configuration value for the FIFO buffer.
 *              Default value is 0xC7.
 */
void serial_configure_fifo(unsigned short com, unsigned char config);

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

#endif // SERIAL_H