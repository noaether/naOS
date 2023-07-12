#include "utils/io.h"

#include "drivers/framebuffer.h"
#include "drivers/serial.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
  return arg1 + arg2 + arg3;
}

int main()
{
  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  char log[] = "Hello from serial port\n";

  fb_write(welcome, sizeof(welcome));
  fb_print_after(hello, sizeof(hello));
  
  serial_setup(SERIAL_COM1_BASE);
  serial_write(log);
}
