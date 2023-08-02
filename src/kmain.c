#include "drivers.h"
#include "lib.h"

#include "keyboard/keyboard.h"

#include "drivers/irq.h"
#include "drivers/clocks.h"

#include "multiboot.h"

typedef void (*call_module_t)(void);

int kmain(uint32_t ebx)
{
  if (!ebx)
  {
    return 1;
  }

  struct multiboot_info *mbinfo = (struct multiboot_info *)ebx;
  unsigned int address_of_module = mbinfo->mods_addr;

  disable_interrupts();

  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  struct logConfigStruct conf = {LOG_DEBUG, LOG_SERIAL};

  fb_print_after(welcome, sizeof(welcome));
  fb_print_after(hello, sizeof(hello));

  serial_setup(SERIAL_COM1_BASE);

  configure_log(conf);

  /* char debug[] = "Debug Log";
  char info[] = "Info Log";
  char warning[] = "Warning Log";
  char error[] = "Error Log";

  log(debug, LOG_DEBUG); // Will not log
  log(info, LOG_INFO);   // will log
  log(warning, LOG_WARNING);
  log(error, LOG_ERROR); */

  /*if(eax == MULTIBOOT_BOOTLOADER_MAGIC) {
    log("Multiboot magic number is correct", LOG_INFO);
  } else {
    log("Multiboot magic number is incorrect", LOG_ERROR);
  }*/

  remap_pic();

  load_gdt();
  idt_init();

  pit_init(1);
  kb_init();

  enable_interrupts();

  play_array();

  call_module_t start_program = (call_module_t)address_of_module;
  start_program();

  while (1)
  {
    asm volatile("hlt");
  }
}