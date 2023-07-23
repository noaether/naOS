#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../lib.h"
#include "../utils/io.h"

// ----- Pre-processor constants -----
// IDT_SIZE: Specific to x86 architecture
#define IDT_SIZE 256
// KERNEL_CODE_SEGMENT_OFFSET: the first segment after the null segment in gdt.asm
#define KERNEL_CODE_SEGMENT_OFFSET 0x8
// 32-bit Interrupt gate: 0x8E
// ( P=1, DPL=00b, S=0, type=1110b => type_attr=1000_1110b=0x8E) (thanks osdev.org)
#define IDT_INTERRUPT_GATE_32BIT 0x8e
// IO Ports for PICs
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1
// IO Ports for Keyboard
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define COMMAND_BUFFER_SIZE 100

  // ----- Structs -----
  struct IDT_pointer
  {
    unsigned short limit;
    unsigned int base;
  } __attribute__((packed));
  struct IDT_entry
  {
    unsigned short offset_lowerbits; // 16 bits
    unsigned short selector;         // 16 bits
    unsigned char zero;              // 8 bits
    unsigned char type_attr;         // 8 bits
    unsigned short offset_upperbits; // 16 bits
  } __attribute__((packed));

  // ----- External functions -----

  void keyboard_handler();
  void load_gdt();

  void load_idt(struct IDT_pointer *idt_address);
  void enable_interrupts();

  void handle_keyboard_interrupt();

  void init_idt();
  void kb_init();

  void special_key_handler(char keycode_str[]);
#ifdef __cplusplus
}
#endif

#endif // KEYBOARD_H