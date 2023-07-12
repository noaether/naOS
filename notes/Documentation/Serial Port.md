| COM Port | IO Port |
|----------|---------|
| COM1     | 0x3F8  |
| COM2     | 0x2F8  |
| COM3     | 0x3E8  |
| COM4     | 0x2E8  |
| COM5     | 0x5F8  |
| COM6     | 0x4F8  |
| COM7     | 0x5E8  |
| COM8     | 0x4E8  |

| IO Port Offset | Setting of DLAB | Register mapped to this port                                                 |
|----------------|----------------|--------------------------------------------------------------------------------|
| +0             | 0              | Data register.  Reading this registers read from the Receive buffer.  Writing to this register writes to the Transmit buffer. |
| +1             | 0              | Interrupt Enable Register.                                                   |
| +0             | 1              | With DLAB set to 1, this is the least significant byte of the divisor value for setting the baud rate. |
| +1             | 1              | With DLAB set to 1, this is the most significant byte of the divisor value.    |
| +2             | -              | Interrupt Identification and FIFO control registers                           |
| +3             | -              | Line Control Register.  The most significant bit of this register is the DLAB. |
| +4             | -              | Modem Control Register.                                                      |
| +5             | -              | Line Status Register.                                                         |
| +6             | -              | Modem Status Register.                                                        |
| +7             | -              | Scratch Register.                                                             |
