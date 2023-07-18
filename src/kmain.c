#include "utils/io.h"
#include "utils/log.h"
#include "utils/structs.h"

#include "drivers/framebuffer.h"
#include "drivers/serial.h"

#include "stdlib/stdbool.h"
#include "stdlib/stddef.h"
#include "stdlib/types.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
  return arg1 + arg2 + arg3;
}

int main()
{
  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  char logstr[] = "Hello from serial port\n";

  struct logConfigStruct conf = {0, 0};

  fb_write(welcome, sizeof(welcome));
  fb_print_after(hello, sizeof(hello));

  serial_setup(SERIAL_COM1_BASE);

  configure_log(conf);
  log(logstr, 0, sizeof(logstr));
}
