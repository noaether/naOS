/*
 * Copyright (c) 2006-2007 -  http://brynet.biz.tm - <brynet@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "stdlib/string.h"
#include "utils/structs.h"

/* You need to include a file with fairly(ish) compliant fb_print_after prototype, Decimal and String support like %s and %d and this is truely all you need! */
// #include <stdio.h> /* for fb_print_after(); */

/* Required Declarations */
struct cpuInfoStruct do_intel(void);
int do_amd(void);
char *printregs(int eax, int ebx, int ecx, int edx);

#define cpuid(in, a, b, c, d) __asm__("cpuid"                              \
                                      : "=a"(a), "=b"(b), "=c"(c), "=d"(d) \
                                      : "a"(in));

/* Simply call this function detect_cpu(); */
struct cpuInfoStruct detect_cpu(void)
{ /* or main() if your trying to port this as an independant application */
  unsigned long ebx, unused;
  cpuid(0, unused, ebx, unused, unused);
  struct cpuInfoStruct cpuInfo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  switch (ebx)
  {
  case 0x756e6547: /* Intel Magic Code */
    return do_intel();
  case 0x68747541:  /* AMD Magic Code */
    return cpuInfo; // do_amd() goes here, but i havent adapted it yet
  default:
    return cpuInfo;
  }
  return cpuInfo;
}

/* Intel Specific brand list */
char *Intel[] = {
    "Brand ID Not Supported.",
    "Intel(R) Celeron(R) processor",
    "Intel(R) Pentium(R) III processor",
    "Intel(R) Pentium(R) III Xeon(R) processor",
    "Intel(R) Pentium(R) III processor",
    "Reserved",
    "Mobile Intel(R) Pentium(R) III processor-M",
    "Mobile Intel(R) Celeron(R) processor",
    "Intel(R) Pentium(R) 4 processor",
    "Intel(R) Pentium(R) 4 processor",
    "Intel(R) Celeron(R) processor",
    "Intel(R) Xeon(R) Processor",
    "Intel(R) Xeon(R) processor MP",
    "Reserved",
    "Mobile Intel(R) Pentium(R) 4 processor-M",
    "Mobile Intel(R) Pentium(R) Celeron(R) processor",
    "Reserved",
    "Mobile Genuine Intel(R) processor",
    "Intel(R) Celeron(R) M processor",
    "Mobile Intel(R) Celeron(R) processor",
    "Intel(R) Celeron(R) processor",
    "Mobile Geniune Intel(R) processor",
    "Intel(R) Pentium(R) M processor",
    "Mobile Intel(R) Celeron(R) processor"};

/* This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table. */
char *Intel_Other[] = {
    "Reserved",
    "Reserved",
    "Reserved",
    "Intel(R) Celeron(R) processor",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Intel(R) Xeon(R) processor MP",
    "Reserved",
    "Reserved",
    "Intel(R) Xeon(R) processor",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

char *intel_type(int type)
{
  switch (type)
  {
  case 0:
    return "Original OEM";
  case 1:
    return "Overdrive";
  case 2:
    return "Dual-capable";
  case 3:
    return "Reserved";
  }
  return "Unknown";
}

char *intel_family(int family)
{
  switch (family)
  {
  case 3:
    return "i386";
  case 4:
    return "i486";
  case 5:
    return "Pentium";
  case 6:
    return "Pentium Pro";
  case 15:
    return "Pentium 4";
  }
  return "Unknown";
}

char *intel_model(int family, int model)
{
  switch (family)
  {
  case 3:
    break;
  case 4:
    switch (model)
    {
    case 0:
    case 1:
      return "DX";
    case 2:
      return "SX";
    case 3:
      return "487/DX2";
    case 4:
      return "SL";
    case 5:
      return "SX2";
    case 7:
      return "Write-back enhanced DX2";
    case 8:
      return "DX4";
    }
    return "Unknown";
  case 5:
    switch (model)
    {
    case 1:
      return "60/66";
    case 2:
      return "75-200";
    case 3:
      return "for 486 system";
    case 4:
      return "MMX";
    }
    return "Unknown";
  case 6:
    switch (model)
    {
    case 1:
      return "Pentium Pro";
    case 3:
      return "Pentium II Model 3";
    case 5:
      return "Pentium II Model 5/Xeon/Celeron";
    case 6:
      return "Celeron";
    case 7:
      return "Pentium III/Pentium III Xeon - external L2 cache";
    case 8:
      return "Pentium III/Pentium III Xeon - internal L2 cache";
    }
    return "Unknown";
  case 15:
    return "Unknown";
  }
  return "Unknown";
}

char *intel_brand(int signature, int brand)
{
  int eax, ebx, ecx, edx, unused;
  unsigned int max_eax;

  static char reg1[17], reg2[17], reg3[17];

  cpuid(0x80000000, max_eax, unused, unused, unused);

  if (max_eax >= 0x80000004)
  {
    cpuid(0x80000002, eax, ebx, ecx, edx);
    strcpy(reg1, printregs(eax, ebx, ecx, edx));

    cpuid(0x80000003, unused, ebx, ecx, edx);
    strcpy(reg2, printregs(unused, ebx, ecx, edx));

    cpuid(0x80000004, unused, ebx, ecx, edx);
    strcpy(reg3, printregs(unused, ebx, ecx, edx));

    strcat(reg1, reg2);
    strcat(reg1, reg3);

    for (int i = 0; i < 48; i++)
    {
      if (reg1[i] == 0x08)
      {
        reg1[i] = '-';
      }
    }

    return reg1;
  }
  else if (brand > 0)
  {
    if (brand < 0x18)
    {
      if (signature == 0x000006B1 || signature == 0x00000F13)
      {
        return Intel_Other[brand];
      }
      else
      {
        return Intel[brand];
      }
    }
    else
    {
      return "Unknown";
    }
  }
  return "Error";
}

/* Intel-specific information */
struct cpuInfoStruct do_intel(void)
{
  unsigned long eax, ebx, signature, unused;
  int model, family, type, brand, stepping, reserved;
  cpuid(1, eax, ebx, unused, unused);
  model = (eax >> 4) & 0xf;
  family = (eax >> 8) & 0xf;
  type = (eax >> 12) & 0x3;
  brand = ebx & 0xff;
  stepping = eax & 0xf;
  reserved = eax >> 14;
  signature = eax;

  char *cputype = intel_type(type);
  char *cpufamily = intel_family(family);
  char *cpumodel = intel_model(family, model);
  char *cpubrand = intel_brand(signature, brand);

  struct cpuInfoStruct cpuInfo = {model, family, type, brand, stepping, reserved, "GenuineIntel", cputype, cpufamily, cpumodel, cpubrand};
  return cpuInfo;
}

/* Print Registers */
char *printregs(int eax, int ebx, int ecx, int edx)
{
  static char string[17]; // Statically allocated array

  string[16] = '\0';
  for (int j = 0; j < 4; j++)
  {
    string[j] = eax >> (8 * j);
    string[j + 4] = ebx >> (8 * j);
    string[j + 8] = ecx >> (8 * j);
    string[j + 12] = edx >> (8 * j);
  }

  return string;
}

/* AMD-specific information */
int do_amd(void)
{
  fb_print_after("AMD Specific Features:\n", 24);
  unsigned long extended, eax, ebx, ecx, edx, unused;
  int family, model, stepping, reserved;
  cpuid(1, eax, unused, unused, unused);
  model = (eax >> 4) & 0xf;
  family = (eax >> 8) & 0xf;
  stepping = eax & 0xf;
  reserved = eax >> 12;
  (void)stepping;
  (void)reserved;
  fb_print_after("Family & Model: ", 17);
  switch (family)
  {
  case 4:
    fb_print_after("486 Model", 10);
    break;
  case 5:
    switch (model)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
      fb_print_after("K6 Model", 9);
      break;
    case 8:
      fb_print_after("K6-2 Model 8", 13);
      break;
    case 9:
      fb_print_after("K6-III Model 9", 15);
      break;
    default:
      fb_print_after("K5/K6 Model", 12);
      break;
    }
    break;
  case 6:
    switch (model)
    {
    case 1:
    case 2:
    case 4:
      fb_print_after("Athlon Model", 13);
      break;
    case 3:
      fb_print_after("Duron Model 3", 14);
      break;
    case 6:
      fb_print_after("Athlon MP/Mobile Athlon Model 6", 32);
      break;
    case 7:
      fb_print_after("Mobile Duron Model 7", 21);
      break;
    default:
      fb_print_after("Duron/Athlon Model", 19);
      break;
    }
    break;
  }
  fb_write("\n", -1);
  cpuid(0x80000000, extended, unused, unused, unused);
  if (extended == 0)
  {
    return 0;
  }
  if (extended >= 0x80000002)
  {
    unsigned int j;
    fb_print_after("Detected Processor Name: ", 26);
    for (j = 0x80000002; j <= 0x80000004; j++)
    {
      cpuid(j, eax, ebx, ecx, edx);
      printregs(eax, ebx, ecx, edx);
    }
    fb_write("\n", -1);
  }
  if (extended >= 0x80000007)
  {
    cpuid(0x80000007, unused, unused, unused, edx);
    if (edx & 1)
    {
      fb_print_after("Temperature Sensing Diode Detected!\n", 37);
    }
  }
  return 0;
}