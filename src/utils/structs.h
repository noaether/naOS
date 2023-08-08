#ifndef STRUCTS_H
#define STRUCTS_H

struct logConfigStruct
{
    unsigned char level;  // debug 0, info 1, warning 2, error 3
    unsigned char output; // serial 0, framebuffer 1
} __attribute__((packed));

struct cpuInfoStruct
{
    int cpuModel;
    int cpuFamily;
    int cpuType;
    int cpuBrand;
    int cpuStepping;
    int cpuReserved;

    char cpuVendor[13];
    char cpuTypeString[49];
    char cpuFamilyString[49];
    char cpuModelString[49];
    char cpuBrandString[49];
} __attribute__((packed)) cpuInfo_t;

#endif // STRUCTS_H
