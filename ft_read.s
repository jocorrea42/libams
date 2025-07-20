global ft_read
extern __errno_location

section .text

ft_read:
    mov     rax, 0            ; syscall number: read
    syscall                   ; realiza read(fd, buf, count)
    cmp     rax, 0
    jl      .error            ; si < 0, hubo error
    ret

.error:                       ; usamos rcx como temporal para evitar modificar rdi
    mov     rcx, rax          ; rcx = valor de error (negativo)
    neg     rcx               ; errno = -rax
    call    __errno_location  ; rax = puntero a errno
    mov     [rax], rcx        ; *errno = rcx
    mov     rax, -1           ; retorno estándar en error
    ret
