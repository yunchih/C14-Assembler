#include "instructionTable.hpp"
Op_table op_table;
Size_table size_table;
Shift_table shift_table;
void initialize_op_table(){
   op_table[  "INR" ] = 0x10;
   op_table[  "DCR" ] = 0x11;
   op_table[ "INRM" ] = 0x12;
   op_table[ "DCRM" ] = 0x13;
   op_table[  "LDI" ] = 0x1A;
   op_table[  "STI" ] = 0x19;
   op_table[  "MOV" ] = 0x14;
   op_table[ "MOVR" ] = 0x15;
   op_table[ "MOVM" ] = 0x16;
   op_table[  "ADD" ] = 0x01;
   op_table[  "ADC" ] = 0x02;
   op_table[  "SUB" ] = 0x03;
   op_table[  "SBB" ] = 0x04;
   op_table[  "AND" ] = 0x05;
   op_table[  "XOR" ] = 0x06;
   op_table[   "OR" ] = 0x07;
   op_table[   "NT" ] = 0x08;
   op_table[  "CMP" ] = 0x09;
   op_table[ "SHLA" ] = 0x0A;
   op_table[ "SHRA" ] = 0x0B;
   op_table[ "SHLL" ] = 0x0C;
   op_table[ "SHRL" ] = 0x0D;
   op_table[  "MUL" ] = 0x60;
   op_table[  "DIV" ] = 0x62;
   op_table[ "MULI" ] = 0x61;
   op_table[ "DIVI" ] = 0x63;
   op_table[  "RLI" ] = 0x64;
   op_table[  "RRI" ] = 0x50;
   op_table[ "CALL" ] = 0x50;
   op_table[   "CC" ] = 0x51;
   op_table[  "CNC" ] = 0x52;
   op_table[   "CZ" ] = 0x53;
   op_table[  "CNZ" ] = 0x54;
   op_table[   "CG" ] = 0x55;
   op_table[  "CNG" ] = 0x56;
   op_table[   "CE" ] = 0x57;
   op_table[  "CNE" ] = 0x58;
   op_table[   "CL" ] = 0x59;
   op_table[  "CNL" ] = 0x5A;
   op_table[   "CP" ] = 0x5B;
   op_table[   "CM" ] = 0x5C;
   op_table[  "RET" ] = 0x40;
   op_table[   "RC" ] = 0x41;
   op_table[  "RNC" ] = 0x42;
   op_table[   "RZ" ] = 0x43;
   op_table[  "RNZ" ] = 0x44;
   op_table[   "RG" ] = 0x45;
   op_table[  "RNG" ] = 0x46;
   op_table[   "RE" ] = 0x47;
   op_table[  "RNE" ] = 0x48;
   op_table[   "RL" ] = 0x49;
   op_table[  "RNL" ] = 0x4A;
   op_table[   "RP" ] = 0x4B;
   op_table[   "RM" ] = 0x4C;
   op_table[  "JMP" ] = 0x30;
   op_table[   "JC" ] = 0x31;
   op_table[  "JNC" ] = 0x32;
   op_table[   "JZ" ] = 0x33;
   op_table[  "JNZ" ] = 0x34;
   op_table[   "JG" ] = 0x35;
   op_table[  "JNG" ] = 0x36;
   op_table[   "JE" ] = 0x37;
   op_table[  "JNE" ] = 0x38;
   op_table[   "JL" ] = 0x39;
   op_table[  "JNL" ] = 0x3A;
   op_table[   "JP" ] = 0x3B;
   op_table[   "JM" ] = 0x3C;
   op_table[   "TA" ] = 0x17;
   op_table[  "LDA" ] = 0x18;
   op_table[  "MVI" ] = 0x28;
   op_table[ "MVIM" ] = 0x29;
   op_table[  "ADI" ] = 0x20;
   op_table[  "ACI" ] = 0x21;
   op_table[  "SUI" ] = 0x22;
   op_table[  "SBI" ] = 0x23;
   op_table[  "ANI" ] = 0x24;
   op_table[  "XRI" ] = 0x25;
   op_table[  "ORI" ] = 0x26;
   op_table[  "CPI" ] = 0x27;
   op_table[  "OUI" ] = 0x2A;
   op_table[ "PUSH" ] = 0x1B;
   op_table[  "POP" ] = 0x1C;
   op_table[   "IN" ] = 0x2C;
   op_table[   "OU" ] = 0x2B;
   op_table[  "HLT" ] = 0x1D;
}
void initialize_size_table(){
    size_table[ "DW" ] = 4;
    size_table[ "DD" ] = 8;
    size_table[ "DS" ] = 16;
}
void initialize_shift_table(){
    shift_table[      "Op" ] =      Op_pos;
    shift_table[ "Address" ] = Address_pos;
    shift_table[    "Dest" ] =    Dest_pos;
    shift_table[ "SourceS" ] = SourceS_pos;
    shift_table[ "SourceT" ] = SourceT_pos;
}
void initialize_table(){
    initialize_op_table();
    initialize_size_table();
    initialize_shift_table();
}

