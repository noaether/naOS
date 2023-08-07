OBJECTS = src/drivers/gdt.o src/loader.o src/kmain.o src/drivers.o src/lib.o \
				src/drivers/framebuffer.o src/drivers/serial.o src/drivers/sound.o src/drivers/irq.o src/drivers/irq_asm.o src/drivers/clocks.o \
				src/keyboard/keyboard.o \
				src/utils/io.o src/utils/log.o src/utils/structs.o \
				src/stdlib/stdbool.o src/stdlib/stddef.o  src/stdlib/string.o src/stdlib/types.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
					-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T src/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

program.bin:
		nasm -f elf32 src/modules/initfpu.s -o src/modules/initfpu.out
		ld -m elf_i386 -Ttext 0x0 --oformat binary src/modules/initfpu.out -o src/modules/initfpu.bin
		cp src/modules/initfpu.bin iso/boot/modules/initfpu

kernel.elf: $(OBJECTS) program.bin
		ld $(LDFLAGS) $(OBJECTS) -o src/kernel.elf

os.iso: kernel.elf
		cp src/kernel.elf iso/boot/kernel.elf
		grub-mkrescue -o os.iso iso

run-q: os.iso
		qemu-system-i386 os.iso -m 32M -soundhw pcspk -serial file:com1.out -rtc base=utc -d int,cpu_reset,pcall,guest_errors,unimp -no-reboot

run-b: os.iso
		bochs -f bochsrc.txt -q

%.o: %.c
		$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
		$(AS) $(ASFLAGS) $< -o $@

clean:
		rm -rf src/*.o src/drivers/*.o src/keyboard/*.o src/utils/*.o src/stdlib/*.o src/modules/*.o src/*.elf *.iso *.bin iso/boot/*.bin iso/boot/*.elf iso/boot/modules/*