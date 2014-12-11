#ifndef BIT_OPERATION_H 
#define BIT_OPERATION_H

/*---------Bit field constants---------*/

#define NumberOfBit 16
#define NumberOfBitPerUnit NumberOfBit / 4
#define NumberOfUnitPerAddr NumberOfBitPerUnit * 2

/*---------Format---------*/

typedef struct 
{
	int code: NumberOfBit ;
} MachineCode ;
typedef struct 
{
	int pos;
	int NumberOfBit;
} Field;

enum { SourceT , SourceS , Dest , Opcode , Addr };

Field fields[] = 
{
	{ 0, NumberOfBitPerUnit }, /* SourceT */
	{ 1, NumberOfBitPerUnit }, /* SourceS */
	{ 2, NumberOfBitPerUnit }, /* Dest    */
	{ 3, NumberOfBitPerUnit }, /* Opcode  */
	{ 0, NumberOfUnitPerAddr } /* Addr    */
};

#define numOfFields  sizeof( fields ) / sizeof( Field )

#endif
