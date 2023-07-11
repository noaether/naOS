#include "utils/io.h"

#include "drivers/framebuffer.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
  return arg1 + arg2 + arg3;
}

int main()
{
  char welcome[] = "Welcome to naOS";
  char hello[] = "Hello Noa";

  fb_write(welcome);
  fb_print_after(hello);
}
