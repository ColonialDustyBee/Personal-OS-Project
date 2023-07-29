#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>


void memory_copy(uint8_t* source, uint8_t* destination, int numberOfBytes);
void memory_set(uint8_t *destination, uint8_t value, uint32_t length);
void init_memory_manager();
void* kmalloc(size_t size); // Allocates within the kernel
#endif