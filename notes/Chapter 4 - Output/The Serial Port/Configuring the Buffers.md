- data transmitted via serial port is placed in buffers (in/out)
	- means if you send data faster than it can respond, the buffer will just wait instead of half-sending data
	- buffer can get full and data will be lost
	- buffers are FIFO queues (first in, first out)
		- FIFO is configured with [[Configuring the Buffers#^bfa264|these]] [[Configuration Bytes]] following [[Configuring the Buffers#^5fffd5|this spec table]]
		- will use `0xC7 = 11000111` to enable fifo, clear queues, use 14 bytes as size of queue
```
Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
Content: | lvl | bs | r | dma | clt | clr | e |
```
^bfa264
| Name | Description                                                |
|------|------------------------------------------------------------|
| lvl  | How many bytes should be stored in the FIFO buffers         |
| bs   | If the buffers should be 16 or 64 bytes large               |
| r    | Reserved for future use                                    |
| dma  | How the serial port data should be accessed                 |
| clt  | Clear the transmission FIFO buffer                          |
| clr  | Clear the receiver FIFO buffer                              |
| e    | If the FIFO buffer should be enabled or not                 | ^5fffd5
