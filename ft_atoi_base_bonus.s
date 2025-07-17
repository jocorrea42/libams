; **************************************************************************** ;
; ft_atoi_base_bonus.s
; Convierte una cadena en una representación numérica dada en una base específica
; Parámetros:
;   rdi = puntero a la cadena a convertir (str)
;   rsi = puntero a la cadena que define la base (base)
; Retorna:
;   rax = número convertido (int)
; **************************************************************************** ;

global ft_atoi_base  ; exporta la función
extern ft_strlen          ; función externa para calcular la longitud de cadena

section .text

ft_atoi_base:
    cmp rdi, 0
    je error
    cmp rsi, 0
    je error
    xor r9, r9              ; r9 = contador de signos '-' encontrados, inicia en 0

check_spaces:
    ; Saltar todos los espacios en blanco (y otros caracteres whitespace) en la cadena str
    cmp byte [rdi], ' '     ; si *str == espacio
    je inc_space
    cmp byte [rdi], 9       ; tabulador
    je inc_space
    cmp byte [rdi], 10      ; salto de línea (LF)
    je inc_space
    cmp byte [rdi], 11      ; tabulador vertical
    je inc_space
    cmp byte [rdi], 12      ; salto de página (form feed)
    je inc_space
    cmp byte [rdi], 13      ; retorno de carro (CR)
    je inc_space
    jmp check_signs         ; si no hay espacio, pasar a verificar signos

inc_space:
    inc rdi                 ; avanzar puntero str para ignorar espacio
    jmp check_spaces        ; repetir hasta que no haya espacios

check_signs:
    mov r8b, byte [rdi]     ; cargar carácter actual (posible signo)
    cmp r8b, '+'            ; si es '+'
    je sign_found
    cmp r8b, '-'            ; si es '-'
    je sign_found
    jmp setup_conversion    ; si no es signo, proceder a conversión

sign_found:
    ; Aquí procesamos un signo único
    cmp r8b, '-'            ; si es '-'
    jne plus_sign           ; si no es '-', es '+', saltar a plus_sign
    inc r9                  ; contador de signos '-' incrementa (para detectar signo negativo)

plus_sign:
    inc rdi                 ; avanzar puntero en str para analizar siguiente carácter
    mov r8b, byte [rdi]     ; obtener siguiente carácter
    cmp r8b, '+'            ; si hay otro signo '+' consecutivo -> error
    je error
    cmp r8b, '-'            ; si hay otro signo '-' consecutivo -> error
    je error
    jmp setup_conversion    ; si no hay otro signo, continuar con conversión

setup_conversion:
    mov r10, rdi            ; guardar puntero actual de str (inicio del número real)
    mov rdi, rsi            ; pasar base en rdi para llamar a ft_strlen
    call ft_strlen          ; obtener longitud de base (rax)

    cmp rax, 2              ; la base debe tener al menos 2 caracteres
    jl error                ; si menos de 2, base inválida -> error

    mov rbx, -1             ; inicializar índice para iterar base en -1 para preincrementar

check_base_chars:
    inc rbx                 ; incrementar índice base
    cmp byte [rsi + rbx], 0 ; si fin de cadena base -> ir a convert
    je convert

    mov r8b, [rsi + rbx]    ; obtener carácter actual de la base

    ; Comprobar caracteres prohibidos en la base (signos, espacios, tabs, etc.)
    cmp r8b, '+'
    je error
    cmp r8b, '-'
    je error
    cmp r8b, 9
    je error
    cmp r8b, 10
    je error
    cmp r8b, 11
    je error
    cmp r8b, 12
    je error
    cmp r8b, 13
    je error
    cmp r8b, ' '
    je error

    ; Comprobar que no haya caracteres duplicados en la base
    mov rcx, rbx            ; índice para buscar duplicados a partir del siguiente carácter
check_duplicates:
    inc rcx
    cmp byte [rsi + rcx], 0 ; si fin de base -> no duplicados, continuar con siguiente char base
    je check_base_chars

    cmp r8b, byte [rsi + rcx] ; si se encontró duplicado -> error
    je error

    jmp check_duplicates    ; repetir hasta fin de base

convert:
    xor rbx, rbx            ; índice para iterar la cadena str
    xor rcx, rcx            ; índice para iterar base
    mov r11, rax            ; r11 = longitud de base
    xor rax, rax            ; resultado numérico acumulado

convert_loop:
    mov r8b, [r10 + rbx]    ; obtener carácter actual de str a convertir
    cmp r8b, 0              ; si fin de cadena str -> terminar conversión
    je finish

    xor rcx, rcx            ; índice para buscar carácter en base

find_in_base:
    cmp r8b, [rsi + rcx]    ; comparar carácter str con base[rcx]
    je add_value            ; si coincide, añadir valor
    inc rcx
    cmp byte [rsi + rcx], 0 ; si fin de base y no encontrado -> terminar (carácter inválido)
    je finish
    jmp find_in_base        ; seguir buscando

add_value:
    xor rdx, rdx            ; limpiar rdx antes de multiplicar (mul usa rdx:rax)
    mul r11                 ; rax *= longitud de base
    add rax, rcx            ; rax += índice del carácter en base
    inc rbx                 ; avanzar a siguiente carácter en str
    jmp convert_loop

finish:
    test r9b, 1             ; si contador de signos '-' es impar (LSB == 1)
    jz ret                  ; si par (o cero), número positivo, ir a retorno
    neg rax                 ; si impar, negar resultado para devolver negativo

ret:
    ret                     ; retornar resultado en rax

error:
    xor rax, rax            ; en caso de error, devolver 0
    ret
