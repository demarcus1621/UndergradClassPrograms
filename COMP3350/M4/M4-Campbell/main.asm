; template to start a new project 
; 12/29/2017 Saad Biaz
; DeMarcus Campbell
; Ian Brown
; Phillip Jauregui
; 10/4/18
; Module 4 Programming Assignment

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

	; Exercise 1
	; Converts value in AL to ASCII equivalent and prints
	mov al, 09h
	mov dl, al
	or dl, 30h
	mov al, dl
	call WriteChar
	mov al, 0dh
	call WriteChar
	mov al, 0ah
	call WriteChar

	; Exercise 2
	; Converts Hexadecimal value to ASCII and prints the number
	mov al, 74h
	mov dh, al
	mov dl, al
	and dh, 0F0h
	shr dh, 4
	or dh, 30h
	mov al, dh
	call WriteChar
	and dl, 0Fh
	or dl, 30h
	mov al, dl
	call WriteChar
	mov al, 68h
	call WriteChar
	mov al, 0Ah
	call WriteChar
	mov al, 0Dh
	call WriteChar

	; Exercise 3
	; Takes in a decimal(base-10) digit and stores the value in AL
	call ReadChar
	mov dl, al
	and dl, 0fh

	; Exercise 4
	; Takes in a 2-digit decimal number and stores the value in AL
	call ReadChar
	mov dh, al
	call ReadChar
	mov dl, al
	and dh, 0fh
	and dl, 0fh
	shl dh, 4
	mov al, dh
	or al, dl

 	invoke ExitProcess,0
main endp
end main 