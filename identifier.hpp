#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <map>
#include <string>

class Identifier{
    public:
        int eval(){}
}; 
class Symbol : public Identifier {
    public:
        Symbol( int IC ): 
            address(IC) {}
        int eval(){ return address; }
    private:
        int address;
};
class Variable : public Identifier {
    public:
        Variable( int size , int value , int IC , int number ): 
            size( size ) , 
            address( IC ) , 
            value( value ) , 
            number( number ) {}
        int eval(){ return address; }
    private:
        int address;
        int value;
        int number;
        int size;

};
class Constant : public Identifier {
    public:
        Constant( int value ): 
            value( value ) {}
        int eval(void){ return value; }
    private:
        int value;
};

typedef std::map<std::string,Identifier*> SymbolTable ; 

#endif
