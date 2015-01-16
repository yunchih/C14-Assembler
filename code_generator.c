#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "code_generator.h"
#include "bitsOperation.h"

static int ToInt( char* value );

void generate_code(
	 FILE* out,
	 Instru_list* instru_list,
	 Symbols_table*  s_table,
	 Variable_table* var_table ){
	
	int IC = 0;	
	
	write_variable( out, var_table, &IC );
	write_instructions( out, instru_list, s_table, var_table, IC );	

}
static void write_variable( FILE* out, Variable_table* var_table, int* IC )
{
	while( var_table != NULL )	
	{
		var_table->addr = *IC;	
		int  value = ToInt(var_table->value);
		#ifdef DEBUG
			log_info("Write %s : %d  addr = %d",var_table->var,value,*IC);
			log_info("Size: %d",var_table->size / SizeOfByte);
		#endif
		int numberOfByte = var_table->size / SizeOfByte;
		#define SizeOfInt 4
		if( numberOfByte > SizeOfInt )
		{
			while( numberOfByte > 0 )
			{
				fwrite( &value, SizeOfInt , 1, out );
				numberOfByte -= SizeOfInt;
			}
		}
		else
			fwrite( &value, numberOfByte , 1, out );

		(*IC) += var_table->size;
		var_table = var_table->next;
	}
}

static void write_instructions(
	FILE* out,
	Instru_list* instru_list,
	Symbols_table* s_table,
	Variable_table* var_table,
    int IC )
{


	while( instru_list != NULL )		
	{
		Opr* oprs = instru_list->first_opr;
		Instructions_table op = instructions_table[ instru_list->type ];

		#ifdef DEBUG
			log_info("Op --> %s",op.name);
		#endif
		writeField( out , Opcode , op.op );

		/* Start with 1 because Opcode has been written  */
		for (int i = 1; format[ op.format ][ i ] != End ; i++ )
		{
			if( format[ op.format ][ i ] == Empty )
			{
				#ifdef DEBUG
					log_info("Write Empty field");
				#endif
				writeField( out , Empty , 0 );
				continue;
			}

			if( oprs == NULL )
			{
				printf("[ERROR] Invalid format\n");
				break;
			}
			if( oprs->type == TK_LITERAL )
			{
				int addr = 0;

				/* 
				 * Because we write variable data first, we need to add an offset
				 * to symbol address
				 */
				if( findSymbol( oprs->token , &addr , s_table ) )
					addr += IC ;
				else if( !findVariable( oprs->token , &addr , var_table ) )
				{
					printf( "[ERROR] Symbol undefined: %s\n",oprs->token );
					exit(1);
				}
				#ifdef DEBUG
					log_info("Address to be written: %d",addr);
				#endif
				writeField( out , format[ op.format ][ i ] , addr );
			}
			else {
				int toBeWritten = ToInt(oprs->token);
				#ifdef DEBUG
					log_info("Numeric to be written: %d",toBeWritten);
				#endif
				writeField( out , format[ op.format ][ i ] , toBeWritten );
			}

			oprs = oprs->next;
		}

	
		instru_list = instru_list->next;
		
	}
}
static int findVariable( char* token , int* addr , Variable_table* var_table )
{
	while( var_table != NULL )
	{
		if( strcmp( token , var_table->var ) == 0 )
		{
			*addr = var_table->addr;
			#ifdef DEBUG
				log_info("Variable found: %s addr = %d",var_table->var,var_table->addr );
			#endif
			return 1;
		}
		var_table = var_table->next;
	}
	return 0;
}
static int findSymbol( char* token , int* addr , Symbols_table* s_table )
{
	while( s_table != NULL )
	{
		if( strcmp( token , s_table->symbol ) == 0 )
		{
			*addr = s_table->addr;
			#ifdef DEBUG
				log_info("Symbol found: %s",s_table->symbol);
			#endif
			return 1;
		}
		s_table = s_table->next;
	}
	return 0;
}
static int ToInt( char* value )
{
	if( !isdigit( *value ) )
	{
		char tmpHex[10] = "0x";
		strcat( tmpHex , value );
		return (int) strtol( value , NULL , 16 );
	}
		return (int) strtol( value , NULL , 0 );
}
/*
 * static int evaluateExpression( char* expr )
 * {
 *     char* opPos;
 *     opPos = strchr( mem , '*' ); 
 * }
 */

