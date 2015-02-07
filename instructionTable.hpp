#ifndef INSTRUCTIONTABLE_H
#define INSTRUCTIONTABLE_H 

typedef std::map<std::string,int> Op_table;

/* Global variable */
extern Op_table op_table;

/* Function prototype */
void initialize_op_table();

#endif
