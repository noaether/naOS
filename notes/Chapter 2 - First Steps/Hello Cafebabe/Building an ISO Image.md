- [[Linking the Kernel|OS]] must now be placed on media that can be loaded by machine (here: iso)
	- `genisoimage`
	- a folder must be created that contains files that will be on ISO image
```bash
    mkdir -p iso/boot/grub              # create the folder structure
    cp stage2_eltorito iso/boot/grub/   # copy the bootloader
    cp kernel.elf iso/boot/             # copy the kernel
```
- config file for [[Bootloader|GRUB]] 
	- tells where kernel is, configures some options
	- iso/grub/grub.cfg
```menu.lst
	menuentry "os" {
		multiboot /boot/kernel.elf
	}
```
- build iso image
```
	grub-mkrescue -o os.iso iso
```