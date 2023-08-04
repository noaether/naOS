	section .multiboot
	align 4
	dd 0                         ; Flags (reserved and set to 0)
	dd MODULE_END - $            ; Size of the module (in bytes)
	dd 0                         ; Checksum (optional, set to 0 for simplicity)

	section .text
    align 8
	; Try to find the x87 FPU
	call x87_fpu_find
	cmp al, 1                    ; FPU found?
	jne no_fpu                   ; If not, handle no FPU case

	; FPU found, set CR0 for FPU
	pushf
	pop ax
	or al, 1 << 1                ; Set MP flag
	or al, 1 << 2                ; Set NE flag (Native FPU Exceptions)
	push ax
	popf

	; Get FPU type (287 or 387 + )
	call fpu_type
	cmp al, 2                    ; FPU 287?
	je fpu_287
	cmp al, 3                    ; FPU 387 + ?
	je fpu_387

no_fpu:
	; Handle case where no FPU is present
	; Set CR0 for emulation
	pushf
	pop ax
	or al, 1 << 2                ; Set EM flag
	and al, ~(1 << 1)            ; Clear MP flag
	push ax
	popf

	; Rest of the code here

	jmp done

fpu_287:
	; Code for 287 FPU here
	jmp done

fpu_387:
	; Code for 387 + FPU here
	jmp done

done:
	; End of the program
    int 0x2D
    ret

	; Function to find the x87 FPU
x87_fpu_find:
	; Check if FPU is present
	pushf
	pop ax
	or ax, 1 << 21               ; Set ID bit in EFLAGS
	push ax
	popf
	pushf
	pop ax
	xor ah, al                   ; If ID bit doesn't change, no FPU
	jnz no_fpu

	; Check if FPU is built - in
	push eax
	xor eax, eax
	cpuid
	test edx, 1 << 0             ; Bit 0 of EDX indicates FPU presence
	setnz al
	pop eax
	ret

fpu_type:
	; Check if FPU supports differentiation of + / - infinity
	finit
	fld1
	fldz
	fdiv
	fscale                       ; Set exponent to + inf (1.0 * 2^127 = + inf)
	fchs
	fcompp
	fnstsw ax
	test ah, 1 << 6              ; ZF (bit 6) will be set if FPU treats + inf as - inf
	jz fpu_387_plus

	; FPU doesn't differentiate infinity values
	mov al, 2                    ; Indicate 80287
	ret

fpu_387_plus:
	; FPU differentiates infinity values
	mov al, 3                    ; Indicate 80387 +
	ret
MODULE_END:
