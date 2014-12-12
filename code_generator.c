#include<stdio.h>
#include "code_generator.h"
#include "bitsOperation.h"

void generate_code(
	 FILE* out,
	 Instru_list* instru_list,
	 Symbols_table*  s_table,
	 Variable_table* var_table ){
	
	int IC = 0;	
	
	/*
	 * MachineCode masks[ NumOfFields ];
	 * initializeMask( masks );
	 */

	write_variable( out, var_table, &IC, masks );
	write_instructions( out, instru_list, s_table, var_table, &LC, masks );	
}
static void write_variable( FILE* out, Variable_table* var_table, int* IC, MachineCode masks[] )
{
	while( var_table != NULL )	
	{
		var_table->addr = *LC;	
		writeField( out ,  DATA  , var_table->value );
		*LC++;
		var_table = var_table->next;
	}
}

static void write_instructions(
	FILE* src,
	Instru_list* instru_list,
	Symbols_table* s_table,
	Variable_table* var_table,
	int* LC,
	MachineCode masks[])
{


	while( instru_list != NULL )		
	{
		Opr oprs = instru_list->first_opr;

		writeField( out , Opcode , instructions_table[ instru_list->type ].op )

		writeField( out , Dest   , ToInt(oprs->token) )
		
		oprs = oprs->next ;	

		if( oprs != NULL )
		{

			if( op.format == Format1 )
			{
				writeField( out , SourceS , ToInt(oprs->token) );

				oprs = oprs->next ;	

				if( oprs != NULL )
					writeField( out , SourceT , ToInt(oprs->token) );
			}
			else
			{
				if( oprs->type == TK_LITERAL )
				{

				}
				else
				{
					writeField( out , Addr , ToInt(oprs->token) );
				}
			}
		}
		else
		{
			/* write 0 */
		}
	
		instru_list = instru_list->next;
		
	}
}

