#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

/*---------Function Prototype---------*/

int case_insensitive_cmp(char const *a, char const *b);

Strings_list* tokenize( char* line , char* delim );


/*---------Struct declaration---------*/

typedef struct Strings_list_struct
{
	char* str;
	struct Strings_list_struct* next ;
	int lineNumber;
} Strings_list;

#endif
