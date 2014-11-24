#ifndef TOKEN_CLASSIFICATION_H
#define TOKEN_CLASSIFICATION_H 

/*---------Function Prototype---------*/ 

void setMode(int* MODE,Strings_list* list);
void setVar(Variable_table* var_table,Strings_list* list);
void setLabel( Symbols_table* s_table, int IC, Strings_list* list );
void setInstruction( Instru_list* instru_list, int typeOfInstr, Strings_list* list );

#endif 
