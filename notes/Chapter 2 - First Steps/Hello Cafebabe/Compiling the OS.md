- fully written in assembly since C requires a stack (not available yet [[Chapter 3 - Getting to C]])
```loader.s
global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)

section .text:
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

loader:
	mov eax, 0xCAFEBABE

.loop:
	jmp .loop
```

- only thing this os does is put 0xCAFEBABE into eax register
- compiled into 32 ELF with `nasm -f elf32 loader.s` *(see: [[Tools#^55ae33|NASM]])*