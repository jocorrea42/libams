global ft_list_sort

section .text

; void ft_list_sort(t_list **begin_list, int (*cmp)());
; rdi = t_list **begin_list
; rsi = int (*cmp)(void*, void*)

ft_list_sort:
    push rbp
    mov rbp, rsp
    sub rsp, 1             ; espacio para swapped (1 byte)

    mov r10, rsi           ; r10 = cmp function pointer
    mov r11, [rdi]         ; r11 = *begin_list (head)

.loop_start:
    mov byte [rbp - 1], 0  ; swapped = 0
    mov rcx, r11           ; rcx = current node

.loop_inner:
    cmp rcx, 0
    je .check_swapped

    mov rdx, [rcx + 8]     ; rdx = current->next
    cmp rdx, 0
    je .check_swapped

    ; call cmp(current->data, next->data)
    mov rdi, [rcx]         ; current->data
    mov rsi, [rdx]         ; next->data

    ; Guardar registros usados por llamada
    push rcx
    push rdx
    push r10

    call r10               ; cmp(rdi, rsi)

    ; Restaurar registros
    pop r10
    pop rdx
    pop rcx

    cmp eax, 0
    jle .no_swap

    ; swap data
    mov r8, [rcx]
    mov r9, [rdx]
    mov [rcx], r9
    mov [rdx], r8

    mov byte [rbp - 1], 1  ; swapped = 1

.no_swap:
    mov rcx, rdx
    jmp .loop_inner

.check_swapped:
    cmp byte [rbp - 1], 1
    je .loop_start

    leave
    ret
