#include "bitsOperation.h"

#define numOfFields  sizeof( fields ) / sizeof( Field )
MachineCode masks[ numOfFields ];

void initializeMask( MachineCode masks[] )
{
	for (int i = 0; i < numOfFields; ++i)
		makeMask( masks+i , masks[i].pos , masks[i].numberOfBit );
}
void makeMask( MachineCode *mask , int pos , int effectiveField )
{
	MachineCode->mask = 0;
	for (int i = 0; i < effectiveField; ++i)
		MachineCode->mask |= ( 1 << i );
	MachineCode->mask <<= ( pos * NumberOfBitPerUnit ) ;
}

void writeBit( MachineCode *Machine , int pos , int value )
{
	
	initializeMask( masks , numOfFields );
	Machine->code |= ( value << ( NumberOfBitPerUnit * pos ) );
}
