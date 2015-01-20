INRR  
DCRR  
INRM 
DCRM
NOP
MOVRR
MOVMR
MOVRM
ADD  
ADC 
SUB 
SBB 
AN
XR 
OR
CMP
RLI
RRI
PUSH
POP
MVIR 
MVIM
ADI  
ACI   
SUI   
SBI  
ANI 
XRI 
ORI 
CPI
OUI
For
Direct Addressing Instructions
Mnemoic Description
STA
LDA
JMP ADDR Jump to location ADDR
JC ADDR Jump to ADDR if Carry set
JNC ADDR Jump to ADDR if Carry not set
JZ ADDR Jump to ADDR if Zero set
JNZ ADDR Jump to ADDR if Zero not set
JG ADDR Jump to ADDR if Greater set
JNG ADDR Jump to ADDR if Greater not set
JE ADDR Jump to ADDR if Equal set
JNE ADDR Jump to ADDR if Equal not set
JL ADDR Jump to ADDR if Less set
JNL ADDR Jump to ADDR if Less not set
JP Jump to ADDR if Sign set (positive)
JM Jump to ADDR if Sign not set (negative)
Call Instructions
Mnemoic Description
CALL ADDR Call subroutine and push return address to stack
CC ADDR Call subroutine if Carry set
CNC ADDR Call subroutine if Carry not set
CZ ADDR Call subroutine if Zero set
CNZ ADDR Call subroutine if Zero not set
CG ADDR Call subroutine if Greater set
CNG ADDR Call subroutine if Greater not set
CE ADDR Call subroutine if Equal set
CNE ADDR Call subroutine if Equal not set
CL ADDR Call subroutine if Less set
CNL ADDR Call subroutine if Less not set
CP Call subroutine if Sign set (positive)
CM Call subroutine if Sign not set (negative)
Return Instructions
Mnemoic Description
RET Return from subroutine
RC Return from subroutine if Carry set
RNC Return from subroutine if Carry not set
RZ Return from subroutine if Zero set
RNZ Return from subroutine if Zero not set
RG Return from subroutine if Greater set
RNG Return from subroutine if Greater not set
RE Return from subroutine if Equal set
RNE Return from subroutine if Equal not set
RL Return from subroutine if Less set
RNL Return from subroutine if Less not set
RP Return from subroutine if Sign set (positive)
RM Return from subroutine if Sign not set (negative)
I/O Instructions
Mnemoic Description
IN RD, DEV Read a word from device to a register
OU DEV, RD Send a word to device from a register
Halt Instruction
Mnemoic Description
HLT
