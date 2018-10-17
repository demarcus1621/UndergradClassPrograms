; template to start a new project 
; 12/29/2017 Saad Biaz
INCLUDE Irvine32.inc
.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
	myString BYTE "Hello World",0dh,0ah
	
.code
main proc
	mov	edx,OFFSET myString
	call WriteString
	; Start writing your code for your assignment

	Start: mov AL, 0Fh 
	call E1_Start
	mov AL, 94h
	call E2_Start
	mov AL, 44h
	call E3_Start
	call E4_Start
	mov AL, 0Ah
	call E5_Start
	call E6_Start
	jmp finish

	; Exercise 1
	E1_Start: mov CL, 0Ah
	mov DL, AL
	cmp CL, AL
	jbe G_T
	or DL, 30h
	ret
	G_T: add dl, 37h
	ret
	
	; Exercise 2
	E2_Start: mov DH, AL
	mov DL, AL
	shr DH, 4
	or DH, 30h
	mov AL, DH
	call WriteChar
	and DL, 0Fh
	or DL, 30h
	mov AL, DL
	call WriteChar
	mov AL, 68h
	call WriteChar
	mov AL, 0Ah
	call WriteChar
	mov AL, 0Dh
	call WriteChar
	ret

	; Exercise 3
	E3_Start: mov DL, AL
	mov CL, 41h
	cmp CL, DL
	jbe G_T2
	and dl, 0Fh
	ret
	G_T2: and dl, 0Fh
	add dl, 09h
	ret

	; Exercise 4
	E4_Start: call ReadChar
	call E3_Start
	mov DH, DL
	call ReadChar
	shl DH, 4
	call E3_Start
	mov AL, DH
	or AL, DL
	ret

	; Exercise 5
	E5_Start: mov CL, AL
	mov CH, 00h
	mov DX, 0000h
	LP: add DX, CX
	loop LP
	ret

	; Exercise 6
	E6_Start: call E4_Start
	call E5_Start
	mov BX, DX
	mov DH, BH
	shr DH, 4
	mov AL, DH
	call E1_Start
	mov AL, DL
	call WriteChar
	mov DL, BH
	and DL, 0Fh
	mov AL, DL
	call E1_Start
	mov AL, DL
	call WriteChar
	mov DH, BL
	shr DH, 4
	mov AL, DH
	call E1_Start
	mov AL, DL
	call WriteChar
	mov DL, BL
	and DL, 0Fh
	mov AL, DL
	call E1_Start
	mov AL, DL
	call WriteChar
	mov AL, 68h
	call WriteChar
	mov AL, 0Ah
	call WriteChar
	mov AL, 0Dh
	call WriteChar
	ret

	finish: invoke ExitProcess,0
main endp
end main