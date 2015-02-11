#include <iostream>
#include <cstddef>
#include <fstream>
#include <cstdlib> 
#include <string>
using namespace std;
string target[] = { "op","size" };
string out_start_tag = "Start Of Table";
string out_end_tag   = "End Of Table";

#define check( f ) if( f.fail() ){cout<<#f<<endl; exit(1);}

void getTargetLine( fstream& in , string t ){
    string line;
    while( getline( in , line ) && line.find(t) == string::npos );
}
void printUntil( fstream& in_lex , fstream& out ){
    string line;
    while( getline( in_lex , line ) && line.find(out_start_tag) == string::npos )
        out << line <<endl;
    out << line << endl << endl;
}
void printToEOF( fstream& in_lex , fstream& out ){
    string line;
    while( getline( in_lex , line ))
        out << line <<endl;
}
void printPrefix( fstream& out, string t ){
    out << t << " " << "(";  
}
void printSuffix( fstream& out ){
    out << ")" << endl;
}
bool fetch( fstream& in , string *str ){
    string line;
    getline( in , line );
    size_t first_quote = line.find_first_of("\"");
    size_t last_quote = line.find_last_of("\"");
    if( first_quote == last_quote ){
        *str = "";
        return false;
    }
    *str = line.substr( first_quote+1 , last_quote - first_quote - 1 );
    return true;
}
int main(int argc, char *argv[])
{

    fstream in_table, in_lex ,out;

    in_table.open(argv[1],ios::in);
    in_lex.open(argv[2],ios::in);
    out.open(argv[3],ios::out);
    check( in_table ); 
    check( in_lex );
    check( out );


    printUntil( in_lex , out );

    int numOfTarget = sizeof(target)/sizeof(string);
    string str;
    for (int i = 0 ; i < numOfTarget; ++i)
    {
        getTargetLine(in_table , "initialize_"+target[i]+"_table"); 
        printPrefix( out , target[i] );

        fetch( in_table , &str ); /* Fetch first token */
        out << str;

        while( fetch( in_table , &str ) ){
            out <<"|"<< str;
        }

        printSuffix( out );

    }
    printToEOF( in_lex , out );
    in_lex.close();
    in_table.close();
    out.close();
    return 0;
}
