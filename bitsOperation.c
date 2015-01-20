#include "bitsOperation.h"
#include "debug.h"
/* Field   | StartPos | Size */
/* --------|----------|------*/
/* Data    |    0     |  4   */
/* Empty   |    0     |  1   */
/* SourceT |    0     |  1   */
/* SourceS |    1     |  1   */
/* Dest    |    2     |  1   */
/* Opcode  |    3     |  1   */
/* Addr    |    0     |  2   */

Field fields[ numOfField ] = 
{
	{ 0, 2 }, 
	{ 0, 1 },
	{ 0, 1 }, 
	{ 1, 1 }, 
	{ 2, 1 }, 
	{ 3, 1 }, 
	{ 0, 2 }  
};

enum FieldName format[ numOfFormat ][ maxFieldNum ] = 
{
/* Format 1 */
	{ Opcode , Dest , SourceS , SourceT , End }, 

/* Format 2 */
	{ Opcode , Dest , Addr , End }, 			 

/* Format 3 */
	{ Opcode , Dest , Empty , SourceT , End },		     

/* Format 4 */
	{ Opcode , Empty , Empty , SourceT , End },

/* Format 5 */
	{ Opcode , Empty , Empty , Empty , End },

/* Format 6 */
	{ Opcode , Empty , Addr , End }, 			 

/* Format 7 */
	{ Opcode , Empty , SourceS , SourceT , End } 			 
};

int formatSize[ numOfFormat ] = {
/* Format 1 */ 
	1 , 
/* Format 2 */ 
	1 , 
/* Format 3 */ 
	1 , 
/* Format 4 */ 
	1 , 
/* Format 5 */ 
	1 , 
/* Format 6 */ 
	1 , 
/* Format 7 */ 
	1 , 
};

void print_binary(int number);

void writeField( FILE* out , enum FieldName name , int value )
{
	static short cnt = 0;
	static MachineCode machineCode = 0;

	machineCode |= ( value << ( NumberOfBitPerUnit * fields[ name ].pos ) ) ;

	cnt += fields[ name ].numberOfUnit;
	#ifdef DEBUG
		printf("MachineCode: ");
		print_binary((int)machineCode);
		puts("");
		printf("Shifted	   : ");
		print_binary(( value << (NumberOfBitPerUnit * fields[ name ].pos)));
		puts("");
	#endif
	if( cnt == UnitPerBundle )
	{
		fwrite( &machineCode, sizeof(MachineCode), 1, out );
		#ifdef DEBUG
			printf("Write file : ");
			print_binary((int)machineCode);
			puts("");
		#endif
		cnt = 0;
		machineCode = 0;
	}

}

void print_binary(int number)
{
	/* printf(" %04X",number); */
	int mask = 1 << 31;
	for (int i = 0; i < SizeOfInstruction ; ++i)
	{
		if(i%8==0)putchar('|');
		putchar((mask & number) ? '1' : '0');
		number <<= 1;
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
