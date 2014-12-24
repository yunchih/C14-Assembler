
.data
	var1 0x02
	var2 10
	var3 100
.code

start:
	ld R1, var1
	ld R2, var2
	ld R3, var3
	jl RF, multiply
	st RD, 0xFF
	hlt

	
	
