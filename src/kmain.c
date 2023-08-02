#include "drivers.h"
#include "lib.h"

#include "keyboard/keyboard.h"

#include "drivers/irq.h"
#include "drivers/clocks.h"

#include "multiboot.h"

int kmain(unsigned int ebx)
{
  multiboot_info_t *mbinfo = (multiboot_info_t *)ebx;
  unsigned int address_of_module = mbinfo->mods_addr;

  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  // char logstr[] = "Hello from serial port\n";

  struct logConfigStruct conf = {LOG_DEBUG, LOG_SERIAL};

  fb_write(welcome, sizeof(welcome));
  fb_print_after(hello, sizeof(hello));

  serial_setup(SERIAL_COM1_BASE);

  configure_log(conf);

  char module_string[16];
  citoa(address_of_module, module_string, 16);

  if (mbinfo->flags & 0x00000040)
  {
    log(module_string, LOG_INFO);
  }
  else
  {
    log("No module string found", LOG_WARNING);
  }

  char debug[] = "Debug Log";
  char info[] = "Info Log";
  char warning[] = "Warning Log";
  char error[] = "Error Log";

  log(debug, LOG_DEBUG); // Will not log
  log(info, LOG_INFO);   // will log
  log(warning, LOG_WARNING);
  log(error, LOG_ERROR);

  remap_pic();

  load_gdt();
  idt_init();

  pit_init(1);
  kb_init();

  enable_interrupts();

  play_array();

  call_module_t start_program = (call_module_t)address_of_module;
  if (start_program != NULL)
  {
    start_program();
  }
  else
  {
    log("You were right, this is the problem", LOG_ERROR)
  }

  return 0;
}
