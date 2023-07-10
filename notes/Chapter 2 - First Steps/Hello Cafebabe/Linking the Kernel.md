- [[Compiling the OS|Code]] must now be linked to make executable file
	- want grub to load kernel at mem adress => 0x00100000, because adresses lower than that are used by [[Bootloader|GRUB]] itself
```link.ld
ENTRY(loader) /* name of the entry label */

SECTIONS {
	. = 0x00100000 /* code should be loaded at 1MB */

	.text ALIGN (0x1000) : /* align at 4kb */
	{
		*(.text)
	}

	.rodata ALIGN (0x1000) :
}