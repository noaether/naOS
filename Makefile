OBJECTS = src/loader.o src/kmain.o src/drivers/framebuffer.o src/utils/io.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
					-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T src/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
		ld $(LDFLAGS) $(OBJECTS) -o src/kernel.elf

os.iso: kernel.elf
		cp src/kernel.elf iso/boot/kernel.elf
		grub-mkrescue -o os.iso iso
		
run: os.iso
		bochs -f bochsrc.txt -q

%.o: %.c
		$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
		$(AS) $(ASFLAGS) $< -o $@

clean:
		rm -rf *.o src/*/**.o src/kernel.elf os.iso