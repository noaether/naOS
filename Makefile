OBJECTS = src/drivers/gdt.o src/loader.o src/kmain.o src/memory.o \
				src/drivers/framebuffer.o src/drivers/serial.o src/drivers/sound.o src/drivers/irq.o src/drivers/irq_asm.o src/drivers/clocks.o src/drivers/sys_calls.o \
				src/keyboard/keyboard.o \
				src/user/cmd.o \
				src/utils/io.o src/utils/log.o \
				src/stdlib/stdbool.o src/stdlib/stddef.o  src/stdlib/string.o src/stdlib/types.o src/stdlib/math.o \
				src/filesystem/fileops.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
					-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T src/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

program.bin:
		nasm -f elf32 src/modules/initfpu.asm -o src/modules/initfpu.out
		ld -m elf_i386 -Ttext 0x0 --oformat binary src/modules/initfpu.out -o src/modules/initfpu.bin
		cp src/modules/initfpu.bin iso/boot/modules/initfpu

kernel.elf: $(OBJECTS) program.bin
		ld $(LDFLAGS) $(OBJECTS) -o src/kernel.elf

os.iso: kernel.elf
		cp src/kernel.elf iso/boot/kernel.elf
		grub-mkrescue -o os.iso iso

run-q: os.iso
		qemu-system-i386 os.iso -m 4M -serial file:com1.out -rtc base=localtime -d int,cpu_reset,pcall,guest_errors,unimp -no-reboot
# -soundhw pcspk

run-b: os.iso
		bochs -f bochsrc.txt -q

%.o: %.c
		$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
		$(AS) $(ASFLAGS) $< -o $@

clean:
		rm -rf $(OBJECTS) src/*.elf *.iso *.bin iso/boot/*.bin iso/boot/*.elf iso/boot/modules/*