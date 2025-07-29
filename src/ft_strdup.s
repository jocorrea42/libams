global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy
;PIE (Position Independent Executable) no pueden usar direcciones absolutas, porque se cargan en direcciones aleatorias (por seguridad → ASLR).
;ejemplo de -no-pie de dir absoluta-> mov rdi, msg  ; Aquí `msg` será resuelto como una dirección absoluta por el ensamblador
section .text
;ejemplo de direccion relativa para PIE lea rdi, [rel msg] ; Dirección relativa al IP → PIE-safe
ft_strdup:
    mov     rbx, rdi             ; rbx = s
    call    ft_strlen            ; rax = len(s)
    inc     rax                  ; incluir '\0'
    mov     rdi, rax             ; malloc(size)
    call    malloc wrt ..plt     ; PIE-safe llamada a malloc ()
    cmp     rax, 0               ; si malloc falla → NULL
    je      .done
    mov     rsi, rbx             ; rsi = s
    mov     rdi, rax             ; rdi = malloc'd buffer
    call    ft_strcpy            ; copiar string
.done:
    ret
