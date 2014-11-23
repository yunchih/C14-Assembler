#include<stdio.h>

void init_file(FILE* src,const char *filename){
	src = malloc(sizeof(FILE));
	if((src = fopen(filename,"r"))==NULL)
		printf("Fail to open %s , please ensure it exists",filename);
	else
		puts("start assembling....");

}
int main(int argc, char **argv)
{
	FILE *src = NULL;
	Symbols_table*  s_table;
	Variable_table* var_table;
    Tokens_list*    tk_list;
	
	if (argc != 2) {
		printf("Correct Usage: %s [filenname]\n", argv[0]);
		exit(1);
	}

	file_init(src, argv[1]);
	lexical_analysis( src, &tk_list, &s_table, &var_table );
	fclose(src);
	return 0;
}
