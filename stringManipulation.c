#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include "stringManipulation.h"

int case_insensitive_cmp(char *a, char *b)
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
	char* token;
	char* comment_pos = NULL ;
    Strings_list* list = NULL;
    Strings_list *cur_list, *next_list;

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
		next_list = (Strings_list*) malloc( sizeof(Strings_list) );
		next_list->next = NULL;
		next_list->str = (char*) malloc( strlen(token)+1 );
		strcpy( next_list->str, token );

		/* strip comment */
		if( ( comment_pos = strchr( next_list->str, ';' )) != NULL )
			*comment_pos = '\0' ;
		/* Adding first token to the list */
		if(list == NULL)
				list = next_list;
		/* Connecting the token to the last token of the list */
		else
				cur_list->next = next_list;
	   
		/* Updating state variables */
		cur_list = next_list;
		token = strtok(NULL, delim);

   	}
	return list;
}

char* formatHEX(char* hex,int size)
{
	char *formatted_hex = (char*)malloc( size + 1 );
	char *strippedHEX = strchr(hex,'x')+1;
	int offset = size - strlen(strippedHEX);
	memset(formatted_hex,'0',offset);
	strcpy(formatted_hex+offset,strippedHEX);
	return formatted_hex;
}
char* DECtoHEX(char* dec,int size)
{
	int decimal;
	sscanf(dec,"%d",decimal);

	char *formatted_hex = (char*)malloc( size + 1 );
	#define FORMAT(size) "%0" size "x"
	sprintf(formatted_hex,FORMAT(size),decimal);
	return formatted_hex;
}
