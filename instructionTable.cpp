#include "instructionTable.hpp"
Op_table op_table;
Size_table size_table;
Shift_table shift_table;
void initialize_op_table(){
   op_table[  "inr" ] = 0x10;
   op_table[  "dcr" ] = 0x11;
   op_table[ "inrm" ] = 0x12;
   op_table[ "dcrm" ] = 0x13;
   op_table[  "ldi" ] = 0x1a;
   op_table[  "sti" ] = 0x19;
   op_table[  "mov" ] = 0x14;
   op_table[ "movr" ] = 0x15;
   op_table[ "movm" ] = 0x16;
   op_table[  "add" ] = 0x01;
   op_table[  "adc" ] = 0x02;
   op_table[  "sub" ] = 0x03;
   op_table[  "sbb" ] = 0x04;
   op_table[  "and" ] = 0x05;
   op_table[  "xor" ] = 0x06;
   op_table[   "or" ] = 0x07;
   op_table[   "nt" ] = 0x08;
   op_table[  "cmp" ] = 0x09;
   op_table[ "shla" ] = 0x0a;
   op_table[ "shra" ] = 0x0b;
   op_table[ "shll" ] = 0x0c;
   op_table[ "shrl" ] = 0x0d;
   op_table[  "mul" ] = 0x60;
   op_table[  "div" ] = 0x62;
   op_table[ "muli" ] = 0x61;
   op_table[ "divi" ] = 0x63;
   op_table[  "rli" ] = 0x64;
   op_table[  "rri" ] = 0x50;
   op_table[ "call" ] = 0x50;
   op_table[   "cc" ] = 0x51;
   op_table[  "cnc" ] = 0x52;
   op_table[   "cz" ] = 0x53;
   op_table[  "cnz" ] = 0x54;
   op_table[   "cg" ] = 0x55;
   op_table[  "cng" ] = 0x56;
   op_table[   "ce" ] = 0x57;
   op_table[  "cne" ] = 0x58;
   op_table[   "cl" ] = 0x59;
   op_table[  "cnl" ] = 0x5a;
   op_table[   "cp" ] = 0x5b;
   op_table[   "cm" ] = 0x5c;
   op_table[  "ret" ] = 0x40;
   op_table[   "rc" ] = 0x41;
   op_table[  "rnc" ] = 0x42;
   op_table[   "rz" ] = 0x43;
   op_table[  "rnz" ] = 0x44;
   op_table[   "rg" ] = 0x45;
   op_table[  "rng" ] = 0x46;
   op_table[   "re" ] = 0x47;
   op_table[  "rne" ] = 0x48;
   op_table[   "rl" ] = 0x49;
   op_table[  "rnl" ] = 0x4a;
   op_table[   "rp" ] = 0x4b;
   op_table[   "rm" ] = 0x4c;
   op_table[  "jmp" ] = 0x30;
   op_table[   "jc" ] = 0x31;
   op_table[  "jnc" ] = 0x32;
   op_table[   "jz" ] = 0x33;
   op_table[  "jnz" ] = 0x34;
   op_table[   "jg" ] = 0x35;
   op_table[  "jng" ] = 0x36;
   op_table[   "je" ] = 0x37;
   op_table[  "jne" ] = 0x38;
   op_table[   "jl" ] = 0x39;
   op_table[  "jnl" ] = 0x3a;
   op_table[   "jp" ] = 0x3b;
   op_table[   "jm" ] = 0x3c;
   op_table[   "ta" ] = 0x17;
   op_table[  "lda" ] = 0x18;
   op_table[  "mvi" ] = 0x28;
   op_table[ "mvim" ] = 0x29;
   op_table[  "adi" ] = 0x20;
   op_table[  "aci" ] = 0x21;
   op_table[  "sui" ] = 0x22;
   op_table[  "sbi" ] = 0x23;
   op_table[  "ani" ] = 0x24;
   op_table[  "xri" ] = 0x25;
   op_table[  "ori" ] = 0x26;
   op_table[  "cpi" ] = 0x27;
   op_table[  "oui" ] = 0x2a;
   op_table[ "push" ] = 0x1b;
   op_table[  "pop" ] = 0x1c;
   op_table[   "in" ] = 0x2c;
   op_table[   "ou" ] = 0x2b;
   op_table[  "hlt" ] = 0x1d;
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

