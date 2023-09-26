	%include "src/drivers/gdt.asm"

	extern handle_keyboard_interrupt

	global ioport_out

	global load_gdt
	global enable_interrupts
	global disable_interrupts

	global irq0
	global irq1
	global irq2
	global irq3
	global irq4
	global irq5
	global irq6
	global irq7
	global irq8
	global irq9
	global irq10
	global irq11
	global irq12
	global irq13
	global irq14
	global irq15

	global load_idt

	extern irq0_handler
	extern irq1_handler
	extern irq2_handler
	extern irq3_handler
	extern irq4_handler
	extern irq5_handler
	extern irq6_handler
	extern irq7_handler
	extern irq8_handler
	extern irq9_handler
	extern irq10_handler
	extern irq11_handler
	extern irq12_handler
	extern irq13_handler
	extern irq14_handler
	extern irq15_handler

	extern syscall_sound
	extern syscall_nosound

load_gdt:
	lgdt [gdt_descriptor]        ; from gdt.s
	ret

	section .text
irq0:
	pushad
	cld
	call irq0_handler
	popad
	iretd

irq1:
	pushad
	cld
	call irq1_handler
	popad
	iretd

irq2:
	pusha
	cld
	call irq2_handler
	popa
	iretd

irq3:
	pusha
	cld
	call irq3_handler
	popa
	iretd

irq4:
	pusha
	cld
	call irq4_handler
	popa
	iretd

irq5:
	pusha
	cld
	call irq5_handler
	popa
	iretd

irq6:
	pusha
	cld
	call irq6_handler
	popa
	iretd

irq7:
	pusha
	cld
	call irq7_handler
	popa
	iretd

irq8:
	pusha
	cld
	call irq8_handler
	popa
	iretd

irq9:
	push eax
	push ebx
	call irq9_handler
	pop ebx
	pop eax
	iretd

irq10:
	pusha
	cld
	call irq10_handler
	popa
	iretd

irq11:
	pusha
	cld
	call irq11_handler
	popa
	iretd

irq12:
	pusha
	cld
	call irq12_handler
	popa
	iretd

irq13:
	pusha
	cld
	call irq13_handler
	popa
	iretd

irq14:
	pusha
	cld
	call irq14_handler
	popa
	iretd

irq15:
	pusha
	cld
	call irq15_handler
	popa
	iretd

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret

enable_interrupts:
	sti
	ret

disable_interrupts:
	cli
	ret
