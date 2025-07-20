; ****************************************************************************
; ft_write.s
; Implementación de write conforme al man y normas 42
; ssize_t ft_write(int fd, const void *buf, size_t count)
; ****************************************************************************

global ft_write

section .text

ft_write:
    mov     rax, 1          ; syscall number: write
    syscall                 ; llamada al sistema
    ret
