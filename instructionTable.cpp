#include "instructionTable.hpp"
#include "operation.hpp"

Op_table op_table;
Size_table size_table;
void initialize_op_table(){
   op_table[  "inr" ] = new Op( "inr",  0x10 , Format1 );
   op_table[  "dcr" ] = new Op( "dcr",  0x11 , Format1 );
   op_table[ "inrm" ] = new Op( "inrm", 0x12 , Format1 );
   op_table[ "dcrm" ] = new Op( "dcrm", 0x13 , Format1 );
   op_table[  "ldi" ] = new Op( "ldi",  0x1a , Format1 );
   op_table[  "sti" ] = new Op( "sti",  0x19 , Format1 );
   op_table[  "mov" ] = new Op( "mov",  0x14 , Format1 );
   op_table[ "movr" ] = new Op( "movr", 0x15 , Format1 );
   op_table[ "movm" ] = new Op( "movm", 0x16 , Format1 );
   op_table[  "add" ] = new Op( "add",  0x01 , Format1 );
   op_table[  "adc" ] = new Op( "adc",  0x02 , Format1 );
   op_table[  "sub" ] = new Op( "sub",  0x03 , Format1 );
   op_table[  "sbb" ] = new Op( "sbb",  0x04 , Format1 );
   op_table[  "and" ] = new Op( "and",  0x05 , Format1 );
   op_table[  "xor" ] = new Op( "xor",  0x06 , Format1 );
   op_table[   "or" ] = new Op( "or",   0x07 , Format1 );
   op_table[   "nt" ] = new Op( "nt",   0x08 , Format1 );
   op_table[  "cmp" ] = new Op( "cmp",  0x09 , Format1 );
   op_table[ "shla" ] = new Op( "shla", 0x0a , Format1 );
   op_table[ "shra" ] = new Op( "shra", 0x0b , Format1 );
   op_table[ "shll" ] = new Op( "shll", 0x0c , Format1 );
   op_table[ "shrl" ] = new Op( "shrl", 0x0d , Format1 );
   op_table[  "mul" ] = new Op( "mul",  0x60 , Format1 );
   op_table[  "div" ] = new Op( "div",  0x62 , Format1 );
   op_table[ "muli" ] = new Op( "muli", 0x61 , Format1 );
   op_table[ "divi" ] = new Op( "divi", 0x63 , Format1 );
   op_table[  "rli" ] = new Op( "rli",  0x64 , Format1 );
   op_table[  "rri" ] = new Op( "rri",  0x50 , Format1 );
   op_table[ "call" ] = new Op( "call", 0x50 , Format1 );
   op_table[   "cc" ] = new Op( "cc",   0x51 , Format1 );
   op_table[  "cnc" ] = new Op( "cnc",  0x52 , Format1 );
   op_table[   "cz" ] = new Op( "cz",   0x53 , Format1 );
   op_table[  "cnz" ] = new Op( "cnz",  0x54 , Format1 );
   op_table[   "cg" ] = new Op( "cg",   0x55 , Format1 );
   op_table[  "cng" ] = new Op( "cng",  0x56 , Format1 );
   op_table[   "ce" ] = new Op( "ce",   0x57 , Format1 );
   op_table[  "cne" ] = new Op( "cne",  0x58 , Format1 );
   op_table[   "cl" ] = new Op( "cl",   0x59 , Format1 );
   op_table[  "cnl" ] = new Op( "cnl",  0x5a , Format1 );
   op_table[   "cp" ] = new Op( "cp",   0x5b , Format1 );
   op_table[   "cm" ] = new Op( "cm",   0x5c , Format1 );
   op_table[  "ret" ] = new Op( "ret",  0x40 , Format1 );
   op_table[   "rc" ] = new Op( "rc",   0x41 , Format1 );
   op_table[  "rnc" ] = new Op( "rnc",  0x42 , Format1 );
   op_table[   "rz" ] = new Op( "rz",   0x43 , Format1 );
   op_table[  "rnz" ] = new Op( "rnz",  0x44 , Format1 );
   op_table[   "rg" ] = new Op( "rg",   0x45 , Format1 );
   op_table[  "rng" ] = new Op( "rng",  0x46 , Format1 );
   op_table[   "re" ] = new Op( "re",   0x47 , Format1 );
   op_table[  "rne" ] = new Op( "rne",  0x48 , Format1 );
   op_table[   "rl" ] = new Op( "rl",   0x49 , Format1 );
   op_table[  "rnl" ] = new Op( "rnl",  0x4a , Format1 );
   op_table[   "rp" ] = new Op( "rp",   0x4b , Format1 );
   op_table[   "rm" ] = new Op( "rm",   0x4c , Format1 );
   op_table[  "jmp" ] = new Op( "jmp",  0x30 , Format1 );
   op_table[   "jc" ] = new Op( "jc",   0x31 , Format1 );
   op_table[  "jnc" ] = new Op( "jnc",  0x32 , Format1 );
   op_table[   "jz" ] = new Op( "jz",   0x33 , Format1 );
   op_table[  "jnz" ] = new Op( "jnz",  0x34 , Format1 );
   op_table[   "jg" ] = new Op( "jg",   0x35 , Format1 );
   op_table[  "jng" ] = new Op( "jng",  0x36 , Format1 );
   op_table[   "je" ] = new Op( "je",   0x37 , Format1 );
   op_table[  "jne" ] = new Op( "jne",  0x38 , Format1 );
   op_table[   "jl" ] = new Op( "jl",   0x39 , Format1 );
   op_table[  "jnl" ] = new Op( "jnl",  0x3a , Format1 );
   op_table[   "jp" ] = new Op( "jp",   0x3b , Format1 );
   op_table[   "jm" ] = new Op( "jm",   0x3c , Format1 );
   op_table[   "ta" ] = new Op( "ta",   0x17 , Format1 );
   op_table[  "lda" ] = new Op( "lda",  0x18 , Format1 );
   op_table[  "mvi" ] = new Op( "mvi",  0x28 , Format1 );
   op_table[ "mvim" ] = new Op( "mvim", 0x29 , Format1 );
   op_table[  "adi" ] = new Op( "adi",  0x20 , Format1 );
   op_table[  "aci" ] = new Op( "aci",  0x21 , Format1 );
   op_table[  "sui" ] = new Op( "sui",  0x22 , Format1 );
   op_table[  "sbi" ] = new Op( "sbi",  0x23 , Format1 );
   op_table[  "ani" ] = new Op( "ani",  0x24 , Format1 );
   op_table[  "xri" ] = new Op( "xri",  0x25 , Format1 );
   op_table[  "ori" ] = new Op( "ori",  0x26 , Format1 );
   op_table[  "cpi" ] = new Op( "cpi",  0x27 , Format1 );
   op_table[  "oui" ] = new Op( "oui",  0x2a , Format1 );
   op_table[ "push" ] = new Op( "push", 0x1b , Format1 );
   op_table[  "pop" ] = new Op( "pop",  0x1c , Format1 );
   op_table[   "in" ] = new Op( "in",   0x2c , Format1 );
   op_table[   "ou" ] = new Op( "ou",   0x2b , Format1 );
   op_table[  "hlt" ] = new Op( "hlt",  0x1d , Format1 );
}
void initialize_size_table(){
    size_table[ "DW" ] = 4;
    size_table[ "DD" ] = 8;
    size_table[ "DS" ] = 16;
}
void initialize_table(){
    initialize_op_table();
    initialize_size_table();
}

/*
 * void initialize_shift_table(){
 *     shift_table[      "Op" ] =      Op_pos;
 *     shift_table[ "Address" ] = Address_pos;
 *     shift_table[    "Dest" ] =    Dest_pos;
 *     shift_table[ "SourceS" ] = SourceS_pos;
 *     shift_table[ "SourceT" ] = SourceT_pos;
 * }
 */

