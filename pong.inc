ballx db 40
bally db 12
velx db 1
vely db 1

%define bat1x 1
%define bat2x 78
%define batheight 9

bat1 db 0
bat2 db 0

reset:
	pusha

	mov byte [es:ballx], 40
	; mov byte [es:bally], 12 ; for some randomness

	popa
	ret

update_ball:
	pusha
	call .updatey
	call .updatex
	popa
	ret

	.updatey:
		mov dl, byte [es:vely]
		mov dh, byte [es:bally]

		cmp dl, 0
		jg .ygoindown
		; Goin' up
		dec dh
		cmp dh, 0
		je .yhitt
		jmp .yapply

			.yhitt:
				mov byte [es:vely], 1
			jmp .yapply

		.ygoindown:
		; Goin' down
		inc dh
		cmp dh, 24
		je .yhitb
		jmp .yapply

			.yhitb:
				mov byte [es:vely], 0
			jmp .yapply

		.yapply:
		mov byte [es:bally], dh

		.ydone:
	ret

	.updatex:
		mov dl, byte [es:velx]
		mov dh, byte [es:ballx]

		cmp dl, 0
		jg .xgoinright
		; Goin' left
		dec dh
		cmp dh, bat1x
		je .xhitl
		jl .xmissl

		jmp .xapply

			.xhitl:
				mov cl, byte[es:bally]
				mov ch, byte [es:bat1]
				cmp ch, cl
				jg .xmissl
				add ch, batheight
				cmp ch, cl
				jl .xmissl

				mov byte [es:velx], 1
				mov dh, bat1x+2
			jmp .xapply

			.xmissl: ; increment score plox
				call reset
			jmp .xdone

		.xgoinright:
		; Goin' right
		inc dh
		cmp dh, bat2x
		je .xhitr
		jg .xmissr
		jmp .xapply

			.xhitr:
				mov cl, byte[es:bally]
				mov ch, byte [es:bat2]
				cmp ch, cl
				jg .xmissr
				add ch, batheight
				cmp ch, cl
				jl .xmissr

				mov byte [es:velx], 0
				mov dh, bat2x-2
			jmp .xapply

			.xmissr: ; increment score plox
				call reset
			jmp .xdone

		.xapply:
		mov byte [es:ballx], dh

		.xdone:
	ret


draw_all:
	call draw_bat1
	call draw_bat2
	call draw_ball
	ret

draw_bat1:
	pusha

	mov dh, bat1x
	mov dl, [es:bat1]
	mov cl, 0x0F
	mov ch, 219 ; The block character
	call putc

	xor ax, ax
	mov al, dl
	add al, batheight
	.dloop:
		inc dl
		call putc

		cmp dl, al
	jne .dloop

	popa
	ret


draw_bat2:
	pusha

	mov dh, bat2x
	mov dl, [es:bat2]
	mov cl, 0x0F
	mov ch, 219 ; The block character
	call putc

	xor ax, ax
	mov al, dl
	add al, batheight
	.dloop:
		inc dl
		call putc

		cmp dl, al
	jne .dloop


	popa
	ret

draw_ball:
	pusha

	mov dh, [es:ballx]
	mov dl, [es:bally]
	mov cl, 0x07
	mov ch, 219 ; The block character
	call putc

	popa
	ret

move_bat1_up:
	pusha
	mov al, byte [es:bat1]
	or al, al
	jz .end

	dec byte [es:bat1]

	.end:
	popa
	ret

move_bat1_down:
	pusha
	mov al, byte [es:bat1]
	add al, batheight
	cmp al, 24
	je .end

	inc byte [es:bat1]

	.end:
	popa
	ret

move_bat2_up:
	pusha
	mov al, byte [es:bat2]
	or al, al
	jz .end

	dec byte [es:bat2]

	.end:
	popa
	ret

move_bat2_down:
	pusha
	mov al, byte [es:bat2]
	add al, batheight
	cmp al, 24
	je .end

	inc byte [es:bat2]

	.end:
	popa
	ret