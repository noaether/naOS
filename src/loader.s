%include "src/drivers/gdt.s"

global loader                   ; the entry symbol for ELF

MAGIC_NUMBER    equ 0x1BADB002      ; define the magic number constant
ALIGN_MODULES   equ 0x00000001      ; tell GRUB to align modules

; calculate the checksum (all options + checksum should equal 0)
CHECKSUM        equ -(MAGIC_NUMBER + ALIGN_MODULES)

KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes

extern kmain

section .bss
align 4                         ; align at 4 bytes
kernel_stack:                   ; label points to beginning of memory
    resb KERNEL_STACK_SIZE      ; reserve stack for the kernel

section .text                       ; start of the text (code) section
align 4                             ; the code must be 4 byte aligned
		dd MAGIC_NUMBER                 ; write the magic number
		dd ALIGN_MODULES                ; write the align modules instruction
		dd CHECKSUM                     ; write the checksum

loader:                         ; the loader label (defined as entry point in linker script)
	lgdt [gdt_descriptor] ; https://stackoverflow.com/a/62885681/17631126
	jmp CODE_SEG:.setcs       ; Set CS to our 32-bit flat code selector
	.setcs:
	mov ax, DATA_SEG          ; Setup the segment registers with our flat data selector
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, kernel_stack        ; set stack pointer
	mov esp, kernel_stack        ; set stack pointer
	push ebx
	call kmain

.loop:
    jmp .loop                   ; loop forever