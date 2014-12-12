#include <stdio.h>
#include "bitsOperation.h"

/*
 * static void makeMask( MachineCode *mask , int pos , int effectiveField )
 * {
 *     MachineCode->mask = 0;
 *     for (int i = 0; i < effectiveField; ++i)
 *         MachineCode->mask |= ( 1 << i );
 *     MachineCode->mask <<= ( pos * NumberOfBitPerUnit ) ;
 * }
 * void initializeMask( MachineCode masks[] )
 * {
 *     for (int i = 0; i < NumOfFields; ++i)
 *         makeMask( masks+i , fields[i].pos , fields[i].numberOfBit );
 * }
 */
void writeField( FILE* out , enum FieldName name , int value )
{
	static short cnt = 0;
	static MachineCode machineCode;

	machineCode |= ( value << ( NumberOfBitPerUnit * fields[ name ].pos ) ) ;

	cnt += fields[ name ].numberOfUnit
	if( cnt == UnitPerBundle )
	{
		fwrite(machineCode,sizeof(MachineCode),1,out);
		cnt = 0;
	}

}
