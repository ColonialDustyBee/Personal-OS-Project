#ifndef TYPES_H // Guard clause
#define TYPES_H

#include <stdint.h>
// using generics instead of characters to allocate non-character bytes
// It defines several signed and unsigned types of 32, 16, and 8 bytes respectively
// This basically saves on having to repeat "unsigned short" or the like everytime we want to define a variable to have specific bytes of data available


#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address >> 16) & 0xFFFF))

#endif
