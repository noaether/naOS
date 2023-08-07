#include "drivers.h"
#include "lib.h"

#include "keyboard/keyboard.h"

#include "drivers/irq.h"
#include "drivers/clocks.h"

#include "multiboot.h"

typedef void (*call_module_t)(void);

int kmain(uint32_t ebx)
{
  disable_interrupts();

  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  struct logConfigStruct conf = {LOG_DEBUG, LOG_SERIAL};

  fb_print_after(welcome, sizeof(welcome));
  fb_print_after(hello, sizeof(hello));

  serial_setup(SERIAL_COM1_BASE);

  configure_log(conf);

  load_gdt();
  idt_init();

  struct multiboot_info *mbinfo = (struct multiboot_info *)ebx;

  if (mbinfo->mods_count > 0)
  {
    // Get the first module information
    struct multiboot_mod_list *module = (struct multiboot_mod_list *)mbinfo->mods_addr;

    // Get the start and end addresses of the module
    uint32_t module_start = module->mod_start;
    uint32_t module_end = module->mod_end;

    if (module_end < module_start || module_end == module_start)
    {
      log("Module end is less than module start", LOG_ERROR);
      return 1;
    }

    // Execute the module
    call_module_t start_program = (call_module_t)module_start;
    start_program();
  }

  pit_init(1);
  kb_init();

  enable_interrupts();

  play_array();

  while (1)
  {
    asm volatile("hlt");
  }
}