#include "idt.h"
#include "types.h"

// Added to .c to allow successfully compilation
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int number, uint32_t handler){
    idt[number].low_offset = low_16(handler);
    idt[number].selector = KERNEL_CS;
    idt[number].always0 = 0;
    idt[number].flags = 0x8E;
    idt[number].high_offset = high_16(handler);
}

void set_idt(){
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    asm volatile("lidtl (%0)" : : "r" (&idt_reg)); 
}