- done via two different i/o ports
	- 0x3D4 describes data, 0x3D5 is for data
- position determined with a 16 bits integer (counting the cells from 0, left to right, top to bottom)
	- since `out` assembly code is only 8 bits, information is sent in two turns

- to set cursor at [[Writing Text| row 1, column 0]] (position 80 = 0x0050)
```C
    out 0x3D4, 14      ; 14 tells the framebuffer to expect the highest 8 bits of the position
    out 0x3D5, 0x00    ; sending the highest 8 bits of 0x0050
    out 0x3D4, 15      ; 15 tells the framebuffer to expect the lowest 8 bits of the position
    out 0x3D5, 0x50    ; sending the lowest 8 bits of 0x0050
```

- since moving can't be done in [[Chapter 3 - Getting to C|C]], need to implement it in assembly - add to file `io.s`, put header in `io.h` and import in `kmain.c` ^7b4482
```s
    global outb             ; make the label outb visible 

    ; outb - send a byte to an I/O port
    ; stack: [esp + 8] the data byte
    ;        [esp + 4] the I/O port
    ;        [esp    ] return address
    outb:
        mov al, [esp + 8]    ; move the data to be sent into 
        mov dx, [esp + 4]    ; move the address of the I/O 
        out dx, al           ; send the data to the I/O port
        ret                  ; return to the calling function
```
```h
    #ifndef INCLUDE_IO_H
    #define INCLUDE_IO_H

    /** outb:
     *  Sends the given data to the given I/O port. Defined in io.s
     *
     *  @param port The I/O port to send the data to
     *  @param data The data to send to the I/O port
     */
    void outb(unsigned short port, unsigned char data);

    #endif /* INCLUDE_IO_H */
```
```
	#include "io.h"
```


***will probably need to fiddle with gcc and nasm, good luck***
