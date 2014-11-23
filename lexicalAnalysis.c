#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "meta.h"
#include "lexicalAnalysis.h"

#define MAX_LINE_LEN 100
#define MAX_SYMBOL_LEN 20
#define MAX_VAR_LEN 20
#define ERROR -1
#define VALID_HEX(c) ( ( c >= 'A' && c <= 'F' ) ||  isdigit(c) )
#define PERR(s)  printError( s , lineNumber )
#define PERRC(s) printError( s , lineNumber );continue
/*
 * TODO:
 *     1. Check if variable or symbol start with number.
 *     2. What if .DATA or .CODE are missing?
 *     3. Where to terminate if errors are found? 
 *        ( Set a static variable in `printError` and
 *        increment it whenever the function is called.  
 *        But how to retrieve that variable when needed )
 *        Or a global variable would be better?
 *     4. How IC should increment.
 */

extern int ErrorCount ;
static int lineNumber ;

void lexical_analysis(  
	 FILE* src, 
	 Tokens_list**    tk_list,
	 Symbols_table**  s_table,
	 Variable_table** var_table ){

	char line[MAX_LINE_LEN];
	int IC = 0 , MODE = UNDEFINED;
	char* delim = " \t\n,";

	Strings_list   *str_list ;
	Tokens_list    *line_tk_list ;
	Tokens_list    *cur_tk_list,    *next_tk_list   ;
	Token          *cur_tk,         *next_tk   	    ;
	Symbols_table  *cur_s_table,    *next_s_table   ;
	Variable_table *cur_var_table,  *next_var_table ;
	*s_table   = NULL;
	*tk_list   = NULL;
	*var_table = NULL;
	lineNumber = 0;
	ErrorCount = 0;
	int typeOfInstr = 0 , typeOfToken = 0 , typeOfImmediate = 0 ;
	
	while( fgets ( line, MAX_LINE_LEN , src ) != NULL ){
		lineNumber++;
		str_list = tokenize( line, delim );
		
		/* blank line or line with comment only */
		if( str_list == NULL )
			continue;
		/* match directive */
		else if(*(str_list->str) == '.')
		{
			if( str_list->next != NULL )
				PERRC( "directive must not share the same line with other instructions");

			if( !case_insensitive_cmp( ".CODE", *( str_list->str ) ) )
				MODE = CODE ;
			else if( !case_insensitive_cmp( ".DATA", *( str_list->str ) ) )
				MODE = DATA ;
			else
				PERRC( "mal-formed directive. Only .DATA and .CODE recognized");

		}
		else if( MODE == DATA )
		{
			if( !isLegalLiteral( str_list->str )
				PERRC( "variable name contains invalid characters");
			if( strlen( str_list->str ) > MAX_VAR_LEN )
				PERRC( "variable name must contain no more than 20 characters");
			if( str_list->next == NULL || str_list->next->next != NULL )
				PERRC( "make sure you have .code before any instruction");

			if( *(str_list->str)  == '?')
				typeOfImmediate = TK_UNIN_IMME ;
			else
				typeOfImmediate = classifyImmediate( str_list->next->str );
			
			if(typeOfImmediate == ERROR)
				continue;
			if(typeOfImmediate == TK_NON_IMME)
				PERRC( "make sure you have .code before any instruction");

			next_var_table = (Variable_table*)malloc( sizeof(Variable_table) );
			strcpy( next_var_table->var , str_list->str );
			next_var_table->value = str_list->next->str;
			next_var_table->type = typeOfImmediate;
			
			if(var_table == NULL)
				*var_table = next_var_table;
			else
				cur_var_table->next = next_var_table;

			cur_var_table = next_var_table;

		}
		/* match label */
		else if(  *( str_list->str + strlen( str_list->str ) - 1 ) == ':' )	
		{
			int s_len = strlen( str_list->str ) ;
			if( !isLegalLiteral( str_list->str )
				PERRC( "variable name contains invalid characters");
			if( s_len > MAX_SYMBOL_LEN )
				PERRC( "symbol must contain no more than 20 characters");
			if( str_list->next != NULL )
				PERRC( "label must not share line with other instructions");
				
				next_symbol = (Symbols_table*)malloc( sizeof(symbols_table) );
				next_symbol->symbol = malloc( s_len ); // no need to plus one here because we will get rid of ':'

				strncpy( next_symbol->symbol, str_list->str , s_len-1 ); // get rid of ':'
				next_symbol->addr = IC ;

				if(*s_table == NULL)
					*s_table = next_symbol;
				else
					cur_symbol->next = next_symbol;

				cur_symbol = next_symbol;
				
		}
		/* match instruction */
		else if( MODE == CODE && ( typeOfInstr = classifyInstruction( str_list->str ) ) != ERROR )
		{
			str_list = str_list->next ;
			while( str_list != NULL )
			{
				next_tk        = (token*)malloc( sizeof(token) );
				next_tk->token = malloc( strlen( str_list ) );
				strcpy( next_tk->token , str_list->str );
				if(line_tk_list == NULL)
					line_tk_list = next_tk;
				else
					cur_tk->next = next_tk;
				cur_tk = next_tk;

				typeOfToken = classifyToken( cur_tk );
				if( typeOfToken == ERROR ) 
					 continue;	 
			}	
			next_tk_list              = (Tokens_list*)malloc( sizeof(Tokens_list) );
			next_tk_list->type        = typeOfInstr;
			next_tk_list->first_token = line_tk_list;
			next_tk_list->addr		  = IC;
			if(tk_list == NULL)
				tk_list = next_tk_list;
			else
				cur_tk_list->next = next_tk_list;
			cur_tk_list = next_tk_list;

			/*
			 * TODO:
			 *     Reconsider how Instruction Counter should increment.	
			 */
			IC++;
		}
		else
		{
			PERRC( "invalid instruction.  Also, make sure you have .code before any instruction.");
		}
	}
}
int legalLiteral( char* p )
{
	for( ; *p ; p++ )
		if( !isalnum(*v_p) && *v_p != '_' )
		{
			return 0;
		}
	return 1;
}
int classifyToken( char* token)
{
	/* match immediate */
	int typeOfImmediate = classifyImmediate( token );
	if( typeOfImmediate != TK_NON_IMME )
		return typeOfImmediate;

	/* match memory */
	if( *token == '[' )
	{
		int n = strlen( token );
		if( *( token + n - 1 ) != ']' )
		{
			PERR("Unclosed bracket");
			return ERROR;
		}
		/* strip '[' and ']'  */
		strncpy( token, token+1, n-2); 
		return TK_MEM;
	}
	if( *token == ']' )
	{
		PERR("Unclosed bracket");
		return ERROR;
	}
	/* match register */
	if( *token == 'R' )
	{
		token++;
		if(*(token+1) == '\0' && VALID_HEX(*token)  )
			return TK_REG;
		PERR("invalid register name");
	}

}
int classifyImmediate( char* imme )
{
	/* match decimal 0 or hexidecimal number */
	if( *imme == '0' )
	{
		imme++;
		if(*imme == 'x' )
		{
			while(*imme!='\0')
				if( !VALID_HEX(*imme) )
				{
					PERR("invalid hexadecimal immediate");
					return ERROR;
				}
			return TK_HEX;
		}
		else if(*imme == '\0' )
			return TK_DEC;

		PERR("invalid immediate or symbol");
		return ERROR;
	}
	/* match decimal */
	if( isdigit(*imme) || *imme == '-' )
	{
		if( *imme == '-' && !isdigit(*(imme+1)) )
		{
			PERR("invalid negative immediate");
			return ERROR;
		}
		while(*(++imme)!='\0')
			if(!isdigit(*imme))
			{
				PERR("invalid decimal immediate or symbol");
				return ERROR;
			}
		return TK_DEC;
	}
	return TK_NON_IMME;
}
int classifyInstruction( char* token )
{
	int i ;
	for( i = 0 ; i < INSTRU_TABLE_SIZE ; i++ )
		if(!case_insensitive_cmp( token , instructions_table[i].name ))
			return i;
	return ERROR;
}

