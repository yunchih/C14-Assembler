#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tokenClassification.h"
#include "stringManipulation.h"
#include "meta.h"

/*---------Function Prototype---------*/

void lexical_analysis( FILE* src, Instru_list** instru_list,Symbols_table** s_table,Variable_table** var_table );

#endif
