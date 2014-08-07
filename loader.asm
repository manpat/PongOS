[BITS 16]
[ORG 0]

	jmp 07C0h:start     ; Goto segment 07C0

start:
	; Update the segment registers
	mov ax, cs
	mov ds, ax
	mov es, ax

reset:                      ; Reset the floppy drive
	mov ax, 0           ;
	mov dl, 0           ; Drive=0 (=A)
	int 13h             ;
	jc reset            ; ERROR => reset again

read:
	mov ax, 1000h       ; ES:BX = 1000:0000
	mov es, ax          ;
	mov bx, 0           ;

	mov ah, 2           ; Load disk data to ES:BX
	mov al, 5           ; Load 5 sectors
	mov ch, 0           ; Cylinder=0
	mov cl, 2           ; Sector=2
	mov dh, 0           ; Head=0
	mov dl, 0           ; Drive=0
	int 13h             ; Read!

	jc read             ; ERROR => Try again

	mov al, 'a'
	mov ah, 0Eh     ; Print AL
	mov bx, 7
	int 10h
	
	mov dh, 26
	mov dl, 81
	mov bh, 0
	mov ah, 2
	int 10h ; move cursor offscreen

	mov ax, 0xb800
	mov gs, ax ; Graphics segment ;D

	jmp 1000h:0000      ; Jump to the program

	times 510-($-$$) db 0
	dw 0AA55h
