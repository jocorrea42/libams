global ft_list_size

section .text

ft_list_size:
    ; rdi = begin_list (puntero al primer nodo)
    xor     rax, rax            ; rax = contador = 0

.loop:
    test    rdi, rdi            ; ¿Es NULL?
    je      .done               ; Si sí, terminamos

    inc     rax                 ; contador++
    mov     rdi, [rdi + 8]      ; rdi = nodo->next
    jmp     .loop

.done:
    ret
