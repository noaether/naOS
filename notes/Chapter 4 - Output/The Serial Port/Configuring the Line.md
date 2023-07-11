- serial port
	- speed used for sending data (bitrate)
	- yes/no error checking (parity bit, stop bits)
	- number of bits that represent a unit of data (data bits)
- line : configure how data is sent over the port
	- [[The Serial Port|serial port]] has I/O port *line command port* used for config ^2bcde2
	- 1st : Set speed for sending data
		- serial port has internal clock : 115200 Hz
		- setting speed = sending divisor to serial port
		- 115200 / 2 = 57600 Hz -> 1 result = 2 clock cycles (in, out)
		- divisor : 16 bit number, 8 bits at a time
			- send 0x80 to [[Configuring the Line#^2bcde2|line command port]] : Expect 2\*8 bits
			- [[Configuring the Line#^a4e728|see code]]
	- 2nd : Way that data should be sent
		- done by sending a [[Configuration Bytes|Configuration byte]]
			- will use 0x03 meaning lenght of 8 bits, no parity, one stop bit and break control disabled

| Name | Description                                                |
|------|------------------------------------------------------------|
| d    | Enables (`d = 1`) or disables (`d = 0`) DLAB                |
| b    | If break control is enabled (`b = 1`) or disabled (`b = 0`) |
| prty | The number of parity bits to use                            |
| s    | The number of stop bits to use (`s = 0` equals 1, `s = 1` equals 1.5 or 2) |
| dl   | Describes the length of the data                            |ç

```
Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
Content: | d | b | prty  | s | dl  |
```

```C
    #include "io.h"

    #define SERIAL_COM1_BASE                0x3F8      
    #define SERIAL_DATA_PORT(base)          (base)
    #define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
    #define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
    #define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
    #define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

    /* The I/O port commands */

    /* SERIAL_LINE_ENABLE_DLAB:
     * Tells the serial port to expect first the highest 8 bits on the data port,
     * then the lowest 8 bits will follow
     */
    #define SERIAL_LINE_ENABLE_DLAB         0x80

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
```

^a4e728


