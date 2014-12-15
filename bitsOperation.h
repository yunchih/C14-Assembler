#ifndef BIT_OPERATION_H 
#define BIT_OPERATION_H

#include <stdio.h>

/*---------Struct Declaration---------*/

/*
 * The type `MachineCode` is a `bundle` that contains some units of machine code,
 * It's of type `int`, i.e. 32-bits, so that it can contain the largest possible
 * unit.  Say we want to output machine codes with 16 bits in each line.  And the
 * largest possible unit is the data ( represented by variable ) , which has 16-bits.
 * Other fields include `Opcode`, `Dest`, `Addr`, which take 4 bits, 4 bits and 8 bits
 * respectively.  We fill the bundle with these, and output the bundle as soon as
 * it's filled.
 */
typedef unsigned int MachineCode ;

typedef struct 
{
	int pos;
	int numberOfUnit;
} Field;

/*---------Bit field constants---------*/

#define NumberOfBit 16
#define NumberOfBitPerUnit NumberOfBit / 4
#define UnitPerBundle sizeof( MachineCode ) / NumberOfBitPerUnit

/*---------Fields---------*/

enum FieldName { Data , SourceT , SourceS , Dest , Opcode , Addr , End };

#define numOfField 6

extern Field fields[ numOfField ] ;

/*---------Format---------*/

enum Format { Format1 , Format2 , Format3 , Format4 };

#define numOfFormat 4
#define maxFieldNum 5

extern enum FieldName format[ numOfFormat ][ maxFieldNum ];


/*---------Function Prototype---------*/

void initializeMask( MachineCode masks[] );
void writeField( FILE* out , enum FieldName name , int value );


#endif
