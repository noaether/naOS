#ifndef IRQ_H
#define IRQ_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../utils/log.h"
#include "../utils/io.h"

#include "../keyboard/keyboard.h"

#include "sound.h"
#include "framebuffer.h"

#define KERNEL_CODE_SEGMENT_OFFSET 0x8
#define INTERRUPT_GATE 0x8e

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

  struct IDT_pointer
  {
    unsigned short limit;
    unsigned int base;
  } __attribute__((packed));
  struct IDT_entry
  {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
  } __attribute__((packed));


  void idt_init();

  void load_gdt();

  int load_idt();
  void ioport_out(unsigned short port, unsigned char data);

  void remap_pic();
  int irq0();
  int irq1();
  int irq2();
  int irq3();
  int irq4();
  int irq5();
  int irq6();
  int irq7();
  int irq8();
  int irq9();
  int irq10();
  int irq11();
  int irq12();
  int irq13();
  int irq14();
  int irq15();

  void irq0_handler();
  void irq1_handler();
  void irq2_handler();
  void irq3_handler();
  void irq4_handler();
  void irq5_handler();
  void irq6_handler();
  void irq7_handler();
  void irq8_handler();
  void irq9_handler();
  void irq10_handler();
  void irq11_handler();
  void irq12_handler();
  void irq13_handler();
  void irq14_handler();
  void irq15_handler();

  void enable_interrupts();
  void disable_interrupts();

#ifdef __cplusplus
}
#endif

#endif // IRQ_H