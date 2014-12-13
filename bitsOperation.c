#include "bitsOperation.h"

Field fields[ numOfField ] = 
{
              /* Field   | StartPos | Size */
			  /* --------|----------|------*/
	{ 0, 4 }, /* Data    |    0     |  4   */
	{ 0, 1 }, /* SourceT |    0     |  1   */
	{ 1, 1 }, /* SourceS |    1     |  1   */
	{ 2, 1 }, /* Dest    |    2     |  1   */
	{ 3, 1 }, /* Opcode  |    3     |  1   */
	{ 0, 2 }  /* Addr    |    0     |  2   */
};

enum FieldName format[ numOfFormat ][ maxFieldNum ] = 
{
	{ Opcode , Dest , SourceS , SourceT , End }, /* Format 1 */
	{ Opcode , Dest , Addr , End }, 			 /* Format 2 */
	{ Opcode , Dest , SourceT , End },		     /* Format 3 */
	{ Opcode , SourceT , End }				     /* Format 4 */
};

void writeField( FILE* out , enum FieldName name , int value )
{
	static short cnt = 0;
	static MachineCode machineCode;

	machineCode |= ( value << ( NumberOfBitPerUnit * fields[ name ].pos ) ) ;

	cnt += fields[ name ].numberOfUnit;
	if( cnt == UnitPerBundle )
	{
		fwrite( &machineCode, sizeof(MachineCode), 1, out );
		cnt = 0;
	}

}


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
