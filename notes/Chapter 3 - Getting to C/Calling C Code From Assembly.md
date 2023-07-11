- many conventions on how to call C code from assembly code, *cdecl* is used here since is the one used by GCC.
	- cdecl convention states that function should be passed via [[Setting Up a Stack|Stack]] in right-to-left order, return of function is placed in `eax` register
```C
    /* The C function */
    int sum_of_three(int arg1, int arg2, int arg3)
    {
        return arg1 + arg2 + arg3;
    }
```
```x86asm

    ; The assembly code
    extern sum_of_three   ; the function sum_of_three is defined elsewhere

    push dword 3            ; arg3
    push dword 2            ; arg2
    push dword 1            ; arg1
    call sum_of_three       ; call the function, the result will be in eax
```
## Packing Structs
- configuration bytes, collections of bits in a very specific order (example with 32 bits)
```
Bit:     | 31     24 | 23          8 | 7     0 |
Content: | index     | address       | config  |
```
```C
    struct example {
        unsigned char config;   /* bit 0 - 7   */
        unsigned short address; /* bit 8 - 23  */
        unsigned char index;    /* bit 24 - 31 */
    };
```
- when using struct, no guarantee that struct will be exactly 32 bits - compiler might add padding (requirements set by hardware/compiler, etc.)
	- very important that compiler doesn't add any padding because those are configuration bytes
	- attribute `packed` (only GCC) can be used to force to not add padding
```C
    struct example {
        unsigned char config;   /* bit 0 - 7   */
        unsigned short address; /* bit 8 - 23  */
        unsigned char index;    /* bit 24 - 31 */
    } __attribute__((packed));
```
