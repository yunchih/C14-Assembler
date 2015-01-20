#include <unistd.h>
#include <stdlib.h>
#include "meta.h"
#include "stringManipulation.h"
#include "tokenClassification.h"
#include "bitsOperation.h"
#include "code_generator.h"
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
	int cnt = 0;
	while( table != NULL )
	{
		cnt++;
		printf("%15s: addr: %8d |  ",table->symbol,table->addr);
		table = table->next;
		if(cnt%3==0)putchar('\n');
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
	int cnt=0;
	while( table != NULL )
	{
		cnt++;
		printf("%15s: value: %10s |  ",table->var,table->value);
		table = table->next;
		if(cnt%3==0)putchar('\n');
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
void Test_LexicalAnalysis( char* filename )
{
	Symbols_table*  s_table;
	Variable_table* var_table;
    Instru_list*    instru_list;
	FILE *testfile,*out;

	testfile = fopen(filename,"r");
	lexical_analysis( testfile, &instru_list, &s_table, &var_table );
	out = fopen("test.out","wb");

	#ifdef DEBUG
		log_info("print variable table----->");
		printVarTable(var_table);
		log_info("print symbol table------->");
		printSymbolList(s_table);
		log_info("print instruction table----->");
		printInstructionList( instru_list );
	#endif

	generate_code( out, instru_list, s_table, var_table );
	fclose(out);
	binaryDump("test.out");
}
int main(int argc, char *argv[])
{
	TEST( Tokenize );
	if (argc != 2) {
		printf("Correct Usage: %s [filenname]\n", argv[0]);
		exit(1);
	}
	Test_LexicalAnalysis( argv[1] );

	return 0;
}

