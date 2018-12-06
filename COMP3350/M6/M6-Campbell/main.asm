; template to start a new project 
; 12/29/2017 Saad Biaz
; Demarcus Campbell, Ian Brown, Philip Jauregui
INCLUDE Irvine32.inc
.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
	; Exercise 1
	myString BYTE "Hello World",0dh,0ah
	StringBuffer BYTE 21 dup(?)

	; Exercise 2
	prompt1 BYTE "Please enter a sentence: ",0
	prompt2 BYTE "Please enter a character: ", 0
	str1 BYTE 21 dup(?)
	compareChar BYTE ?
	
	; Exercise 3
	prompt3 BYTE 0dh,0ah,"Please enter the first sentence: ", 0
	prompt4 BYTE "Please enter the second sentence: ", 0
	sen1 BYTE 21 dup(?)
	sen2 BYTE 21 dup(?)
	concatBuffer BYTE 41 dup(?)

.code
main proc
	mov	edx,OFFSET myString
	call WriteString
	; Start writing your code for your assignment
	call Exercise1
	call Exercise2
	call Exercise3
	invoke ExitProcess,0
main endp

Exercise1 proc
	mov edx, OFFSET stringBuffer ; Prepares for usage of readString function
	mov ecx, SIZEOF stringBuffer
	call readString
	call writeDec  ; readString stores the length of input string into EAX
	push eax   ; Use stack to save value of length while printing line feed characters
	mov eax, 0Dh
	call writeChar
	mov eax, 0Ah
	call writeChar
	pop eax    ; Retrieve value of length from stack
	call writeHex
	mov eax, 0Dh
	call writeChar
	mov eax, 0Ah
	call writeChar
	ret
Exercise1 endp

Exercise2 proc
	mov edx, OFFSET prompt1
	call writeString
	mov edx, OFFSET str1
	mov ecx, SIZEOF str1
	call readString
	push eax ; Use the stack to save the length of the string, this will be used later
	mov edx, OFFSET prompt2
	call writeString
	call readChar
	mov ebx, 0h
	mov edi, OFFSET str1
	pop ecx  ; Retrieve string size from the stack and set the loop register
looper:
	repne scasb
	jcxz ender
	inc ebx
	jmp looper
ender:
	jnz Next
	inc ebx
Next:
	mov eax, ebx
	call writeDec
	ret
Exercise2 endp

Exercise3 proc
	mov edx, OFFSET prompt3
	call writeString
	mov edx, OFFSET sen1
	mov ecx, SIZEOF sen1
	call readString
	push eax
	mov edx, OFFSET prompt4
	call writeString
	mov edx, OFFSET sen2
	mov ecx, SIZEOF sen2
	call readString
	pop ecx
	push ecx
	mov esi, OFFSET sen1
	mov edi, OFFSET concatBuffer
	rep movsb 
	mov ecx, eax
	mov esi, OFFSET sen2
	rep movsb
	mov edx, OFFSET concatBuffer
	call writeString
	pop ecx
	add eax, ecx
	call writeDec
	push eax
	mov eax, 0ah
	call writeChar
	mov eax, 0dh
	call writeChar
	pop eax
	call writeHex
	ret
Exercise3 endp
end main