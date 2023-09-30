#ifndef IRQ_H
#define IRQ_H

#include "../utils/log.h"
#include "../utils/io.h"

#include "../keyboard/keyboard.h"

#include "sound.h"
#include "framebuffer.h"

/**
 * @brief Offset of the kernel code segment.
 *
 */
#define KERNEL_CODE_SEGMENT_OFFSET 0x8

/**
 * @brief Interrupt gate descriptor type.
 *
 */
#define INTERRUPT_GATE 0x8e

/**
 * @brief The port number for the command register of the first Programmable Interrupt Controller (PIC).
 *
 */
#define PIC1_COMMAND_PORT 0x20

/**                                                                                                   \
 * @brief The port number for the data register of the first Programmable Interrupt Controller (PIC). \
 *                                                                                                    \
 */                                                                                                   \
#define PIC1_DATA_PORT 0x21

/**
 * @brief The port number for the command register of the second Programmable Interrupt Controller (PIC).
 *
 */
#define PIC2_COMMAND_PORT 0xA0

/**
 * @brief The port number for the data register of the second Programmable Interrupt Controller (PIC).
 *
 */
#define PIC2_DATA_PORT 0xA1

/**
 * @brief The port number for the command register of the Programmable Interrupt Controller (PIC).
 *
 */
#define KEYBOARD_DATA_PORT 0x60

/**
 * @brief The port number for the status register of the Programmable Interrupt Controller (PIC).
 *
 */
#define KEYBOARD_STATUS_PORT 0x64

/**
 * @brief Struct representing the Interrupt Descriptor Table (IDT) pointer.
 *
 */
struct IDT_pointer
{
  unsigned short limit; /** The size of the IDT in bytes. */
  unsigned int base;    /** The base address of the IDT. */
} __attribute__((packed));

/**
 * @brief Struct representing an entry in the Interrupt Descriptor Table (IDT).
 *
 */
struct IDT_entry
{
  unsigned short int offset_lowerbits;  /** Lower 16 bits of the interrupt routine's address */
  unsigned short int selector;          /** Code segment selector */
  unsigned char zero;                   /** Always zero */
  unsigned char type_attr;              /** Type and attributes of the interrupt gate */
  unsigned short int offset_higherbits; /** Upper 16 bits of the interrupt routine's address */
} __attribute__((packed));

/**
 * Initializes the Interrupt Descriptor Table (IDT) by setting the offset and attributes of each entry.
 * The IDT is used by the processor to handle interrupts and exceptions.
 * This function remaps the Programmable Interrupt Controller (PIC) and sets the address of each interrupt handler.
 *
 * @param None
 *
 * @return None
 */
void idt_init();

void load_gdt();

int load_idt();
void ioport_out(unsigned short port, unsigned char data);

/**
 * @brief Remaps the Programmable Interrupt Controller (PIC) to change the default interrupt mapping.
 *
 * The function remaps the PIC to change the default interrupt mapping. It initializes the PICs and masks all interrupts.
 *
 * @note This function assumes that the PICs are wired in a master-slave configuration.
 *
 * @param None
 *
 * @return None
 */
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

#endif // IRQ_H