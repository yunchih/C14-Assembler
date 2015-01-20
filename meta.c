#include <stdio.h>
#include "meta.h"

int ErrorCount;


Instructions_table instructions_table[] = 
{
	{ 0x10,    "INR",  Format4 },
	{ 0x11,    "DCR",  Format4 },
	/* { 0x12, "INRM", Format  },*/
	/* { 0x13, "DCRM", Format  },*/
	{ 0x1A,    "LDI",  Format7 },
	{ 0x19,    "STI",  Format7 },
	{ 0x14,    "MOV",  Format7 },
	/* { 0x15, "MOVR", Format  },*/
	/* { 0x16, "MOVM", Format  },*/
	{ 0x01,    "ADD",  Format1 },
	{ 0x02,    "ADC",  Format1 },
	{ 0x03,    "SUB",  Format1 },
	{ 0x04,    "SBB",  Format1 },
	{ 0x05,    "AND",   Format1 },
	{ 0x06,    "XOR",   Format1 },
	{ 0x07,    "OR",   Format1 },
	{ 0x08,    "NT",   Format7 },
	{ 0x09,    "CMP",  Format7 },
	{ 0x0A,    "SHLA", Format7 },
	{ 0x0B,    "SHRA", Format7 },
	{ 0x0C,    "SHLL", Format7 },
	{ 0x0D,    "SHRL", Format7 },
	{ 0x60,    "MUL",  Format1 },
	{ 0x62,    "DIV",  Format1 },
	/* { 0x61, "MULI", Format  }, */
	/* { 0x63, "DIVI", Format  },*/
	{ 0x0E,    "RLI",  Format2 },
	{ 0x50,    "RRI",  Format2 },
	{ 0x50,    "CALL", Format6 },
	{ 0x51,    "CC",   Format6 },
	{ 0x52,    "CNC",  Format6 },
	{ 0x53,    "CZ",   Format6 },
	{ 0x54,    "CNZ",  Format6 },
	{ 0x55,    "CG",   Format6 },
	{ 0x56,    "CNG",  Format6 },
	{ 0x57,    "CE",   Format6 },
	{ 0x58,    "CNE",  Format6 },
	{ 0x59,    "CL",   Format6 },
	{ 0x5A,    "CNL",  Format6 },
	{ 0x5B,    "CP",   Format5 },
	{ 0x5C,    "CM",   Format5 },
	{ 0x40,    "RET",  Format5 },
	{ 0x41,    "RC",   Format5 },
	{ 0x42,    "RNC",  Format5 },
	{ 0x43,    "RZ",   Format5 },
	{ 0x44,    "RNZ",  Format5 },
	{ 0x45,    "RG",   Format5 },
	{ 0x46,    "RNG",  Format5 },
	{ 0x47,    "RE",   Format5 },
	{ 0x48,    "RNE",  Format5 },
	{ 0x49,    "RL",   Format5 },
	{ 0x4A,    "RNL",  Format5 },
	{ 0x4B,    "RP",   Format5 },
	{ 0x4C,    "RM",   Format5 },
	{ 0x30,    "JMP",  Format6 },
	{ 0x31,    "JC",   Format6 },
	{ 0x32,    "JNC",  Format6 },
	{ 0x33,    "JZ",   Format6 },
	{ 0x34,    "JNZ",  Format6 },
	{ 0x35,    "JG",   Format6 },
	{ 0x36,    "JNG",  Format6 },
	{ 0x37,    "JE",   Format6 },
	{ 0x38,    "JNE",  Format6 },
	{ 0x39,    "JL",   Format6 },
	{ 0x3A,    "JNL",  Format6 },
	{ 0x3B,    "JP",   Format5 },
	{ 0x3C,    "JM",   Format5 },
	/* not sure */
	{ 0x17, "STA",  Format2 },
	{ 0x18,    "LDA",  Format2 },
	{ 0x28,    "MVI",  Format2 },
	/* { 0x29, "MVIM", Format  },*/
	{ 0x20,    "ADI",  Format2 },
	{ 0x21,    "ACI",  Format2 },
	{ 0x22,    "SUI",  Format2 },
	{ 0x23,    "SBI",  Format2 },
	{ 0x24,    "ANI",  Format2 },
	{ 0x25,    "XRI",  Format2 },
	{ 0x26,    "ORI",  Format2 },
	{ 0x27,    "CPI",  Format2 },
	{ 0x2A,    "OUI",  Format2 },
	{ 0x1B,    "PUSH", Format4 },
	{ 0x1C,    "POP",  Format4 },
	{ 0x2C,    "IN",   Format3 },
	{ 0x2B,    "OU",   Format3 },
	{ 0x1D,    "HLT",  Format5 }
};

/*
 * Instructions_table instructions_table[] = 
 * {
 *     [> Opcode , Name , NumberOfFields , Format <]
 *     { 0x0, "hlt",   0, Format5 }, 
 *     { 0x1, "add",   3, Format1 },
 *     { 0x2, "sub",   3, Format1 },
 *     { 0x3, "and",   3, Format1 },
 *     { 0x4, "xor",   3, Format1 },
 *     { 0x5, "shl",   3, Format1 },
 *     { 0x6, "shr",   3, Format1 },
 *     { 0x7, "lda",   2, Format2 },
 *     { 0x8, "ld",    2, Format2 },
 *     { 0x9, "st",    2, Format2 },
 *     { 0xA, "ldi",   2, Format3 },
 *     { 0xB, "sti",   2, Format3 },
 *     { 0xC, "bz",    2, Format2 },
 *     { 0xD, "bp",    2, Format2 },
 *     { 0xE, "jr",    1, Format4 },
 *     { 0xF, "jl",    2, Format2 },
 * };
 */

int instructions_table_size = sizeof( instructions_table ) / sizeof( Instructions_table );

void printError( char* errorMessage , int lineNumber )
{
	ErrorCount++;
	printf("On line %d : %s\n",lineNumber,errorMessage);
}
