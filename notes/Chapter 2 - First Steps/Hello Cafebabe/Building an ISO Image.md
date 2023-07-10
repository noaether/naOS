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
	- iso/grub/menu.lst
```menu.lst
    default=0
    timeout=0

    title os
    kernel /boot/kernel.elf
```
- build iso image
```
    genisoimage -R                              \
                -b boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o os.iso                       \
                iso
```