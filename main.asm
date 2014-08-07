[BITS 16]

jmp main

welcome_string db "This is my shitty ass OS that I'ma turn into pong! ", 2, 0
wait_string db "Press, like, literally any key to begin...", 0

%include "io.inc"
%include "pong.inc"

main:
	mov cl, 0x3F
	call clear

	mov dh, 3
	mov dl, 3
	mov cl, 0x3F
	mov si, welcome_string
	call prints

	mov dh, 3
	mov dl, 4
	mov si, wait_string
	call prints

	call get_char_wait
	mov cl, 0x0F
	call clear

	.gameloop:
		mov cl, 0x0F
		call clear
		call draw_all

		mov cx, 50
		call sleep

		.getanother:
		xor ax, ax
		call get_char

		cmp al, 0
		je .end

		cmp al, 'q'
		je .lmove_bat1_up
		cmp al, 'z'
		je .lmove_bat1_down

		cmp al, 'u'
		je .lmove_bat2_up
		cmp al, 'm'
		je .lmove_bat2_down

		jmp .end

			.lmove_bat1_up:
				call move_bat1_up
				jmp .end
			.lmove_bat1_down:
				call move_bat1_down
				jmp .end

			.lmove_bat2_up:
				call move_bat2_up
				jmp .end
			.lmove_bat2_down:
				call move_bat2_down
				jmp .end

		.end:

		call update_ball
	jmp .gameloop

	.stopeet:
	hlt
	jmp .stopeet

	times 512*7-($-$$) db 0 ; just to fill up the floppy