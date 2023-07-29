global _start
[bits 32]
_start:
    [extern kernel_main] ; Defines calling function thats in C file
    call kernel_main ; Calls C function void main()
    jmp $
