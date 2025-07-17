; ft_read.s
; ssize_t ft_read(int fd, void *buf, size_t count)

global ft_read
extern __errno_location        ; acceso a errno

section .text

ft_read:
    mov     rax, 0             ; syscall number for read
    syscall                    ; ejecuta syscall: read(fd, buf, count)

    cmp     rax, 0             ; compara si la syscall falló (rax < 0)
    jl      .error             ; si es negativo (JL = Jump if Less), ir a manejar error

    ret                        ; si éxito, simplemente retorna

.error:
    neg     rax                ; convierte error negativo a positivo para errno
    mov     rdi, rax
    call    __errno_location   ; devuelve dirección de errno
    mov     [rax], edi         ; guarda errno
    mov     rax, -1            ; valor de retorno estándar en caso de error
    ret
