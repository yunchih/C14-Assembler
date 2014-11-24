#include<stdio.h>
#include "meta.h"
#include "lexicalAnalysis.h"
#include "tokenClassification.h"
#include "stringManipulation.h"

#define MAX_LINE_LEN 100

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

void lexical_analysis(  
	 FILE* src, 
	 Instruction**    instru_list,
	 Symbols_table**  s_table,
	 Variable_table** var_table ){

	int lineNumber;
	char line[MAX_LINE_LEN];
	int IC = 0 , MODE = UNDEFINED;
	char* delim = " \t\n,";

	Strings_list   *str_list ;
	*s_table   = NULL;
	*tk_list   = NULL;
	*var_table = NULL;
	lineNumber = 0;
	ErrorCount = 0;
	int typeOfInstr = 0 , typeOfToken = 0 , typeOfImmediate = 0 ;
	
	while( fgets ( line, MAX_LINE_LEN , src ) != NULL ){
		lineNumber++;
		str_list = tokenize( line, delim );
		str_list->lineNumber = lineNumber;	

		/* blank line or line with comment only */
		if( str_list == NULL )
			continue;
		/* match directive */
		else if(*(str_list->str) == '.')
		{
			setMode( &MODE, str_list );
		}
		/* match variable */
		else if( MODE == DATA )
		{
			setVar( *var_table, str_list );
		}
		/* match label */
		else if(  *( str_list->str + strlen( str_list->str ) - 1 ) == ':' )	
		{
			setLabel( *s_table, IC, str_list );
		}
		/* match instruction */
		else if( MODE == CODE && ( typeOfInstr = classifyInstruction( str_list->str ) ) != ERROR )
		{
			setInstruction( *instru_list, typeOfInstr, str_list );
			/*
			 * TODO:
			 *     Reconsider how Instruction Counter should increment.	
			 */
			IC++;
		}
		else
		{
			printError( "invalid instruction.  Also, make sure you have .code before any instruction.",lineNumber);
		}
	}
}
