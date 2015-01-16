
.data
	Array DWORD DUP(4)
	VAR WORD 1023
.code
start:
	add R1,R2,R3

	jl RF, start
end:
	xor R2,R3,R4
	jl RF, end
