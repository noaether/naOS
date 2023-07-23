extern handle_keyboard_interrupt

global load_gdt
global load_idt
global enable_interrupts
global keyboard_handler

global ioport_in
global ioport_out
global inl
global outl

%include "src/keyboard/gdt.s"

load_gdt:
	lgdt [gdt_descriptor] ; from gdt.s
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret

enable_interrupts:
	sti
	ret

keyboard_handler:
	pushad
	cld
	call handle_keyboard_interrupt
	popad
	iretd

ioport_in:
	mov edx, [esp + 4] ; PORT_TO_READ, 16 bits
	; dx is lower 16 bits of edx. al is lower 8 bits of eax
	; Format: in <DESTINATION_REGISTER>, <PORT_TO_READ>
	in al, dx					 ; Read from port DX. Store value in AL
	; Return will send back the value in eax
	; (al in this case since return type is char, 8 bits)
	ret

ioport_out:
	mov edx, [esp + 4]	; port to write; DST_IO_PORT. 16 bits
	mov eax, [esp + 8] 	; value to write. 8 bits
	; Format: out <DST_IO_PORT>, <VALUE_TO_WRITE>
	out dx, al
	ret

inl:
	mov edx, [esp + 4]
	in eax, dx
	ret

outl:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, eax
	ret
