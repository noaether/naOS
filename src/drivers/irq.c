#include "irq.h"

#include "../utils/log.h"
#include "../utils/io.h"

struct IDT_entry IDT[256];

void remap_pic()
{
  // Restart PIC1
  ioport_out(PIC1_COMMAND_PORT, 0x11);
  ioport_out(PIC2_COMMAND_PORT, 0x11);
  // ICW2: Vector Offset (this is what we are fixing)
  // Start PIC1 at 32 (0x20 in hex) (IRQ0=0x20, ..., IRQ7=0x27)
  // Start PIC2 right after, at 40 (0x28 in hex)
  ioport_out(PIC1_DATA_PORT, 0x20);
  ioport_out(PIC2_DATA_PORT, 0x28);
  // ICW3: Cascading (how master/slave PICs are wired/daisy chained)
  // Tell PIC1 there is a slave PIC at IRQ2 (why 4? don't ask me - https://wiki.osdev.org/8259_PIC)
  // Tell PIC2 "its cascade identity" - again, I'm shaky on this concept. More resources in notes
  ioport_out(PIC1_DATA_PORT, 0x0);
  ioport_out(PIC2_DATA_PORT, 0x0);
  // ICW4: "Gives additional information about the environemnt"
  // See notes for some potential values
  // We are using 8086/8088 (MCS-80/85) mode
  // Not sure if that's relevant, but there it is.
  // Other modes appear to be special slave/master configurations (see wiki)
  ioport_out(PIC1_DATA_PORT, 0x1);
  ioport_out(PIC2_DATA_PORT, 0x1);
  // Voila! PICs are initialized

  // Mask all interrupts (why? not entirely sure)
  // 0xff is 16 bits that are all 1.
  // This masks each of the 16 interrupts for that PIC.
  ioport_out(PIC1_DATA_PORT, 0xff);
  ioport_out(PIC2_DATA_PORT, 0xff);
}

void idt_init()
{
  remap_pic();

  unsigned int irq0_address = (unsigned long)irq0;
  unsigned int irq1_address = (unsigned long)irq1;
  unsigned int irq2_address = (unsigned long)irq2;
  unsigned int irq3_address = (unsigned long)irq3;
  unsigned int irq4_address = (unsigned long)irq4;
  unsigned int irq5_address = (unsigned long)irq5;
  unsigned int irq6_address = (unsigned long)irq6;
  unsigned int irq7_address = (unsigned long)irq7;
  unsigned int irq8_address = (unsigned long)irq8;
  unsigned int irq9_address = (unsigned long)irq9;
  unsigned int irq10_address = (unsigned long)irq10;
  unsigned int irq11_address = (unsigned long)irq11;
  unsigned int irq12_address = (unsigned long)irq12;
  unsigned int irq13_address = (unsigned long)irq13;
  unsigned int irq14_address = (unsigned long)irq14;
  unsigned int irq15_address = (unsigned long)irq15;

  IDT[32].offset_lowerbits = irq0_address & 0x0000FFFF;
  IDT[32].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[32].zero = 0;
  IDT[32].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[32].offset_higherbits = (irq0_address & 0xffff0000) >> 16;

  IDT[33].offset_lowerbits = irq1_address & 0x0000FFFF;
  IDT[33].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[33].zero = 0;
  IDT[33].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[33].offset_higherbits = (irq1_address & 0xffff0000) >> 16;

  IDT[34].offset_lowerbits = irq2_address & 0x0000FFFF;
  IDT[34].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[34].zero = 0;
  IDT[34].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[34].offset_higherbits = (irq2_address & 0xffff0000) >> 16;

  IDT[35].offset_lowerbits = irq3_address & 0x0000FFFF;
  IDT[35].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[35].zero = 0;
  IDT[35].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[35].offset_higherbits = (irq3_address & 0xffff0000) >> 16;

  IDT[36].offset_lowerbits = irq4_address & 0xffff;
  IDT[36].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[36].zero = 0;
  IDT[36].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[36].offset_higherbits = (irq4_address & 0xffff0000) >> 16;

  IDT[37].offset_lowerbits = irq5_address & 0xffff;
  IDT[37].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[37].zero = 0;
  IDT[37].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[37].offset_higherbits = (irq5_address & 0xffff0000) >> 16;

  IDT[38].offset_lowerbits = irq6_address & 0xffff;
  IDT[38].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[38].zero = 0;
  IDT[38].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[38].offset_higherbits = (irq6_address & 0xffff0000) >> 16;

  IDT[39].offset_lowerbits = irq7_address & 0xffff;
  IDT[39].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[39].zero = 0;
  IDT[39].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[39].offset_higherbits = (irq7_address & 0xffff0000) >> 16;

  IDT[40].offset_lowerbits = irq8_address & 0xffff;
  IDT[40].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[40].zero = 0;
  IDT[40].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[40].offset_higherbits = (irq8_address & 0xffff0000) >> 16;

  IDT[41].offset_lowerbits = irq9_address & 0xffff;
  IDT[41].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[41].zero = 0;
  IDT[41].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[41].offset_higherbits = (irq9_address & 0xffff0000) >> 16;

  IDT[42].offset_lowerbits = irq10_address & 0xffff;
  IDT[42].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[42].zero = 0;
  IDT[42].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[42].offset_higherbits = (irq10_address & 0xffff0000) >> 16;

  IDT[43].offset_lowerbits = irq11_address & 0xffff;
  IDT[43].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[43].zero = 0;
  IDT[43].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[43].offset_higherbits = (irq11_address & 0xffff0000) >> 16;

  IDT[44].offset_lowerbits = irq12_address & 0xffff;
  IDT[44].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[44].zero = 0;
  IDT[44].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[44].offset_higherbits = (irq12_address & 0xffff0000) >> 16;

  IDT[45].offset_lowerbits = irq13_address & 0xffff;
  IDT[45].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[45].zero = 0;
  IDT[45].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[45].offset_higherbits = (irq13_address & 0xffff0000) >> 16;

  IDT[46].offset_lowerbits = irq14_address & 0xffff;
  IDT[46].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[46].zero = 0;
  IDT[46].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[46].offset_higherbits = (irq14_address & 0xffff0000) >> 16;

  IDT[47].offset_lowerbits = irq15_address & 0xffff;
  IDT[47].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[47].zero = 0;
  IDT[47].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[47].offset_higherbits = (irq15_address & 0xffff0000) >> 16;

  struct IDT_pointer idt_ptr;

  idt_ptr.limit = (sizeof(struct IDT_entry) * 256) - 1;
  idt_ptr.base = (unsigned int)&IDT;

  load_idt(&idt_ptr);
}

// temporary handlers

void irq0_handler()
{
  // timer_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 0", LOG_DEBUG);
}

void irq1_handler()
{
  handle_keyboard_interrupt();
  log("IRQ 1", LOG_DEBUG);
}

void irq2_handler()
{
  // cascade_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 2", LOG_DEBUG);
}

void irq3_handler()
{
  // COM2_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 3", LOG_DEBUG);
}

void irq4_handler()
{
  // COM1_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 4", LOG_DEBUG);
}

void irq5_handler()
{
  // LPT2_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 5", LOG_DEBUG);
}

void irq6_handler()
{
  // floppy_disk_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 6", LOG_DEBUG);
}

void irq7_handler()
{
  // LPT1_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 7", LOG_DEBUG);
}

void irq8_handler()
{
  // CMOS_RTC_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 8", LOG_DEBUG);
}

void irq9_handler()
{
  // free_for_peripherals_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 9", LOG_DEBUG);
}

void irq10_handler()
{
  // free_for_peripherals_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 10", LOG_DEBUG);
}

void irq11_handler()
{
  // free_for_peripherals_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 11", LOG_DEBUG);
}

void irq12_handler()
{
  // PS2_mouse_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 12", LOG_DEBUG);
}

void irq13_handler()
{
  // FPU_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 13", LOG_DEBUG);
}

void irq14_handler()
{
  // primary_ATA_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 14", LOG_DEBUG);
}

void irq15_handler()
{
  // secondary_ATA_handler();
  ioport_out(0x20, 0x20);
  log("IRQ 15", LOG_DEBUG);
}
