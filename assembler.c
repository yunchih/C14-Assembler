#include<stdio.h>
#include<string.h>
#define maxLenOfTokens 10
#define maxNumOfTokens 10
void init_file(FILE* src,const char *filename){
	*src = malloc(sizeof(FILE));
	*src = fopen(filename,"r");
}
void destroy_file(FILE* src){
	fclose(src);
}_

char* trimComment(char* str){
	char *copy=str;
	while(*copy && *copy!=';')copy++;
	*copy = 0 ;
	return str;	
}
int tokenize(char dest[][10],char* src){
	int n=0;
	char *delim = " \t,";
	/*
	   make a copy and allocate memory to it 
	   ( so that trimComment can write on memory)
	*/
	char *srcCopy = strdup(src);

	srcCopy = trimComment(srcCopy);

	/* get the first token */
   	char *token = strtok(srcCopy, delim);
	 
  	 /* walk through other tokens */
   	while( token != NULL  ) 
   	{
    	//ignore label such as .data or .text
	   if( token[0]!='.'){
   	   	  strcpy(*dest++,token); 
	   	  n++;
	   } 
   	   token = strtok(NULL, delim);
   	}
	free(srcCopy);
	return n;
}

void read_line(FILE* src){
	char *line = NULL;
	size_t len = 0;
	int numOfTokens;
	char tokens[maxNumOfTokens][maxLenOfTokens];

	while(getline(&line,&len,src)!= -1){
		numOfTokens = tokenize(tokens,line);
	}
}
int main(int argc, char **argv)
{
	FILE *src = NULL;
	if (argc != 2) {
		printf("Correct Usage: %s [filenname]\n", argv[0]);
		exit(1);
	}
	file_init(&src, argv[1]);
	read_line(&src);
	file_destroy(&src);
	return 0;
}
