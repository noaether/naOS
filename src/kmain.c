#include "drivers.h"
#include "lib.h"

#include "cpudet-clean.c"

#include "keyboard/keyboard.h"

#include "drivers/irq.h"
#include "drivers/clocks.h"
#include "user/cmd.h"

#include "multiboot.h"

#include "filesystem/start.h"
#include "filesystem/fileops.h"

typedef void (*call_module_t)(void);

int kmain(uint32_t ebx)
{
  disable_interrupts();

  struct logConfigStruct conf = {LOG_INFO, LOG_SERIAL};

  serial_setup(SERIAL_COM1_BASE);

  configure_log(conf);

  struct cpuInfoStruct cpu = detect_cpu();

  static char firstLine[] = "               ____   _____ ";
  fb_println(firstLine, 29);

  char secondLine[] = "              / __ \\ / ____| > ";
  char *cpuType = cpu.cpuTypeString;
  strcat(secondLine, cpuType);
  fb_println(secondLine, 32 + strlen(cpuType));

  char thirdLine[] = "  _ __   __ _| |  | | (___   > ";
  char *cpuFamily = cpu.cpuFamilyString;
  strcat(thirdLine, cpuFamily);
  fb_println(thirdLine, 32 + strlen(cpuFamily));

  char fourthLine[] = " | '_ \\ / _` | |  | |\\___ \\  > ";
  char *cpuModel = cpu.cpuModelString;
  strcat(fourthLine, cpuModel);
  fb_println(fourthLine, 32 + strlen(cpuModel));

  char fifthLine[] = " | | | | (_| | |__| |____) | > ";
  char *cpuBrand = cpu.cpuBrandString;
  strcat(fifthLine, cpuBrand);
  fb_println(fifthLine, 32 + strlen(cpuBrand));

  fb_println(" |_| |_|\\__,_|\\____/|_____/", 28);

  load_gdt();
  idt_init();

  log(cpuType, LOG_INFO);
  log(cpuFamily, LOG_INFO);
  log(cpuModel, LOG_INFO);
  log(cpuBrand, LOG_INFO);

  struct multiboot_info *mbinfo = (struct multiboot_info *)ebx;

  if (mbinfo->mods_count > 0)
  {
    // Get the first module information
    struct multiboot_mod_list *module = (struct multiboot_mod_list *)mbinfo->mods_addr;

    // Get the start and end addresses of the module
    uint32_t module_start = module->mod_start;
    uint32_t module_end = module->mod_end;

    if (mbinfo->mods_count > 1)
    {
      log("MB  | More than one module found, only the first one will be executed", LOG_WARNING);
    }

    if (module_end < module_start || module_end == module_start)
    {
      log("MB  | Module end is less than module start", LOG_ERROR);
      return 1;
    }

    // Execute the module
    call_module_t start_program = (call_module_t)module_start;
    start_program();
  }

  since_enter = 0;

  fs_main();

  pit_init(20);
  enable_interrupts();
  play_array();

  kb_init();

  while (1)
  {
    asm volatile("hlt");
  }
}