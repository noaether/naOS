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

// intptr_t and unint_ptr
typedef long int intptr_t;
typedef unsigned long int uintptr_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

// Floating-point types
typedef float float32_t;
typedef double float64_t;

#endif /* TYPE_H */
