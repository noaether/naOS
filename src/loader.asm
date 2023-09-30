	%include "src/drivers/gdt.asm"

	global loader                ; the entry symbol for ELF

	MAGIC_NUMBER equ 0x1BADB002  ; define the magic number constant
	ALIGN_MODULES equ 0x00000001 ; multiboot flags
	FLAGS equ ALIGN_MODULES
	CHECKSUM equ - (MAGIC_NUMBER + FLAGS)
	; (magic number + checksum + flags should equal 0)
	KERNEL_STACK_SIZE equ 4096   ; size of stack in bytes

section .bss
align 4                      ; align at 4 bytes
	kernel_stack:                 ; label points to the beginning of memory
		resb KERNEL_STACK_SIZE       ; reserve stack for the kernel

		section .multiboot
		align 4
		dd MAGIC_NUMBER
		dd FLAGS                     ; the flags,
		dd CHECKSUM                  ; and the checksum

section .text
align 4
extern kmain

	loader:                       ; the loader label (defined as the entry point in the linker script)
		lgdt [gdt_descriptor]        ; https: / / stackoverflow.com / a / 62885681 / 17631126
	jmp CODE_SEG:.setcs           ; Set CS to our 32 - bit flat code selector

	.setcs:
		mov ax, DATA_SEG             ; Setup the segment registers with our flat data selector
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov ss, ax                   ; Set the stack segment (SS) to the data segment (DATA_SEG) in GDT
		mov esp, kernel_stack        ; set the stack pointer
		cli                          ; Disable interrupts

		push ebx
		call kmain
		pop ebx
