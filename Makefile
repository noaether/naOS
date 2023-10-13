# Compiler and flags
CC = i686-elf-gcc
CCFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding -lgcc -Wall -Wextra -Werror -c -I$$CC_PREFIX/lib/gcc/$$CC_TARGET/9.4.0/include -Isrc/lib -Isrc -c
AS = nasm
ASFLAGS = -f elf
LDFLAGS = -T src/link.ld -nostdlib --verbose -L$$cc_prefix/lib/gcc/$$cc_target/9.4.0 -lgcc

# Source files and objects
SOURCES = src/drivers/gdt.c src/loader.c src/kmain.c src/memory.c \
    src/drivers/framebuffer.c src/drivers/serial.c src/drivers/sound.c src/drivers/irq.c src/drivers/irq_asm.c src/drivers/clocks.c src/drivers/sys_calls.c \
    src/keyboard/keyboard.c \
    src/user/cmd.c \
    src/utils/io.c src/utils/log.c \
    src/lib/naOS/string.c src/lib/naOS/math.c src/lib/printf.c \
    src/filesystem/fileops.c

OBJECTS = $(SOURCES:.c=.o)

# Additional objects
PROGRAM_OBJECTS = src/modules/initfpu.o
PROGRAM_BIN = src/modules/initfpu.bin

# Targets
TARGET = kernel.elf
ISO_TARGET = os.iso

.PHONY: test_c_compilation test_asm_compilation test_program_bin_generation test_iso_creation all clean setup run

all: $(ISO_TARGET)

$(ISO_TARGET): $(TARGET)
	cp $(TARGET) iso/boot/$(TARGET)
	grub-mkrescue -o $(ISO_TARGET) iso

$(TARGET): $(OBJECTS) $(PROGRAM_BIN)
	$(CC) --verbose $(LDFLAGS) $(OBJECTS) $(PROGRAM_OBJECTS) $$CC_PREFIX/lib/gcc/$$CC_TARGET/9.4.0/libgcc.a -o $(TARGET)

%.o: %.c
	$(CC) --verbose $(CCFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

$(PROGRAM_BIN): src/modules/initfpu.asm
	nasm -f elf32 $< -o $(PROGRAM_OBJECTS)
	ld -m elf_i386 -Ttext 0x0 --oformat binary $(PROGRAM_OBJECTS) -o $@
	cp $@ iso/boot/

run: run-q

run-q: $(ISO_TARGET)
	qemu-system-i386 $(ISO_TARGET) -m 4M -serial file:qemu_com1.out -soundhw pcspk -rtc base=localtime -d int,cpu_reset,pcall,guest_errors,unimp -no-reboot

run-b: $(ISO_TARGET)
	bochs -f bochsrc.txt -q

clean:
	rm -rf $(OBJECTS) $(TARGET) $(PROGRAM_OBJECTS) $(PROGRAM_BIN) $(ISO_TARGET) iso/boot/*.bin iso/boot/*.elf iso/boot/*.bin

setup:
	bash ./configure

test_c_compilation: $(OBJECTS)
	@echo "C compilation successful"

test_asm_compilation: $(PROGRAM_OBJECTS)
	@echo "Assembly compilation successful"

test_program_bin_generation: $(PROGRAM_BIN)
	@echo "Program binary generation successful"

test_iso_creation: $(ISO_TARGET)
	@echo "ISO creation successful"