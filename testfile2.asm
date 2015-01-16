.data
	var1 1000
	var2 0x1
	var3 0x2
.code

; Dummy....
Label1:	and R4,RB,R1
		jr  RF
Label2: ld R1 1
		ld R2 0x1
		bz R1 Label3
Label3:
		;whatever
