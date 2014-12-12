#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H 
#include "meta.h"

#define ToInt( value ) ((int) strtol( value , NULL , 0 ) )

/*---------Function Prototype---------*/

void generate_code(FILE* out, Instru_list* instru_list, Symbols_table* s_table, Variable_table* var_table );

#endif

