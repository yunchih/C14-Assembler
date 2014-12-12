#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "tokenClassification.h"

#define VALID_HEX(c) ( ( c >= 'A' && c <= 'F' ) ||  isdigit(c) )

#define PrintErr(s)  printError( s , lineNumber )

#define PrintErrReturn(s) do{ printError( s , list->lineNumber );return; } while(0)

void setMode(int* MODE,Strings_list* list)
{
	
	if( list->next != NULL )
		PrintErrReturn("directive must not share the same line with other instructions");

	if( !case_insensitive_cmp( ".CODE",  list->str  ) )
		*MODE = CODE ;
	else if( !case_insensitive_cmp( ".DATA",  list->str  ) )
		*MODE = DATA ;
	else
		PrintErrReturn("mal-formed directive. Only .DATA and .CODE recognized");
}
void setVar(Variable_table** var_table,Strings_list* list)
{

	static Variable_table *cur_var_table,  *next_var_table ;
	int initilized;

	if( !legalLiteral( list->str ) )
		PrintErrReturn( "variable name contains invalid characters");
	if( strlen( list->str ) > MAX_VAR_LEN )
		PrintErrReturn( "variable name must contain no more than 20 characters");
	if( list->next == NULL || list->next->next != NULL )
		PrintErrReturn( "make sure you have .code before any instruction");

	if( !isImmediate( list->next->str ) )
		PrintErrReturn( "Invalid value" );
		
	next_var_table = (Variable_table*)malloc( sizeof(Variable_table) );
	strcpy( next_var_table->var , list->str );
	strcpy( next_var_table->value , list->next->str );
	
	if(*var_table == NULL)
		*var_table = next_var_table;
	else
		cur_var_table->next = next_var_table;

	cur_var_table = next_var_table;
}
void setLabel( Symbols_table** s_table, int IC, Strings_list* list )
{
	static Symbols_table  *cur_symbol,    *next_symbol   ;
	int s_len = strlen( list->str ) ;

	if( !legalLiteral( list->str ) )
		PrintErrReturn("variable name contains invalid characters");
	if( s_len > MAX_SYMBOL_LEN )
		PrintErrReturn("symbol must contain no more than 20 characters");
	if( list->next != NULL )
		PrintErrReturn("label must not share line with other instructions");
		
		next_symbol = (Symbols_table*)malloc( sizeof(Symbols_table) );
		next_symbol->symbol = malloc( s_len ); // no need to plus one here because we will get rid of ':'

		strncpy( next_symbol->symbol, list->str , s_len-1 ); // get rid of ':'
		next_symbol->addr = IC ;

		if(*s_table == NULL)
			*s_table = next_symbol;
		else
			cur_symbol->next = next_symbol;

		cur_symbol = next_symbol;
}
void setInstruction( Instru_list** instru_list, int typeOfInstr, int IC, Strings_list* list )
{
	static Instru_list *cur_instru_list, *next_instru_list;
	Opr *cur_opr, *next_opr ;
	Opr *opr_list = NULL    ;

	list = list->next ;
	while( list != NULL )
	{
		next_opr        = (Opr*)malloc( sizeof(Opr) );
		next_opr->token = malloc( strlen( list->str )+1 );
		strcpy( next_opr->token , list->str );
		
		int typeOfToken = classifyToken( list->str, list->lineNumber );
		if( typeOfToken == ERROR ) 
			 return;	 
		else
			next_opr->type = typeOfToken;

		if(opr_list == NULL)
			opr_list = next_opr;
		else
			cur_opr->next = next_opr;
		cur_opr = next_opr;

	}	
	next_instru_list            = (Instru_list*)malloc( sizeof(Instru_list) );
	next_instru_list->type      = typeOfInstr;
	next_instru_list->first_opr = opr_list;
	next_instru_list->addr      = IC;
	if(*instru_list == NULL)
		*instru_list = next_instru_list;
	else
		cur_instru_list->next = next_instru_list;
	cur_instru_list = next_instru_list;
}
int legalLiteral( char* p )
{
	for( ; *p ; p++ )
		if( !isalnum(*p) && *p != '_' )
			return 0;
	return 1;
}
int classifyToken( char* token,int lineNumber )
{
	/* match immediate */
	if( isImmediate(token) )
		return TK_IMME;

	/* match memory */
	if( *token == '[' )
	{
		int n = strlen( token );
		if( *( token + n - 1 ) != ']' )
		{
			PrintErr("Unclosed bracket");
			return ERROR;
		}
		/* strip '[' and ']'  */
		strncpy( token, token+1, n-2); 
		return classifyToken( token , lineNumber );
	}
	if( *token == ']' )
	{
		PrintErr("Unclosed bracket");
		return ERROR;
	}
	/* match register */
	if( *token == 'R' )
	{
		if( !isImmediate(token+1) )
			PrintErr("invalid register name");
		/* Strip 'R' */
		strcpy( token , token+1 );
		return TK_REG;
	}

	return TK_LITERAL;

}
int isImmediate( char* imme )
{
	char* p;

	strtol( imme , &p , 10 )
	if( *p != '\0' ) return 0; 

	strtol( imme , &p , 16 )
	if( *p != '\0' ) return 0; 

	return 1;

}
int classifyInstruction( char* token )
{
	int i ;
	for( i = 0 ; i < INSTRU_TABLE_SIZE ; i++ )
		if(!case_insensitive_cmp( token , instructions_table[i].name ))
			return i;
	return ERROR;
}

