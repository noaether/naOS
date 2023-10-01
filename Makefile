OBJECTS = src/drivers/gdt.o src/loader.o src/kmain.o src/memory.o \
    src/drivers/framebuffer.o src/drivers/serial.o src/drivers/sound.o src/drivers/irq.o src/drivers/irq_asm.o src/drivers/clocks.o src/drivers/sys_calls.o \
    src/keyboard/keyboard.o \
    src/user/cmd.o \
    src/utils/io.o src/utils/log.o \
    src/lib/naOS/string.o src/lib/naOS/math.o src/lib/printf.o \
    src/filesystem/fileops.o

TARGET = kernel.elf
CC = i686-elf-gcc
CCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -lgcc -Wall -Wextra -Werror -c -I/home/noa/opt/cross/lib/gcc/i686-elf/9.4.0/include -I/media/noa/Code/C/naOS/src/lib -I/media/noa/Code/C/naOS/src -c
AS = nasm
ASFLAGS = -f elf
LDFLAGS = -T src/link.ld -nostdlib --verbose -L/home/noa/opt/cross/lib/gcc/i686-elf/9.4.0 -lgcc

all: os.iso

os.iso: $(TARGET)
	cp $(TARGET) iso/boot/$(TARGET)
	grub-mkrescue -o os.iso iso

$(TARGET): $(OBJECTS) program.bin
	$(CC) --verbose $(LDFLAGS) $(OBJECTS) /home/noa/opt/cross/lib/gcc/i686-elf/9.4.0/libgcc.a -o $(TARGET)

%.o: %.c
	$(CC) --verbose $(CCFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

program.bin:
	nasm -f elf32 src/modules/initfpu.asm -o src/modules/initfpu.out
	ld -m elf_i386 -Ttext 0x0 --oformat binary src/modules/initfpu.out -o src/modules/initfpu.bin
	cp src/modules/initfpu.bin iso/boot/modules/initfpu

run-q: os.iso
	qemu-system-i386 os.iso -m 4M -serial file:com1.out -soundhw pcspk -rtc base=localtime -d int,cpu_reset,pcall,guest_errors,unimp -no-reboot

run-b: os.iso
	bochs -f bochsrc.txt -q

clean:
	rm -rf $(OBJECTS) $(TARGET) src/*.elf *.iso *.bin iso/boot/*.bin iso/boot/*.elf iso/boot/modules/*
