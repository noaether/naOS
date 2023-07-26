; GDT - Global Descriptor Table
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data:
    dw 0xfffff
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

; GDT Descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

; Define constants
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; In protected mode, set DS = INDEX to select GDT entries
; Then CPU knows to use the segment at that offset
; Example: (0x0: NULL segment; 0x8: CODE segment; 0x10: DATA segment)
