global ft_list_push_front
extern malloc

section .text

ft_list_push_front:
	cmp rdi, 0
	je ret_null
	push rsi
	push rdi
	sub rsp, 8              ; alineación para call
	mov rdi, 16             ; malloc(sizeof(t_list))
	call [rel malloc wrt ..got]
	add rsp, 8
	cmp rax, 0
	je cleanup
	pop rdi                 ; **begin_list
	pop rsi                 ; *data
	mov [rax], rsi          ; new->data = data
	mov rdx, [rdi]          ; rdx = *begin_list
	mov [rax + 8], rdx      ; new->next = *begin_list
	mov [rdi], rax          ; *begin_list = new
	ret

cleanup:
	add rsp, 16             ; limpiar lo que se había hecho push (si malloc falló)
ret_null:
	xor rax, rax
	ret
