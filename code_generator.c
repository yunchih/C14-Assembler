#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_generator.h"
#include "bitsOperation.h"

void generate_code(
	 FILE* out,
	 Instru_list* instru_list,
	 Symbols_table*  s_table,
	 Variable_table* var_table ){
	
	int IC = 0;	
	
	write_variable( out, var_table, &IC );
	write_instructions( out, instru_list, s_table, var_table );	
}
static void write_variable( FILE* out, Variable_table* var_table, int* IC )
{
	while( var_table != NULL )	
	{
		var_table->addr = *IC;	
		writeField( out ,  Data  , ToInt(var_table->value) );
		*IC++;
		var_table = var_table->next;
	}
}

static void write_instructions(
	FILE* out,
	Instru_list* instru_list,
	Symbols_table* s_table,
	Variable_table* var_table )
{


	while( instru_list != NULL )		
	{
		Opr* oprs = instru_list->first_opr;
		Instructions_table op = instructions_table[ instru_list->type ];

		writeField( out , Opcode , op.op );

		for (int i = 1; format[ op.format ][ i ] != End ; i++ , oprs = oprs->next )
		{
			if( oprs == NULL )
			{
				printf("[ERROR] Invalid format\n");
				break;
			}
			if( oprs->type == TK_LITERAL )
			{
				int addr = 0;
					/* && is a short-circuiting symbol */
				if( !findVariable( oprs->token , &addr , var_table ) &&
					!findSymbol( oprs->token , &addr , s_table ) )
					printf( "[ERROR] Symbol undefined: %s\n",oprs->token );

				writeField( out , format[ op.format ][ i ] , addr );
			}
			else 
				writeField( out , format[ op.format ][ i ] , ToInt(oprs->token) );
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
			return 1;
		}
		s_table = s_table->next;
	}
	return 0;
}

