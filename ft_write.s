; ****************************************************************************
; ft_write.s
; Implementación de write conforme al man y normas 42
; ssize_t ft_write(int fd, const void *buf, size_t count)
; ****************************************************************************

global ft_write
extern __errno_location

section .text

ft_write:
    mov     rax, 1          ; syscall number: write
    syscall                 ; llamada al sistema
    cmp     rax, 0
    jl      .error          ; si rax < 0, hubo error
    ret

.error:
    ; No usar rbx (callee-saved), usamos rcx
    mov     rcx, rax        ; guardar valor de error
    neg     rcx             ; hacer positivo (errno)
    call    __errno_location
    mov     [rax], rcx      ; *errno = código de error
    mov     rax, -1         ; retorno de write en caso de error
    ret
