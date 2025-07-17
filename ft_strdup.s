global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy
section .text

ft_strdup:
    push    rdi          ; guarda s
    call    ft_strlen
    inc     rax          ; tamaño +1
    mov     rdi, rax
    call    malloc
    cmp     rax, 0
    je      .malloc_fail
    mov     rdi, rax     ; ptr duplicado (inicio)
    pop     rsi          ; recupera s (fuente)
    call    ft_strcpy
    jmp     .done
.malloc_fail:
    xor     rax, rax
.done:
   
    ret
