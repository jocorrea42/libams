; ft_strcpy.s
; char *ft_strcpy(char *dst, const char *src)

global ft_strcpy
section .text

ft_strcpy:
    mov     rax, rdi        ; guardar puntero original de destino en rax

.copy:
    mov     dl, [rsi]       ; cargar byte de src
    mov     [rdi], dl       ; guardar en destino
    inc     rsi             ; avanzar src
    inc     rdi             ; avanzar dst
    cmp     dl, 0           ; comparar byte con 0
    jne     .copy        ; si no es cero, continuar

    ret
