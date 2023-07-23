#include "keyboard.h"
#include "keyboard_map.h"
#include "keyboard_asm.h"

#include "../drivers.h"
#include "../utils/io.h"

struct IDT_entry IDT[IDT_SIZE]; // This is our entire IDT. Room for 256 interrupts

void init_idt()
{
  // Get the address of the keyboard_handler code in kernel.asm as a number
  unsigned int kb_handler_offset = (unsigned long)keyboard_handler;
  // Populate the first entry of the IDT

  // why 0x21 and not 0x0? first 32 interrupts (up to 0x20)
  // are reserved for the CPU.
  // These include special interrupts such as divide-by-zero exception.

  // 0x21, or 33 decimal, is the first available interrupt
  // that we can set to whatever we want.
  IDT[0x21].offset_lowerbits = kb_handler_offset & 0x0000FFFF; // lower 16 bits
  IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
  IDT[0x21].zero = 0;
  IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
  IDT[0x21].offset_upperbits = (kb_handler_offset & 0xFFFF0000) >> 16;
  // Program the PICs - Programmable Interrupt Controllers
  // Background:
  // In modern architectures, the PIC is not a separate chip.
  // It is emulated in the CPU for backwards compatability.
  // The APIC (Advanced Programmable Interrupt Controller)
  // is the new version of the PIC that is integrated into the CPU.
  // Default vector offset for PIC is 8
  // This maps IRQ0 to interrupt 8, IRQ1 to interrupt 9, etc.
  // This is a problem. The CPU reserves the first 32 interrupts for
  // CPU exceptions such as divide by 0, etc.
  // In programming the PICs, we move this offset to 0x2 (32) so that
  // we can handle all interrupts coming to the PICs without overlapping
  // with any CPU exceptions.

  // Send ICWs - Initialization Command Words
  // PIC1: IO Port 0x20 (command), 0xA0 (data)
  // PIC2: IO Port 0x21 (command), 0xA1 (data)
  // ICW1: Initialization command
  // Send a fixed value of 0x11 to each PIC to tell it to expect ICW2-4
  // Restart PIC1
  outb(PIC1_COMMAND_PORT, 0x11);
  outb(PIC2_COMMAND_PORT, 0x11);
  // ICW2: Vector Offset (this is what we are fixing)
  // Start PIC1 at 32 (0x20 in hex) (IRQ0=0x20, ..., IRQ7=0x27)
  // Start PIC2 right after, at 40 (0x28 in hex)
  outb(PIC1_DATA_PORT, 0x20);
  outb(PIC2_DATA_PORT, 0x28);
  // ICW3: Cascading (how master/slave PICs are wired/daisy chained)
  // Tell PIC1 there is a slave PIC at IRQ2 (why 4? don't ask me - https://wiki.osdev.org/8259_PIC)
  // Tell PIC2 "its cascade identity" - again, I'm shaky on this concept. More resources in notes
  outb(PIC1_DATA_PORT, 0x0);
  outb(PIC2_DATA_PORT, 0x0);
  // ICW4: "Gives additional information about the environemnt"
  // See notes for some potential values
  // We are using 8086/8088 (MCS-80/85) mode
  // Not sure if that's relevant, but there it is.
  // Other modes appear to be special slave/master configurations (see wiki)
  outb(PIC1_DATA_PORT, 0x1);
  outb(PIC2_DATA_PORT, 0x1);
  // Voila! PICs are initialized

  // Mask all interrupts (why? not entirely sure)
  // 0xff is 16 bits that are all 1.
  // This masks each of the 16 interrupts for that PIC.
  outb(PIC1_DATA_PORT, 0xff);
  outb(PIC2_DATA_PORT, 0xff);

  // Last but not least, we fill out the IDT descriptor
  // and load it into the IDTR register of the CPU,
  // which is all we need to do to make it active.
  struct IDT_pointer idt_ptr;
  idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
  idt_ptr.base = (unsigned long)&IDT;
  // Now load this IDT
  load_idt(&idt_ptr);
}

void kb_init()
{
  // 0xFD = 1111 1101 in binary. enables only IRQ1
  // Why IRQ1? Remember, IRQ0 exists, it's 0-based
  outb(PIC1_DATA_PORT, 0xFD);
}

void handle_keyboard_interrupt()
{
  // Write end of interrupt (EOI)
  outb(PIC1_COMMAND_PORT, 0x20);

  unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
  // Lowest bit of status will be set if buffer not empty
  // (thanks mkeykernel)
  /* Lowest bit of status will be set if buffer is not empty */
  if (status & 0x01)
  {
    int keycode = ioport_in(KEYBOARD_DATA_PORT);

    char keycode_str[10];
    citoa(keycode, keycode_str, 10);

    if (keycode < 0)
    {
      char logup[] = "KBD INT UP: ";
      strcat(logup, keycode_str);
      log(logup, LOG_DEBUG);
      return;
    }
    else
    {
      char logdown[] = "KBD INT DOWN: ";
      strcat(logdown, keycode_str);
      log(logdown, LOG_DEBUG);
    }
    // Check if it's a key press event (the most significant bit is clear)
    if (!(keycode & 0x80))
    {
      // convert keycode to ascii with keyboard map
      char ascii[2] = {keyboard_map[keycode], '\0'}; // Ensure null-terminated string
      if (ascii[0] == ' ')
      {
        special_key_handler(keycode_str);
      }
      log(ascii, LOG_INFO); // Pass the address of ascii to the log function

      fb_print_after(ascii, 1);
    }
  }
};

void special_key_handler(char keycode_str[]){
  char space[] = "57";
  if(strcmp(keycode_str, space) == 0) {
    fb_print_after(" ", 0);
  } else {
    fb_print_after(keycode_str, 2);
  }
}
