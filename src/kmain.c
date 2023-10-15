#include <brynet/cpudet-clean.c>

#include <keyboard/keyboard.h>

#include <drivers/serial.h>
#include <drivers/irq.h>
#include <drivers/clocks.h>
//#include <drivers/disks/ide.h>

#include <utils/log.h>
#include <user/cmd.h>

#include <multiboot.h>

#include <filesystem/fileops.h>

typedef void (*call_module_t)(void);

struct note boot_melody[] = {
    {OCTAVE_4, NOTE_C, 10},
    {OCTAVE_4, NOTE_E, 10},
    {OCTAVE_4, NOTE_FS, 10},
    {OCTAVE_4, NOTE_AS, 10},
    {OCTAVE_5, NOTE_C, 10},
};

int kmain(uint32_t ebx)
{
  disable_interrupts();

  serial_setup(SERIAL_COM1_BASE);

  struct logConfigStruct conf = {LOG_DEBUG, LOG_SERIAL};

  configure_log(conf);

  log("KRN | Kernel started!\0", LOG_INFO);

  struct cpuInfoStruct cpu = detect_cpu();

  char firstLine[] = "               ____   _____ ";
  fb_println(firstLine, 29);

  char secondLine[80];
  char *cpuType = cpu.cpuTypeString;
  sprintf(secondLine, "              / __ \\ / ____| > %s", cpuType);
  fb_println(secondLine, strlen(secondLine));

  char thirdLine[80];
  char *cpuFamily = cpu.cpuFamilyString;
  sprintf(thirdLine, "  _ __   __ _| |  | | (___   > %s", cpuFamily);
  fb_println(thirdLine, strlen(thirdLine));

  char fourthLine[80];
  char *cpuModel = cpu.cpuModelString;
  sprintf(fourthLine, " | '_ \\ / _` | |  | |\\___ \\  > %s", cpuModel);
  fb_println(fourthLine, strlen(fourthLine));

  char fifthLine[80];
  char *cpuBrand = cpu.cpuBrandString;
  sprintf(fifthLine, " | | | | (_| | |__| |____) | > %s", cpuBrand);
  fb_println(fifthLine, strlen(fifthLine));

  fb_println(" |_| |_|\\__,_|\\____/|_____/", 28);

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
      log("MB  | Module end is less than module start", LOG_ERROR);
      return 1;
    }

    // Execute the module
    call_module_t start_program = (call_module_t)module_start;
    start_program();
  }

  //ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);

  since_enter = 0;

  fs_main();

  pit_init(20);
  enable_interrupts();
  play_array(boot_melody, 5);

  kb_init();

  char buffer[100];
  int num = 42;
  char *text = "Hello World!";

  sprintf(buffer, "TST | 42 = %d, Hello World! = %s", num, text);

  log(buffer, LOG_DEBUG);

  while (1)
  {
    asm volatile("hlt");
  }
}
