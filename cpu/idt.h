// Interrupt Descriptor Table, it defines interrupts that can be done by the CPU
#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// Segment selector for kernel
#define KERNEL_CS 0x08

typedef struct{
    uint16_t low_offset;
    uint16_t selector; // Kernel segment selector, allows for interrupts
    uint8_t always0;

    /* Way the first 8 bytes are defined
        Bit 7: Notifies CPU that interrupt is present
        Bit 6-5: Privilege of caller (0=kernel..3=user)
        Bit 4: Set to 0 for interrupt gates
        Bits 3-0: Defines 32 bit interrupt gate - 1110 or 14
    */
   uint8_t flags;
   uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

// Pointer to array of interrupt handlers that are sent to the CPU
typedef struct{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256 // Needs to be exactly 256 for CPU to properly load interrupt gates

void set_idt_gate(int number, uint32_t handler);
void set_idt();

#endif