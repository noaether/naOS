#include "types.h"
#include "math.h"

float64_t fabs(float64_t x)
{
  return x < 0.0 ? -x : x;
}

float64_t fmod(float64_t x, float64_t m)
{
  float64_t result;
  asm("1: fprem\n\t"
      "fnstsw %%ax\n\t"
      "sahf\n\t"
      "jp 1b"
      : "=t"(result)
      : "0"(x), "u"(m)
      : "ax", "cc");
  return result;
}

float64_t sin(float64_t x)
{
  float64_t result;
  asm("fsin"
      : "=t"(result)
      : "0"(x));
  return result;
}

float64_t cos(float64_t x)
{
  return sin(x + PI / 2.0);
}

// black magic
float64_t pow(float64_t x, float64_t y)
{
  float64_t out;
  asm(
      "fyl2x;"
      "fld %%st;"
      "frndint;"
      "fsub %%st,%%st(1);"
      "fxch;"
      "fchs;"
      "f2xm1;"
      "fld1;"
      "faddp;"
      "fxch;"
      "fld1;"
      "fscale;"
      "fstp %%st(1);"
      "fmulp;"
      : "=t"(out)
      : "0"(x), "u"(y)
      : "st(1)");
  return out;
}