extern handle_keyboard_interrupt

global load_gdt
global load_idt
global enable_interrupts
global keyboard_handler

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
