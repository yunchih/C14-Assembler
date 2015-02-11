#ifndef CCALC_H_
#define CCALC_H_

#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <cmemory>
#include <cstdlib>
#include <cstdarg>
#include <cfloat>
#include "parser.hpp"

/*
 * global variable
 */
extern int debug;

/*
 * lex & parse
 */
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char*);

/*
 * input.cpp
 */
extern void DumpRow(void); 
extern int GetNextChar(char *b, int maxBuffer);
extern void BeginToken(char*);
extern void PrintError(const char *s, ...);


#endif /*CCALC_H_*/

