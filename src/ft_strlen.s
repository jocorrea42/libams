global ft_strlen
section .text

ft_strlen:
	xor rax, rax        ; contador = 0

.count:
	cmp byte [rdi + rax], 0  ; si str[rax] == 0 => fin
	je .done
	inc rax
	jmp .count

.done:
	ret
