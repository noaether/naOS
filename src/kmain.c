#include "drivers.h"
#include "lib.h"

#include "keyboard/keyboard.h"

#include "drivers/irq.h"
#include "drivers/clocks.h"

int main()
{
  disable_interrupts();

  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  // char logstr[] = "Hello from serial port\n";

  struct logConfigStruct conf = {LOG_DEBUG, LOG_SERIAL};

  fb_write(welcome, sizeof(welcome));
  fb_print_after(hello, sizeof(hello));

  serial_setup(SERIAL_COM1_BASE);

  configure_log(conf);

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
}
