#include "utils/io.h"

#include "drivers/framebuffer.h"

/* The C function */
int sum_of_three(int arg1, int arg2, int arg3)
{
  return arg1 + arg2 + arg3;
}

int main()
{
  char hello[] = "Hello Noa !";

  fb_write(hello, sizeof(hello));
}
