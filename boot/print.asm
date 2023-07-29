print:
    pusha ; Pushes to stack



start: ; Starts to write character
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0 
    je done

    
    mov ah, 0x0e
    int 0x10 ; utilizing 0x10 interrupt

    ; increments pointer by 1
    add bx, 1
    jmp start

done: ; pops from memory stack
    popa
    ret



print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline 
    int 0x10
    mov al, 0x0d 
    int 0x10
    
    popahex_loop:
    cmp cx, 4 ; loop 4 times
    je end
    ret
