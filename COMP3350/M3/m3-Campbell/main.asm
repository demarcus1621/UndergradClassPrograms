; template to start a new project 
; 12/29/2017 Saad Biaz
; 9/27/2018 Demarcus Campbell
; Module 3 Programming Assignment

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

	mov eax,0fffdh
	inc eax
	inc eax
	inc eax
	mov eax,0fffdh
	inc al
	inc al
	inc al

	invoke ExitProcess,0
main endp
end main