#include<stdio.h>
#include "code_generator.h"

void generate_code(
	 FILE* src,
	 Instru_list* instru_list,
	 Symbols_table*  s_table,
	 Variable_table* var_table ){
	
	int LC = 0;	
	write_variable(src,var_table,&LC);
	write_instructions(src,instru_list,s_table,var_table,&LC);	
}
void write_variable(Variable_table* var_table,int* LC)
{
	while( var_table != NULL )	
	{
		var_table->addr = *LC;	
		char* formatted_addr = DECtoHEX(LC,ADDR_SIZE);
		char* formatted_code;
		if(var_table->type != TK_HEX)
			formatted_hex_code = formatHEX(var_table->value,CODE_SIZE);
		else
			formatted_hex_code = DECtoHEX(var_table->value,CODE_SIZE);
		fprintf(src, "%s: %s\n",formatted_addr,formatted_code);

		free(formatted_addr);
		free(formatted_code);

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
