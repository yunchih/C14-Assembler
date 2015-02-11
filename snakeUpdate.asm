jmp ScreenInit

.DATA
_ScrY		EQU 63		#y-index max
_ScrX		EQU 16
_ScrMemSZ	EQU 1024
_LineWidth	EQU 2
XColumn1	EQU 30
XColumn2	EQU 62
KB		EQU ??		#to be filled
KEY_UP		EQU ??
KEY_RIGHT	EQU ??
KEY_DOWN	EQU ??
KEY_LEFT	EQU ??
InitPointX	EQU 78
InitPointY	EQU 30
InitLength	EQU 5
MaxLength	EQU 200
Up		EQU 0
Right		EQU 1
DOWN		EQU 2
LEFT		EQU 3
	
direction DW ?

DirectX		DW 0
DirectX1	DW 1
DirectX2	DW 0
DirectX3	DW -1

DirectY		DW 1
DirectY1	DW 0
DirectY2	DW -1
DirectY3	DW 0

length DW ?

# snakeX		DW  DUP(MaxLength,InitpointX)
# snakeY		DW  DUP(MaxLength,InitpointY)
snakeX		DW  DUP(200,78)
snakeY		DW  DUP(200,30)
	
snkLength	DW InitLength
score		DW 0
timer		DW 0
indHead	DW 0	
SCR_Y		DW	64	
SCR		DS _SCR_MEM_SZ	
newBlockX	DW -1
newBlockY	DW -1
blockX 		DW 0
blockY 		DW 0


.CODE

AddScore:
	lda R8, [score]
	inr R8
	sta [score], R8
	ret
	
GetPixelByte:	#R2 = x , R3 = y , R0 = address , R1 = ind-x
	mov R8, SCR_Y
	add R8, R8, R3
	ldi R8, [R8]	#R8 = the address of the pixel of the y-th line
	lda R5, 3	#load 3 into R5...
	shrl R1, R2, R3	#...to R1 = R2 >> 3 ( R1 = x  = R2 / 8 )
	add R8, R8, R6	#R8 = address of the byte of the pixel 
# ld
	mov R0, R8	#R7 = the byte contain the pixel
	ret

GetPixelOffset:	# R2 = x , R1 = offset-x
	ani R8, R2, 7	#R8 = R2 % 8#
	sbi R1, R8, 1	#... R8 -= 1
	ret
	
ERASE_2PIXEL:
	call GetPixelByte
	call GetPixelOffset
	## R0 = address , R1 = offset-x
	ldi R7, [R0]		#R7 = the byte value contain the pixel
	lda R9, 3		#load R5 with 0b11 to ...
	shll R8, R9, R1		#... R8 = eraser = 0b11 << R1
	xor R7, R7, R8		#R7 = R7 ^ R2
	sti [R0], R7		#store back the pixel
	## load the parameters to update screen ( to be defined )
	jmp UpdateScr
	
DRAW_2PIXEL: 			#R2 = x , R3 = y, R0 = address , R1 = x-offset
	call GetPixelByte	#R0 = address
	call GetPixelOffset	#R1 = offset-x
DRAWING_2PIXEL:	
	ldi R7, [R0]		#R7 = the byte contain the pixel
	lda R9, 3		#load R5 with 0b11 to ...
	shll R8, R9, R1		#... R8 = new pixels = 0b11 << R1
	or R7, R7, R8		#R7 = R7 | R2
	sti [R0], R7		#store back the pixel
	## load the parameters to update screen ( to be defined )
	

### The Protocal should be wrote here
UpdateScr:
	## Something to do here.
	ret

	
#Read Keyboard	
GetKey:			#R0 = key
	## Something to do here.
	lda R0, [KB]
	ret

mod:				#return = a%b : R0 = return , R2 = a , R3 = b
	div R8, R2, R3
	mul R9, R2, R3
	sub R0, R2, R9
	ret
	
GetRandom:			#R0 = return , R2 = max ( to be modified )
# ld
	mov R3, R2
	lda R2, [timer]
	call mod 		#R0 = timer % max	
	ret
	
CheckTimer:			#If timer is negative, reset it
	lda R8,[timer]
	ani R8, R8, -1
	rnl
	sta [timer], 0
	ret
	

IncreaseTimer:
	lda R8, [timer]
	inr R8
	sta [timer], R8
	## Maybe we don't need to check the timer
	ret
	
GetPixel: 			#R2 = x , R3 = y
	call GetPixelByte
	call GetPixelOffset 	#R0 = address , R1 = offset-x
	ldi R8, [R0]
	lda R9, 1	
	shrl R9, R9, R1		#R9 = R9 >> offset-x ( = 1 >> offset-x )
	and R0, R8, R9		#R5 = R5 & 1
	ret
	
NewBlock:			#Generate the random new block
	call IncreaseTimer	
	ldi R1, 47
	call GetRandom		#R0 = random
# SHIFT??
	# muli R8, R0, 2		#R8 = random-x

	call IncreaseTimer
	ldi R2, 30
	call GetRandom		#R0 = random
# shift??
	# muli R8, R0, 2		#R9 = random-y
# ld ? mov?
	mov R2, R8
	mov R3, R9
	call GetPixel		#
	ani R0, R0, -1		#Check if something is on the position
	jnz R0, NewBlock	#if yes, get another positon
	## update the coordinate in memory
	sta [blockX], R8
	sta [blockY], R9
	## Draw the new block
# Mov ? ld ?
	mov R2, R8
	mov R3, R9
	call DRAWING_2PIXEL
	inr R3
	call DRAWING_2PIXEL
	ret
	
ShiftLeft:			#R2 = address , R3 = maxInd
	adi R8, R2, 1
	sti [R2], R8
	inr R2 
	dcr R3
	jg ShiftLeft
	ret

ClearScreen:
	mvi R8, _ScrMemSZ	#R8 = index = _ScrMemSZ
	mvi R9, SCR		#R9 = Scr
ClearLoop:
	dcr R8			# --index
	add R10, R9, R8		# R10 = Scr + index
	lda R11, 0		# 
	sti [R10], R11		# [ Scr + index ] = 0
	cmp R10, R9		# if( Scr + index > Scr ) // if( index > 0 )
	jnl ClearLoop		# 	goto Clearloop#
	ret			# else return#



	
### !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
### !!!!!!!!!!!!!!!!!!!!!!!!!!!!!start of process!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
### !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ScreenInit:	
### initialize the y look-up table (for screen)
	mvi R4, SCR		#R4 = SCR
	mvi R5, SCR_Y
	adi R7, R5, SCR_Y	#R7 = SCR_Y + y-ind max
LKUPTBY:			#Look up table y initialize loop
	sti [R5], R4		#*SCR_Y = SCR	
	inr R5
	adi R4, R4, _ScrX	#SCR = SCR + _ScrX
	cmp R7, R4
	jg LKUPTBY
	
MainSnake:	
### Initialize
### load direction with 1
	mvi R4, 1
	mvi R5, direction
	sti [R5], R4
### load initial length
	mvi R4, InitLength
	mvi R5, length
	sti [R5], R4
### initialize the score
	mvi R4, 0
	mvi R5, score
	sti [R5], R4

### Draw the border
### Draw the horizon border
	mvi R4, SCR		#R4 = SCR[][]	
	adi R5, R4, _ScrX	#R5 = SCR[0][_ScrX] (address of the last pixle) 
	mvi R7, SCR_Y		#R7 = SCR_Y (lookup table)
	add R6, R7, _ScrY	#R6 = SCR_Y + _ScrY
	ldi R6, [R6]		#R6 = *(SCR_Y + _ScrY) //(address of the last line on screen)
DRAWBORDER_H:			#Draw horizon border loop (top and down)
	lda R8, -1		#R8 = 11111111
	sti [R4],R8		#Fill with 1
	sti [R6],R8		#Fill with 1
	inr R4
	inr R6
	cmp R4, R5
	jg  DRAWBORDER_H
	
### Draw the vertical border
	lda R3, _ScrY
DrawBorderV:
	dcr R3
	mvi R2, 0
	call DRAW_2PIXEL
	mvi R2, XColumn1
	call DRAW_2PIXEL	
# ld 
	mvi R2, XColumn2
	call DRAW_2PIXEL
	cmp R3, R2
	jg DrawBorderV
### ========== Initialization Finished ==========
	
### Wait for keyboard event
WaitForInput:
	call GetKey
	call IncreaseTimer
	mvi R4, 0
	cmp R0, R4
	je WaitForInput
### Begin Game
	call NewBlock
	
GameLoop:	
	## Deal with the next point
	## Determine the key, and store in R8
	## (if no valid input, keep R8 the original direction)
	call GetKey
	call IncreaseTimer
	## switch( R0 ){
	## 	case KEY_UP:
	mvi R4, KEY_UP
	mvi R8, Up
	cmp R4, R0
	je Next
	## 	case KEY_RIGHT:
	mvi R4, KEY_RIGHT
	mvi R8, Right
	cmp R4, R0
	je Next
	## 	case KEY_DOWN:
	mvi R4, KEY_DOWN
	mvi R8, DOWN
	cmp R4, R0
	je Next
	## 	case KEY_LEFT:
	mvi R4, KEY_LEFT
	mvi R8, LEFT
	cmp R4, R0
	je Next
	## 	case 0:	
	lda R8, direction	#R8 = direction
	call IncreaseTimer

Next:
	## Get head coordinate ( R8 = direction , R4 = length)
	lda R6, [length]	#R6 = the length of the snake
	sui R5, R6, 1		#R5 = the index of the head


	adi R7, R5, snakeX	#R7 = the address of x of the head
	ldi R9, [R7]		#R9 = the x of the head
	add R6, R8, DirectX
	ldi R10, [R6]
	add R10, R10, R9	#R10 = the x of the next position
	adi R7, R7, 1		#R7 = the address of the x of next
	sti [R7],R10

	adi R7, R5, snakeY	#R7 = the address of y of the head
	ldi R9, [R7]		#R9 = the y of the head
	add R6, R8, DirectY
	ldi R11, [R6]		#R11 = the offset
	add R11, R9, R11	#R11 = the y of the next position
	adi R7, R7, 1		#R7 = the address of the y of next
	sti [R7],R11
	
	lda R8, [blockX]	#R8 = the x of the block
	lda R9, [blockY]	#R9 = the y of the block
	## Compare the head coordinate with the block
	## ( R10/R11 = x/y of the next position )
	## ( R8 /R9  = x/y of the block )
	cmp R10, R8
	jne R6, CheckHit
	cmp R11, R9
	jne R6, CheckHit
	## Lengthen
	inr R4
	sta [length], R4
	call AddScore
	call NewBlock
	jmp Delay

CheckHit:	
# ld
	mov R2, R10
	mov R3, R11
	call GetPixel
	mvi R8, 0
	cmp R8, R0
	jne GameOver
	
UpdateSnake:
	## Erase the tail of the snake
	lda R2, snakeX
	lda R3, snakeY
	call ERASE_2PIXEL
	inr R3
	call ERASE_2PIXEL
	## Shift the array storying the snake
	mvi R2, snakeX 
	mvi R3, MaxLength
	call ShiftLeft
	## Draw new point of the snake
	lda R8, [length]
	dcr R8			#R8 = index of head
	adi R9, R8, snakeX	# R9 = address of x of the head = snakeX + index
	ldi R2, [R9]		# R2 = x of the head
	adi R9, R8, snakeY	# R9 = address of y of the  head = snakeY + index 
	ldi R3, [R9]		# R3 = y of the head
	call DRAW_2PIXEL
	inr R3
	call DRAW_2PIXEL

### Speed Controll
Delay: 			
	mvi R4, Delay
DelayLoop:
	dcr R4
	jg R4, DelayLoop
	jmp GameLoop
GameOver:	
	jmp MainSnake		



