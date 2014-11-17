
; This is a sample TOY assembly language program

.DATA

.CODE
	mov R1 1   ; Initialize

	mov R2 1   ; Initialize

	read R5    ; How many fibonacci number do you want?
	
loop:

	print R1   ; Print to standard output

	mov R3 R1  ; Move R1 into a temporary register R3

	add R1 R2  ; add R2 to R1

	mov R2 R3  ; Put R1 into R2
		
	dec R5     ; Decrease index

	jz done    ; If the last operation dec yield zero, the program is done.
		
	jmp loop   ; Continue the loop

done:

