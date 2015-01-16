#include <stdio.h>
#include "meta.h"

int ErrorCount;

Instructions_table instructions_table[] = 
{
	/* Opcode , Name , NumberOfFields , Format */
    { 0x0, "hlt",   0, Format5 }, 
    { 0x1, "add",   3, Format1 },
    { 0x2, "sub",   3, Format1 },
    { 0x3, "and",   3, Format1 },
    { 0x4, "xor",   3, Format1 },
    { 0x5, "shl",   3, Format1 },
    { 0x6, "shr",   3, Format1 },
    { 0x7, "lda",   2, Format2 },
    { 0x8, "ld",    2, Format2 },
    { 0x9, "st",    2, Format2 },
    { 0xA, "ldi",   2, Format3 },
    { 0xB, "sti",   2, Format3 },
    { 0xC, "bz",    2, Format2 },
    { 0xD, "bp",    2, Format2 },
    { 0xE, "jr",    1, Format4 },
    { 0xF, "jl",    2, Format2 },
};

int instructions_table_size = sizeof( instructions_table ) / sizeof( Instructions_table );

void printError( char* errorMessage , int lineNumber )
{
	ErrorCount++;
	printf("On line %d : %s\n",lineNumber,errorMessage);
}
