#include<ctype.h>
#include<string.h>
#include "stringManipulation.h"

int case_insensitive_cmp(char const *a, char const *b)
{
	int d;
    for (;; a++, b++) {
        d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}
Strings_list* tokenize( char* line , char* delim )
{
	char* tok;
	char* comment_pos = NULL ;
    string_list* list = NULL;
    string_list *cur_list, *next_list;

	/* get the first token */
   	token = strtok( line, delim );
	 
	   
	/*
	 * Walk through other tokens
	 *
	 * Condition 1 : Ignore blank line
	 * Condition 2 : Ignore comment line
	 * Condition 3 : Ignore further comment 
	 *
	 */
   	while( token != NULL && *token != ';' && comment_pos == NULL ) 
   	{
		next_list = (string_list*) malloc( sizeof(string_list) );
		next_list->next = NULL;
		next_list->string = (char*) malloc( strlen(tok)+1 );
		strcpy( next_list->string, tok );

		/* strip comment */
		if( ( comment_pos = strchr( next_list->string, ';' )) != NULL )
			*comment_pos = '\0' ;
		/* Adding first token to the list */
		if(list == NULL)
				list = next_list;
		/* Connecting the token to the last token of the list */
		else
				cur_list->next = next_list;
	   
		/* Updating state variables */
		cur_list = next_list;
		tok = strtok(NULL, delim);

   	}
	return list;
}

