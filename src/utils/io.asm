	global outb
	global inb

	global ioport_in
	global ioport_out
	global inl
	global outl

outb:
	; outb - send a byte to an I / O port
	; stack: [esp + 8] the data byte
	; [esp + 4] the I / O port
	; [esp ] the return address
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

inb:
	; inb - read a byte from an I / O port
	; stack: [esp + 4] the data byte
	; [esp ] the return address
	mov [esp + 4], al
	in al, dx
	ret

ioport_in:                    ;
	mov edx, [esp + 4]           ; PORT_TO_READ, 16 bits
	; dx is lower 16 bits of edx. al is lower 8 bits of eax
	; Format: in <DESTINATION_REGISTER>, <PORT_TO_READ>
	in al, dx                    ; Read from port DX. Store value in AL
	; Return will send back the value in eax
	; (al in this case since return type is char, 8 bits)
	ret

ioport_out:
	mov edx, [esp + 4]           ; port to write; DST_IO_PORT. 16 bits
	mov eax, [esp + 8]           ; value to write. 8 bits
	; Format: out <DST_IO_PORT>, <VALUE_TO_WRITE>
	out dx, al
	ret

inl:
	mov edx, [esp + 4]           ; Move the port number from the stack to the EDX register.
	in eax, dx                   ; Perform the input operation, storing the result in EAX.
	ret                          ; Return from the function.

outl:
	mov edx, [esp + 4]           ; Move the port number from the stack to the EDX register.
	mov eax, [esp + 8]           ; Move the data value from the stack to the EAX register.
	out dx, eax                  ; Perform the output operation to the specified port using the data in EAX.
	ret                          ; Return from the function.
