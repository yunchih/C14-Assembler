#include <unistd.h>
#include <stdlib.h>
#include "meta.h"
#include "stringManipulation.h"
#include "tokenClassification.h"
#include "bitsOperation.h"
#include "lexicalAnalysis.h"
#include "debug.h"
void binaryDump( char* fileName ){
	FILE* file = fopen(fileName,"rb");
	assert( file != NULL );
	int c,cnt = 0;

	printf("Dumping %s ---->\n",fileName);
	printf(" %04X : ",cnt*8);
	while( ( c = fgetc(file) ) != EOF ){
		printf("%02X ",c);
		cnt++;
		if( cnt % 4 == 0 ){
			putchar('\n');
			printf(" %04X : ",cnt*8);
		}
	}
	putchar('\n');
	fclose(file);
}
void printSymbolList( Symbols_table* table ){
	if( table == NULL )
	{
		puts("Table is null");
		return;
	}
	while( table != NULL )
	{
		printf("symbol: %s,addr: %d |  ",table->symbol,table->addr);
		table = table->next;
	}
	puts("");
}
void printInstructionList( Instru_list* list )
{
	if( list == NULL )
	{
		puts("List is null");
		return;
	}
	while( list != NULL )
	{
		printf("type: %d , addr: %d  |",list->type,list->addr);
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
	FILE *testfile,*out;

	testfile = fopen("testfile3.asm","r");
	lexical_analysis( testfile, &instru_list, &s_table, &var_table );
	out = fopen("test.out","wb");
	generate_code( out, instru_list, s_table, var_table );
	fclose(out);
	binaryDump("test.out");
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

