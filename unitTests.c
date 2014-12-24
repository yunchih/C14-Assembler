#include <unistd.h>
#include <stdlib.h>
#include "meta.h"
#include "stringManipulation.h"
#include "tokenClassification.h"
#include "bitsOperation.h"
#include "lexicalAnalysis.h"
#include "debug.h"
void printInstructionList( Instru_list* list )
{
	if( list == NULL )
	{
		puts("List is null");
		return;
	}
	while( list != NULL )
	{
		printf("type: %d , addr: %d  ",list->type,list->addr);
		Opr* oprs = list->first_opr;
		while( oprs != NULL )
		{
			printf(" %s |",oprs->token );
			oprs = oprs->next;
		}
		printf("\n-----\n");
		list = list->next;
	}

}
void printVarTable(Variable_table* table)
{
	if( table == NULL )
	{
		puts("Table is null");
		return;
	}
	while( table != NULL )
	{
		printf("var: %s,value: %s |  ",table->var,table->value);
		table = table->next;
	}
	puts("");
}
void printStrList(Strings_list* list)
{
	if( list == NULL )
	{
		puts("This is a null line");
		return;
	}
	while( list != NULL )
	{
		printf("%s | ",list->str);
		list = list->next;
	}
	puts("");
}

Test(Tokenize)
{
	char* delim = " \t\n,";
	char test[5][30] = 
	{
		" a b c d",
		" a , b, c, d",
		" a b , c , d",
		" a		b,c,d ;comment",
	   	" 		a b	c 	d;;;comment	"	
	};
	char expected[4][2]={"a","b","c","d"};
	Strings_list* list;
	for (int i = 0; i < 5; ++i)
	{
		list = tokenize(test[i],delim);
		for (int j = 0; j < 4; ++j)
		{
			assert( list != NULL );
			assert_str(list->str, expected[j]);
			list = list->next;
		}
		assert( list == NULL );
	}
}
Test(Case_insensitive_cmp)
{
	char *test1[3] = 
	{
		"abc","aBc","AB,C"
	};
	char *test2[3] = 
	{
		"Abc","ABC","ab,c"
	};
	for (int i = 0; i < 3; ++i)
		assert( case_insensitive_cmp(test1[i],test2[i]) == 0 );
}

Test( LexicalAnalysis )
{
	Symbols_table*  s_table;
	Variable_table* var_table;
    Instru_list*    instru_list;
	FILE* testfile;

	testfile = fopen("testfile2.asm","r");
	lexical_analysis( testfile, &instru_list, &s_table, &var_table );
}
int main(void)
{
	TEST( Tokenize );
	TEST( Case_insensitive_cmp );
	TEST( isImmediate );
	TEST( classifyInstruction );
	TEST( LexicalAnalysis );
	return 0;
}

