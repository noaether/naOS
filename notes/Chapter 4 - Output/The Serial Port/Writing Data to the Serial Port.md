- writing data is done via data i/o port [[Configuring the Line]]
- before writing [[FIFO Queues|FIFO Queue]] has to be empty
- [[Configuring the Line|line]] status i/o register (read-only, afaik) uses bit6 to show that all previous writes have been completed **but** bit5 is used to show that [[FIFO Queues|FIFO queue]] is empty *what we need*

- reading content of i/o port is done via assembly `in`. need to implement it in C like we did with for [[The Framebuffer]] when [[Moving the Cursor#^7b4482|moving cursor]]
```ios
    global inb

    ; inb - returns a byte from the given I/O port
    ; stack: [esp + 4] The address of the I/O port
    ;        [esp    ] The return address
    inb:
        mov dx, [esp + 4]       ; move the address of the 
        in  al, dx              ; read a byte from the I/O 
        ret                     ; return the read byte
```
```ioh
    /* in file io.h */

    /** inb:
     *  Read a byte from an I/O port.
     *
     *  @param  port The address of the I/O port
     *  @return      The read byte
     */
    unsigned char inb(unsigned short port);
```

