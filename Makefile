OBJECTS = src/loader.o src/kmain.o src/drivers.o src/lib.o \
				src/drivers/framebuffer.o src/drivers/serial.o src/drivers/sound.o src/drivers/irq.o src/drivers/irq_asm.o src/drivers/gdt.o src/drivers/clocks.o \
				src/keyboard/keyboard.o \
				src/utils/io.o src/utils/log.o src/utils/structs.o \
				src/stdlib/stdbool.o src/stdlib/stddef.o  src/stdlib/string.o src/stdlib/types.o src/stdlib/math.o
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
		$(AS) -f bin src/program.s -o program
		cp program iso/boot/modules/program

		cp src/kernel.elf iso/boot/kernel.elf
		grub-mkrescue -o os.iso iso

run-q: os.iso
		qemu-system-i386 os.iso -m 32M -soundhw pcspk -serial file:com1.out -rtc base=utc -d int,cpu_reset,pcall,guest_errors,unimp -no-reboot

run-b: os.iso
		bochs -f bochsrc.txt -q

%.o: %.c
		$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
		$(AS) $(ASFLAGS) $< -o $@

clean:
		rm -rf *.o src/*.o src/**/**.o src/**/**/**.o src/kernel.elf os.iso bochslog.txt program iso/modules/program