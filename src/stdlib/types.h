#ifndef TYPES_H
#define TYPES_H

#include "stdbool.h" // For bool type
#include "stddef.h"  // For size_t
#include "string.h"

// Define the packed attribute for the struct
#define PACKED_STRUCT(name) struct __attribute__((packed)) name

// Integer types
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

// Floating-point types
typedef float float32_t;
typedef double float64_t;

// Structure to hold all the basic types
PACKED_STRUCT(BasicTypes) {
    int8_t int8;
    int16_t int16;
    int32_t int32;
    int64_t int64;

    uint8_t uint8;
    uint16_t uint16;
    uint32_t uint32;
    uint64_t uint64;

    char_t character;
    uchar_t unsignedChar;

    bool_t boolean;

    float32_t float32;
    float64_t float64;
};

#endif /* TYPE_H */
