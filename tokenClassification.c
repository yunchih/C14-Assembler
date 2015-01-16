#include "tokenClassification.h"

#define VALID_HEX(c) ( ( c >= 'A' && c <= 'F' ) ||  isdigit(c) )

#define PrintErr(s)  printError( s , lineNumber )

#define PrintErrReturn(s) do{ printError( s , lineNumber );return; } while(0)

static int isArray( char* value );

static int getArraySize( char* value );

static int getVarSize( char* size ); 

static int isInitialized( char* token );

static int isImmediate( char* imme );
	
static int legalLiteral( char* p );

static int classifyToken( char* token);

extern int lineNumber;

void setMode(int* MODE,Strings_list* list)
{
	
	if( list->next != NULL )
		PrintErrReturn("directive must not share the same line with other instructions");

	if( !case_insensitive_cmp( ".CODE",  list->str  ) )
		*MODE = CODE ;
	else if( !case_insensitive_cmp( ".DATA",  list->str  ) )
		*MODE = DATA ;
	else
		PrintErrReturn("mal-formed directive. Only .DATA and .CODE recognized");
}
void setConstant(Variable_table** var_table,Strings_list* list )
{
	static Variable_table *cur_var_table,  *next_var_table ;

	if( list->next == NULL || list->next->next == NULL )
		PrintErrReturn( "invalid constant declaration");

	char *name = list->str;
	list = list->next->next;
	char *value = list->str;

	next_var_table = (Variable_table*)malloc( sizeof(Variable_table) );
	next_var_table->var = malloc( strlen(name)+1 );
	strcpy( next_var_table->var , name );

	next_var_table->value = malloc( strlen(value)+1 );
	strcpy( next_var_table->value , value );
	
	if(*var_table == NULL)
		*var_table = next_var_table;
	else
		cur_var_table->next = next_var_table;

	cur_var_table = next_var_table;

}
void setVar( Variable_table** var_table,Strings_list* list )
{
	static Variable_table *cur_var_table,  *next_var_table ;

	if( list->next == NULL )
		PrintErrReturn( "invalid variable declaration");

	char *name = list->str;
	list = list->next;
	char* size = NULL;
	if( !isdigit(*(list->str)) && isInitialized(list->str) )
	{
		size = list->str;
		list = list->next;
	}
	char *value = list->str;

	next_var_table = (Variable_table*)malloc( sizeof(Variable_table) );
	next_var_table->size = getVarSize(size);
	next_var_table->var = malloc( strlen(name)+1 );
	strcpy( next_var_table->var , name );

	int checkArray = isArray( value );
	if( !isInitialized( value ) )
		strcpy( value , "0" );

	if( isArray( value ) )
	{
		#ifdef DEBUG
			log_info("Dealing with array");
		#endif
		int arraySize = getArraySize( value );
		#ifdef DEBUG
			log_info("ArraySize: %d",arraySize);
		#endif

		strcpy( value , "0" );

		if( arraySize > 0 )
			next_var_table->size *= arraySize;
		else
			PrintErrReturn("Invalid array declaration");
		/*
		 *
		 * Beware!  Remember to fill 0 
		 *
		 */
	}
	next_var_table->value = malloc( strlen(value)+1 );
	strcpy( next_var_table->value , value );
	
	if(*var_table == NULL)
		*var_table = next_var_table;
	else
		cur_var_table->next = next_var_table;

	cur_var_table = next_var_table;
}
void setLabel( Symbols_table** s_table, int IC, Strings_list* list )
{
	static Symbols_table  *cur_symbol,    *next_symbol   ;
	int s_len = strlen( list->str ) ;

	if( !legalLiteral( list->str ) )
		PrintErrReturn("variable name contains invalid characters");
	if( s_len > MAX_SYMBOL_LEN )
		PrintErrReturn("symbol must contain no more than 20 characters");
		
	next_symbol = (Symbols_table*)malloc( sizeof(Symbols_table) );
	// no need to plus one here because we will get rid of ':'
	next_symbol->symbol = malloc( s_len ); 

	list->str[ s_len-1 ] = '\0'; // get rid of ':'
	strcpy( next_symbol->symbol, list->str ); 
	next_symbol->addr = IC ;

	if(*s_table == NULL)
		*s_table = next_symbol;
	else
		cur_symbol->next = next_symbol;

	cur_symbol = next_symbol;
}
void setInstruction( Instru_list** instru_list, int typeOfInstr, int IC, Strings_list* list )
{
	static Instru_list *cur_instru_list, *next_instru_list;
	Opr *cur_opr, *next_opr ;
	Opr *opr_list = NULL    ;

	list = list->next ;
	while( list != NULL )
	{
		#ifdef DEBUG
			/* log_info("Current token: %s",list->str); */
		#endif
		next_opr        = (Opr*)malloc( sizeof(Opr) );
		
		int typeOfToken = classifyToken( list->str );
		if( typeOfToken == ERROR ) 
			 return;	 
		else
			next_opr->type = typeOfToken;

		next_opr->token = malloc( strlen( list->str )+1 );
		strcpy( next_opr->token , list->str );

		if(opr_list == NULL)
			opr_list = next_opr;
		else
			cur_opr->next = next_opr;
		cur_opr = next_opr;
		list = list->next;
	}	
	next_instru_list            = (Instru_list*)malloc( sizeof(Instru_list) );
	next_instru_list->type      = typeOfInstr;
	next_instru_list->first_opr = opr_list;
	next_instru_list->addr      = IC;
	if(*instru_list == NULL)
		*instru_list = next_instru_list;
	else
		cur_instru_list->next = next_instru_list;
	cur_instru_list = next_instru_list;
}
static int isArray( char* value )
{
	return strncmp( "DUP",value,3 ) == 0;
}
static int getArraySize( char* value )
{
	int size;
	if( sscanf( value , "DUP(%d)", &size ) )
		return size;
	else
		return 0;
}
static int getVarSize( char* size )
{
	if( size == NULL )
		return SizeOfWord;
	if( strcmp( size , "BYTE" ) == 0 )
		return SizeOfByte;
	if( strcmp( size , "WORD" ) == 0 )
		return SizeOfWord;
	if( strcmp( size , "DWORD" ) == 0 )
		return SizeOfDWord;
}
static int legalLiteral( char* p )
{
	for( ; *p != ':' && *p ; p++ )
		if( !isalnum(*p) && *p != '_' )
			return 0;
	return 1;
}
static int classifyToken( char* token )
{
	/* match immediate */
	if( isImmediate(token) )
		return TK_IMME;

	/* match memory */
	if( *token == '[' )
	{
		char* closeBracket  = strchr( token , ']' );
		
		if( closeBracket  == NULL )
		{
			PrintErr("Unclosed bracket");
			return ERROR;
		}
		
		/* strip '[' and ']'  */
		 *closeBracket = '\0';
		strcpy( token, token+1 ); 

		return TK_MEM;
		/* return classifyToken( token ); */
	}
	if( *token == ']' )
	{
		PrintErr("Unclosed bracket");
		return ERROR;
	}
	/* match register */
	if( *token == 'R' )
	{
		if( !isImmediate(token+1) )
			PrintErr("invalid register name");
		/* Strip 'R' */
		*token = '\0';
		strcpy( token , token+1 );
		#ifdef DEBUG
			log_info("Register written: %s",token);
		#endif
		return TK_REG;
	}

	return TK_LITERAL;

}
static int isInitialized( char* token )
{
	return strcmp( token , "?" ) != 0;
}
static int isImmediate( char* imme )
{
	char *p10,*p16;
	strtol( imme , &p10 , 10 );
	strtol( imme , &p16 , 16 );
	if( *p10 == '\0' || *p16 == '\0' ) return 1; 
	else return 0;

}
int classifyInstruction( char* token )
{
	int i ;
	for( i = 0 ; i < instructions_table_size ; i++ )
		if(!case_insensitive_cmp( token , instructions_table[i].name ))
			return i;
	return ERROR;
}
int isConstant( Strings_list* str )
{
	if( str == NULL )
		return 0;
	else 
		return case_insensitive_cmp( str->str , "EQA" ) == 0;
}
Test( isImmediate )
{
	char test[3][10] = 
	{
		"0x00F","1234","0xFF"
	};
	for (int i = 0; i < 3; ++i)
	{
		log_info("assert %s",test[i]);
		assert( isImmediate( test[i] ) );		
	}
}
Test( classifyInstruction )
{
	assert( classifyInstruction("add") != ERROR );
	assert( classifyInstruction("bz") != ERROR );
	assert( classifyInstruction("abc") == ERROR );
}
