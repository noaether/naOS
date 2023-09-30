#ifndef IO_H
#define IO_H

#include <stdint.h>

/** outb:
 *  Sends the given byte to the given I/O port.
 *
 *  @param port The I/O port to send the data
 *  @param data The data to send to the I/O port (in byte)
 */

void outb(unsigned short port, unsigned char data);

/** inb:
 *  Reads byte from the given I/O port.
 *  @param port The I/O port to read the data
 */

unsigned char inb(unsigned short port);

void inl(uint16_t port);
void outl(uint16_t port, uint32_t data);

char ioport_in(unsigned short port);
void ioport_out(unsigned short port, unsigned char data);

#endif // IO_H