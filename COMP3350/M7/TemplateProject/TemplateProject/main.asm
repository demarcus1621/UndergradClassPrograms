; template to start a new project 
; 12/29/2017 Saad Biaz
INCLUDE Irvine32.inc
.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
	myString BYTE "Hello World",0dh,0ah
	myBuffer BYTE  21 dup(?)
	
.code
main proc
	mov	edx,OFFSET myString
	call WriteString
	; Start writing your code for your assignment
	call exec1

	invoke ExitProcess,0
main endp

exec1 proc
	mov ecx SIZEOF myBuffer
	mov edx OFFSET myBuffer
	call ReadString
	
	ret
exec1 enp

end main