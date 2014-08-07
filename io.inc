clear: ; cl - clear color
	pusha
	xor bx, bx
	.go:
		mov byte [gs:bx], ' '
		inc bx
		mov byte [gs:bx], cl
		inc bx
		cmp bx, 25*80*2
		jge .done
	jmp .go

	.done:

	popa
	ret

putc: ; ch - character, cl - color, dx - xy
	pusha

	mov bx, dx	; bx = dx -- because the mul can mess with the dx register
	mov ax, 80	; ax = 80

	push bx
	and bx, 0xFF; to get y
	mul bx		; ax *= bx
	pop bx

	shr bx, 8
	and bx, 0xFF
	add ax, bx	; al += bh
	shl ax, 1	; ax *= 2

	mov bx, ax	; bx = ax

	xchg cl, ch
	mov [gs:bx], cx

	popa
	ret

prints: ; si - string, dh - x, dl - y, cl - color
	pusha

	mov bx, dx	; bx = dx -- because the mul can mess with the dx register
	mov ax, 80	; ax = 80
	mul bl		; ax *= bl
	add al, bh	; al += bh
	shl ax, 1	; ax *= 2

	mov bx, ax	; bx = ax

	.go:
		mov al, [es:si]
		mov ah, cl
		mov [gs:bx], ax
		inc bx
		inc bx
		inc si

		cmp byte [es:si], 0
		je .done
	jmp .go
	.done:

	popa
	ret

get_char: ; non block
	mov ah, 1
	int 16h
	jz .done

	xor ax, ax
	int 16h

	.done:
	ret

get_char_wait: ; blocks
	xor ax, ax
	int 16h
	ret

sleep: ; cx millis
	pusha
	; cx m -> cx:dx u
	xor dx, dx
	mov ax, cx
	mov cx, 1000
	mul cx
	xchg ax, dx
	mov cx, ax
	; xor al, al
	mov ah, 86h
	int 15h

	popa
	ret

get_time:
	push ax
	push cx

	mov ah, 0
	int 1Ah ; cx:dx = ticks since midnight; 18.20648 ticks per second

	pop cx ; only return low byte
	pop ax
	ret