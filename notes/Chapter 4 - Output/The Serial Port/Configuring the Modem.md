- modem control register -> control very simple hardware flow via RTS (Ready To Transmit) and DTR (Data Terminal Ready).
	- controls conversation between serial devices on [[The Serial Port|serial port]] 
	- want RTS and DTR to be 1, meaning we are ready to send data 
	- configured with [[Configuration Bytes]]
		- will use `0x03 = 00000011` for RTS=1 & DTS=1, no interrupts because no data received is handled
```
Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
```

| Name | Description                                       |
|------|---------------------------------------------------|
| r    | Reserved                                          |
| af   | Autoflow control enabled                          |
| lb   | Loopback mode (used for debugging serial ports)   |
| ao2  | Auxiliary output 2, used for receiving interrupts |
| ao1  | Auxiliary output 1                                |
| rts  | Ready To Transmit                                 |
| dtr  | Data Terminal Ready                               |
