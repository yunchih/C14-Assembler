#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H 
#include "meta.h"
#include "stringManipulation.h"

/*---------Function Prototype---------*/

void generate_code(FILE* src, Instru_list* instru_list, Symbols_table* s_table, Variable_table* var_table );

#endif

