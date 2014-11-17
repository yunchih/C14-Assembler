#include<stdio.h>
void printError( char* errorMessage , int lineNumber )
{
	/* static NumOfError = 0 ; */
	/* NumOfError++; */
	ErrorCount++;
	printf("On line %d : %s\n",lineNumber,errorMessage);
}
