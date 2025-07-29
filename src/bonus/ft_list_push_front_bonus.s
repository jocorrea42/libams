global ft_list_push_front
extern malloc
;GOT(Global Offset Table) es una estructura usada en programas ELF (como en Linux) 
;permite que el código pueda acceder a funciones y variables globales ubicadas en direcciones desconocidas en tiempo de compilación. 
section .text

ft_list_push_front:
	cmp rdi, 0
	je ret_null
	push rsi
	push rdi
	sub rsp, 8              ; alineación para call
	mov rdi, 16               ; malloc(sizeof(t_list)) → 16 bytes (8 bytes para `data`, 8 para `next`)
    call [rel malloc wrt ..got] ; Llamada a malloc de forma PIE-safe a través de la GOT al no poder compilar el main con -no-pie
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
