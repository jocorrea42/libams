global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

section .text

ft_strdup:                   ; Entrada: RDI = const char *s.Guardar el argumento s porque lo necesitaremos luego de llamar a malloc
    mov     rbx, rdi         ; rbx = s, evitar usar la pila para no tener que checkear alineamiento, para luego obtener longitud de la cadena y rdi pueda ser modificado como parametro de ft_strlen
    call    ft_strlen        ; rax = len(s)
    inc     rax              ; incluir '\0', rax = size → malloc(size)
    mov     rdi, rax
    call    malloc           ; rax = ptr destino
    cmp    rax, 0            ; si malloc falla → NULL
    je      .done            ; rax = malloc_ptr, rsi = s
    mov     rsi, rbx         ;  rsi = s, rbx lo utilizo como storage, dado que directamente rsi = rdi, en la linea 9 pudiera en el malloc ser modificaco rsi 
    mov     rdi, rax         ; primer arg para ft_strcpy: dest = ptr
    call    ft_strcpy        ; copia s en malloc'd buffer
.done:
    ret
