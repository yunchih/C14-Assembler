#ifndef INSTRUCTIONTABLE_H
#define INSTRUCTIONTABLE_H 

#include <map>
#include <string>
#include "main.hpp"
#include "operation.hpp"

typedef std::map<std::string,Op*>  Op_table;
typedef std::map<std::string,int>  Size_table;
typedef std::map<std::string,int>  Shift_table;

/* Global variable */
extern Op_table    op_table;
extern Size_table  size_table;


/* Function prototype */
void initialize_table();

#endif
