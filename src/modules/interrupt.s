section .multiboot
align 4
dd 0                         ; Flags (reserved and set to 0)
dd MODULE_END - $            ; Size of the module (in bytes)
dd 0                         ; Checksum (optional, set to 0 for simplicity)

section .text
align 4
mov eax, 0xCAFEBEBE
mov ebx, 0xDEADBEEF

jmp $
ret
MODULE_END:
