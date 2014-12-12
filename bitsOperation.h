#ifndef BIT_OPERATION_H 
#define BIT_OPERATION_H

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
typedef unsigned int MachineCode

typedef struct 
{
	int pos;
	int numberOfUnit;
} Field;

/*---------Bit field constants---------*/

#define NumberOfBit 16
#define NumberOfBitPerUnit NumberOfBit / 4
#define NumberOfUnitPerAddr NumberOfBitPerUnit / 2
#define UnitPerBundle sizeof( MachineCode ) / NumberOfBitPerUnit

/*---------Format---------*/

enum FieldName { Data , SourceT , SourceS , Dest , Opcode , Addr };

enum Format { Format1 , Format2 };

Field fields[] = 
{
	{ 0, 4 }, /* Data    */
	{ 0, 1 }, /* SourceT */
	{ 1, 1 }, /* SourceS */
	{ 2, 1 }, /* Dest    */
	{ 3, 1 }, /* Opcode  */
	{ 0, 2 } /* Addr    */
};

enum FieldName format[2][] = 
{
	{ Opcode , Dest , SourceS , SourceT }, /* Format 1 */
	{ Opcode , Dest , Addr } 			   /* Format 2 */
}

#define numOfFields  sizeof( fields ) / sizeof( Field )

/*---------Function Prototype---------*/

void initializeMask( MachineCode masks[] );
void writeField( FILE* out , enum FieldName name , int pos , int value );


#endif
