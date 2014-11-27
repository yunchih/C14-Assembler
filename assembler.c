#include<stdio.h>
#include<stdlib.h>
#include "lexicalAnalysis.h"
#include "code_generator.h"

void file_init(FILE* src,const char *filename,char* type,char* message ){
	src = malloc(sizeof(FILE));
	if((src = fopen(filename,type))==NULL)
		printf("Fail to open %s",filename);
	else
		puts(message);

}
int main(int argc, char **argv)
{
	FILE *src = NULL, *out = NULL;
	Symbols_table*  s_table;
	Variable_table* var_table;
    Instru_list*    instru_list;
	
	if (argc != 2) {
		printf("Correct Usage: %s [filenname]\n", argv[0]);
		exit(1);
	}

	file_init(src, argv[1],"r","start assembling....");
	lexical_analysis( src, &instru_list, &s_table, &var_table );
	fclose(src);

	file_init(out,"a.out","w","start writing code....");
	generate_code( out, instru_list, s_table, var_table );
	fclose(out);

	return 0;
}
