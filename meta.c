#include<stdio.h>
#include "meta.h"

int ErrorCount;

Instructions_table instructions_table[ INSTRU_TABLE_SIZE ] = 
{
    { '0', "hlt",   0, {             }},
    { '1', "add",   3, { REG,REG,REG }},
    { '2', "sub",   3, { REG,REG,REG }},
    { '3', "and",   3, { REG,REG,REG }},
    { '4', "xor",   3, { REG,REG,REG }},
    { '5', "shl",   3, { REG,REG,REG }},
    { '6', "shr",   3, { REG,REG,REG }},
    { '7', "lda",   2, { REG,CON     }},
    { '8', "ld",    2, { REG,MEM     }},
    { '9', "st",    2, { MEM,REG     }},
    { 'A', "ldi",   2, { REG,MEM     }},
    { 'B', "sti",   2, { MEM,REG     }},
    { 'C', "bz",    2, { REG,CON     }},
    { 'D', "bp",    2, { REG,CON     }},
    { 'E', "jr",    1, { REG         }},
    { 'F', "jl",    2, { REG,CON     }},
    { '8', "read",  1, { REG         }},
    { '9', "print", 1, { REG         }}
};
void printError( char* errorMessage , int lineNumber )
{
	ErrorCount++;
	printf("On line %d : %s\n",lineNumber,errorMessage);
}
