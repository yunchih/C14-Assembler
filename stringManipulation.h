#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#include "meta.h"
#include "debug.h"

/*---------Struct declaration---------*/

typedef struct Strings_list_struct
{
	char* str;
	struct Strings_list_struct* next ;
	int lineNumber;
} Strings_list;

/*---------Function Prototype---------*/

int case_insensitive_cmp(char *a, char *b);

Strings_list* tokenize( char* line , char* delim );

#endif
