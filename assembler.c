#include<stdio.h>
#include<string.h>
#define maxLenOfTokens 10
#define maxNumOfTokens 10
char* trimComment(char* str){
	char *copy=str;
	while(*copy && *copy!=';')copy++;
	*copy = 0 ;
	return str;	
}
int tokenize(char dest[][10],char* src){
	int n=0;
	char *delim = " \t,";
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

void parse_line(char* str){
	char tokens[maxNumOfTokens][maxLenOfTokens];
	int numOfTokens = tokenize(tokens,str);
}
int main(int argc, char **argv)
{
	struct asm_file *af = NULL;
	if (argc != 2) {
		printf("Correct Usage: %s [filenname]\n", argv[0]);
		exit(1);
	}
	asm_init(&af, argv[1]);
	asm_start(af);
	asm_destroy(af);
	return 0;
}
