#include "bitsOperation.h"

void initializeMask( MachineCode masks[] )
{
	for (int i = 0; i < NumOfFields; ++i)
		makeMask( masks+i , masks[i].pos , masks[i].numberOfBit );
}
static void makeMask( MachineCode *mask , int pos , int effectiveField )
{
	MachineCode->mask = 0;
	for (int i = 0; i < effectiveField; ++i)
		MachineCode->mask |= ( 1 << i );
	MachineCode->mask <<= ( pos * NumberOfBitPerUnit ) ;
}

void writeField( MachineCode *Machine , int pos , int value )
{
	Machine->code |= ( value << ( NumberOfBitPerUnit * pos ) );
}
