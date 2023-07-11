- prerequisite for using C is setting up a stack
- setting up a stack : make `esp` register point to end of area of free memory (on x86, stack grows from high to low) that is aligned on 4 bytes
- could point esp to random area in memory, since for now only thing in memory is [[Bootloader|GRUB]] [[BIOS]] [[OS]] and memory-mapped I/O.
	- ***NOT A GOOD IDEA*** because 1. hardcoding is bad 2. `esp` could point to something else accidentally when OS is more advanced
	- **GOOD IDEA** : reserve a piece of memory in [[Setting Up a Stack#^5f4d81|BSS]] section of kernel 

- nasm pseudo-instruction resb used to declare uninitialized data
```
    KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

    section .bss
    align 4                                     ; align at 4 bytes
    kernel_stack:                               ; label points to beginning of memory
        resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel
```
*-> add right after last definition (checksum) [[Setting Up a Stack#^575682|Source]]*

- setting up the stack pointer
```    
	mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the stack (end of memory area)
```

*according to https://github.com/littleosbook/littleosbook/issues/60* ^575682

**BSS** : In [computer programming](https://en.wikipedia.org/wiki/Computer_programming "Computer programming"), the **block starting symbol** (abbreviated to **.bss** or **bss**) is the portion of an [object file](https://en.wikipedia.org/wiki/Object_file "Object file"), executable, or [assembly language](https://en.wikipedia.org/wiki/Assembly_language "Assembly language") code that contains [statically allocated variables](https://en.wikipedia.org/wiki/Static_variable "Static variable") that are declared but have not been assigned a value yet. It is often referred to as the "bss section" or "bss segment". ^5f4d81