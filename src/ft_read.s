global ft_read

section .text

ft_read:
    mov     rax, 0            ; syscall number: read
    syscall                   ; realiza read(fd, buf, count)
    ret
