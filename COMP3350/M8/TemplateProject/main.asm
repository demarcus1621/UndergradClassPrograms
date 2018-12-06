; template to start a new project 
; 12/29/2017 Saad Biaz
INCLUDE Irvine32.inc
.386
.model flat,stdcall
.stack 4096
ExitProcess proto,dwExitCode:dword

.data
	myPrompt BYTE "Please enter a 64-bit hexadecimal(8 bytes).", 0
	fprompt BYTE "Enter the most significant 32 bits: ",0
	sprompt BYTE "Enter the least significant 32 bits: ",0
	var1high DWORD ?
	var1low DWORD ?
	var2high DWORD ?
	var2low DWORD ?
	resHigh DWORD ?
	resLow DWORD ?
	resCarry DWORD ?
	
.code
main proc
	call exercise1
	call exercise2
	invoke ExitProcess,0
main endp

newLine proc
push eax
mov al, 0dh
call WriteChar
mov al, 0ah
call WriteChar
pop eax
ret
newLine endp

exercise1 proc
	push edx
	push eax
	xor eax, eax
	xor edx, edx
	mov edx, OFFSET myPrompt
	call WriteString
	call newLine
	mov edx, OFFSET fprompt
	call WriteString
	call ReadHex
	mov var1high, eax
	mov edx, OFFSET sprompt
	call WriteString
	call ReadHex
	mov var1low, eax
	mov edx, OFFSET myPrompt
	call WriteString
	call newLine
	mov edx, OFFSET fprompt
	call WriteString
	call ReadHex
	mov var2high, eax
	mov edx, OFFSET sprompt
	call WriteString
	call ReadHex
	mov var2low, eax
	add eax, var1low
	mov resLow, eax
	mov eax, var2high
	adc eax, var1high
	mov resHigh, eax
	jnc printer
	xor eax, eax
	adc al, 0
	call WriteHex
printer:
	mov eax, resHigh
	call WriteHex
	mov eax, resLow
	call WriteHex
	call newLine
	pop eax
	pop edx
	ret
exercise1 endp

exercise2 proc

ret
exercise2 endp

exercise3 proc
ret
exercise3 endp
end main