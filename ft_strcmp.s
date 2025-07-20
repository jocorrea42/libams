global ft_strcmp
section .text

ft_strcmp:
    mov     al, [rdi]       ; cargar byte de s1
    mov     bl, [rsi]       ; cargar byte de s2
    cmp     al, bl          ; comparar bytes
    jne     .diff           ; si son distintos, ir a diferencia
    cmp     al, 0           ; si llegamos al fin ('\0'), terminar
    je      .equal
    inc     rdi
    inc     rsi
    jmp     ft_strcmp

.diff:                      ; usamos al y bl (ambos bytes), devolver al - bl como entero con signo
    movzx   eax, al         ; convertir al a 32-bit sin signo
    movzx   ebx, bl
    sub     eax, ebx        ; eax = al - bl
    ret

.equal:
    xor     eax, eax        ; retorno 0
    ret
