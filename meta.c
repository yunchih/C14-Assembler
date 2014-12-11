#include<stdio.h>
#include "meta.h"

int ErrorCount;

Instructions_table instructions_table[ INSTRU_TABLE_SIZE ] = 
{
    { 0x0, "hlt",   0, Format1 }, 
    { 0x1, "add",   3, Format1 },
    { 0x2, "sub",   3, Format1 },
    { 0x3, "and",   3, Format1 },
    { 0x4, "xor",   3, Format1 },
    { 0x5, "shl",   3, Format1 },
    { 0x6, "shr",   3, Format1 },
    { 0x7, "lda",   2, Format2 },
    { 0x8, "ld",    2, Format2 },
    { 0x9, "st",    2, Format2 },
    { 0xA, "ldi",   2, Format1 },
    { 0xB, "sti",   2, Format1 },
    { 0xC, "bz",    2, Format2 },
    { 0xD, "bp",    2, Format2 },
    { 0xE, "jr",    1, Format1 },
    { 0xF, "jl",    2, Format2 },
};
void printError( char* errorMessage , int lineNumber )
{
	ErrorCount++;
	printf("On line %d : %s\n",lineNumber,errorMessage);
}
