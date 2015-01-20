#include "lexicalAnalysis.h"
#ifdef DEBUG
	#include "debug.h"
#endif

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

int lineNumber;

void lexical_analysis(  
	 FILE* src, 
	 Instru_list**    instru_list,
	 Symbols_table**  s_table,
	 Variable_table** var_table ){

	char line[MAX_LINE_LEN];
	int IC = 0 , MODE = CODE;
	char* delim = " \t\n,";

	Strings_list   *str_list ;
	*s_table     = NULL;
	*instru_list = NULL;
	*var_table   = NULL;
	lineNumber = 0;
	int typeOfInstr = 0 ;
	
	while( fgets ( line, MAX_LINE_LEN , src ) != NULL ){

		lineNumber++;

		str_list = tokenize( line, delim );

		/* blank line or line with comment only */
		if( str_list == NULL )
			continue;

	#ifdef DEBUG
		log_info("Line %d : %s",lineNumber,line);
		/* printStrList(str_list); */
	#endif

		/* match directive */
		if(*(str_list->str) == '.')
		{
			setMode( &MODE, str_list );
			#ifdef DEBUG
				log_info("Set mode: %s, %d",str_list->str,MODE);
			#endif
			continue;
		}
		/* match constant */
		else if( isConstant( str_list->next ) )
		{
			/* str_list->next = str_list->next->next; [> strip EQU <] */
			setVar( var_table , str_list );
			#ifdef DEBUG
				log_info("Set constant %s",str_list->str);
			#endif
			continue;
		}
		/* match variable */
		else if( MODE == DATA )
		{
			#ifdef DEBUG
				log_info("Set variable %s",str_list->str);
			#endif

			setVar( var_table, str_list );

			continue;
		}
		/* match label */
		else if(  *( str_list->str + strlen( str_list->str ) - 1 ) == ':' )	
		{
			#ifdef DEBUG
				log_info("Set label: %s",str_list->str);
			#endif
			setLabel( s_table, IC, str_list );
			if( str_list->next == NULL )
				continue;
			str_list = str_list->next;
		}

		/* match instruction */
		if( MODE == CODE && ( typeOfInstr = classifyInstruction( str_list->str ) ) != ERROR )
		{
			#ifdef DEBUG
				log_info("Set instruction: %s",str_list->str);
			#endif

			setInstruction( instru_list, typeOfInstr, IC, str_list );

			IC += SizeOfInstruction ;
		}
		else
		{
			log_err( "invalid instruction on line %d.  Also, make sure you have .code before any instruction.",lineNumber);
			exit(1);
		}

	}
}
