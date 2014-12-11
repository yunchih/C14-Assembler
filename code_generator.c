#include<stdio.h>
#include "code_generator.h"

#include<stdio.h>
#include "code_generator.h"

void generate_code(
	 FILE* out,
	 Instru_list* instru_list,
	 Symbols_table*  s_table,
	 Variable_table* var_table ){
	
	int IC = 0;	
	
	write_variable( out,var_table,&IC );
	write_instructions( out,instru_list,s_table,var_table,&LC );	
}
void write_variable( FILE* src, Variable_table* var_table,int* IC )
{
	while( var_table != NULL )	
	{
		var_table->addr = *LC;	
		fwrite( LC, SizeOfAddr, 1, out );
		*LC++;
		var_table = var_table->next;
	}
}

void write_instructions(
	FILE* src,
	Instru_list* instru_list,
	Symbols_table* s_table,
	Variable_table* var_table,
	int* LC){

	MachineCode masks[ NumOfFields ];
	initializeMask( masks );

	while( instru_list!= NULL )		
	{
		
		int type = instru_list->type;	
		char op = instructions_table[type].op;
		char code[5] = "";
		Opr oprs = instru_list->oprs;

		for(int i = 0 ; i < instructions_table[type].len ; i++ )			
		{
			switch(oprs->type)
			{
				case TK_HEX:
					char formatted = formatHEX(oprs->token,ADDR_SIZE);
					strcat(code,
				case TK_MEM:		
			}
		}
				
	}
}

