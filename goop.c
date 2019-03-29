#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define ANSIC_LANG_COMPILER
// #define CPP_LANG_COMPILER
// #define CSHARP_LANG_COMPILER
// #define JAVA_LANG_COMPILER
// #define PYTHON_LANG_COMPILER

#define SPL "SPECIALCHAR\0"
#define NUM "NUMBERCONST\0"
#define STR "STRINGCONSTANT\0"
#define CHR "CHARCONSTANT\0"
#define IDF "IDENTIFIER\0"
#define KEY "KEYWORD\0"
#define OPT "OPERATOR\0"
#define SEM "SEMICOLON\0"
#define TABLESIZE 300

typedef enum RawType
{
	RAW_CHARSCOREDIGIT,
	RAW_ESCAPECHARS,
	RAW_SEMICOLON,
	RAW_OPENBRACKET1,
	RAW_OPENBRACKET2,
	RAW_OPENBRACKET3,
	RAW_CLOSEBRACKET1,
	RAW_CLOSEBRACKET2,
	RAW_CLOSEBRACKET3,
	RAW_OTHER
}RAW_TYPE;

typedef enum LanguageType
{
	LANG_CPLUSPLUS,
	LANG_ANSIC,
	LANG_JAVA,
	LANG_CSHARP,
	LANG_PYTHON
}LANGUAGE_TYPE;

typedef enum ConstructType
{
	CONSTRUCT_CLASS,
	CONSTRUCT_NAMESPACE,
	CONSTRUCT_FORLOOP,
	CONSTRUCT_WHILELOOP,
	CONSTRUCT_DOWHILELOOP,
	CONSTRUCT_IFELSE,
	CONSTRUCT_SWITCH,
	CONSTRUCT_EXPRESSION,
	CONSTRUCT_DECLARATION,
	CONSTRUCT_TYPEDEF,
	CONSTRUCT_PREPROCESSOR,
	CONSTRUCT_STRUCT,
	CONSTRUCT_ENUM,
	CONSTRUCT_FUNCTIONDEF,
	CONSTRUCT_FUNCTIONCALL,
	CONSTRUCT_ERROR,
	CONSTRUCT_NA
}CONSTRUCT_TYPE;

typedef enum TokenMaster
{
	TOKEN_START,
	TOKEN_KEYWORD,
	TOKEN_OPERATOR,
	TOKEN_CONSTANT,
	TOKEN_IDENTIFIER,
	TOKEN_SPECIALCHAR,
	TOKEN_SEMICOLON,
	TOKEN_END,
	CONSTANT_START,
	CONSTANT_NUM,
	CONSTANT_STR,
	CONSTANT_CHAR,
	CONSTANT_NULL,
	CONSTANT_END,
	KEYWORD_START,
	KEYWORD_ACCESSSPECIFIER,
	KEYWORD_MODIFIER,
	KEYWORD_DATATYPE,
	KEYWORD_FUNCTION,
	KEYWORD_MALLOC,
	KEYWORD_CALLOC,
	KEYWORD_REALLOC,
	KEYWORD_FREE,
	KEYWORD_SIZEOF,
	KEYWORD_CONTAINER,
	KEYWORD_PREPROCESSOR,
	KEYWORD_TYPEDEF,
	KEYWORD_IF,
	KEYWORD_ELSE,
	KEYWORD_SWITCH,
	KEYWORD_FOR,
	KEYWORD_WHILE,
	KEYWORD_DO,
	KEYWORD_BREAK,
	KEYWORD_CONTINUE,
	KEYWORD_CASE,
	KEYWORD_DEFAULT,
	KEYWORD_STRUCT,
	KEYWORD_ENUM,
	KEYWORD_UNION,
	KEYWORD_RETURN,
	KEYWORD_MAIN,
	KEYWORD_SCANF,
	KEYWORD_PRINTF,
	KEYWORD_FSCANF,
	KEYWORD_FPRINTF,
	KEYWORD_PUTS,
	KEYWORD_GETS,
	KEYWORD_FOPEN,
	KEYWORD_FCLOSE,
	KEYWORD_FSEEK,
	KEYWORD_END,
	ACCESSSPECIFIER_START,
	ACCESSSPECIFIER_PUBLIC,
	ACCESSSPECIFIER_PRIVATE,
	ACCESSSPECIFIER_PROTECTED,
	ACCESSSPECIFIER_INTERNAL,
	ACCESSSPECIFIER_END,
	OPERATOR_START,
	TERNARYOP_TERNARY,
	UNARY_START,
	UNMATOP_ARITHMATICNOT,
	UNMATOP_INCREAMENT,
	UNMATOP_DECREAMENT,
	UNRELOP_LOGICALNOT,
	UNARY_END,
	BINARY_START,
	BINARYREL_START,
	BINRELOP_EQUALITY,
	BINRELOP_NOTEQUALITY,
	BINRELOP_GREATER,
	BINRELOP_LESSER,
	BINRELOP_GREATEROREQUAL,
	BINRELOP_LESSEROREQUAL,
	BINRELOP_LOGICALOR,
	BINRELOP_LOGICALAND,
	BINARYREL_END,
	BINARYMAT_START,
	BINMATOP_ASSIGNMENT,
	BINMATOP_ADDITION,
	BINMATOP_SUBTRACTION,
	BINMATOP_MULTIPLICATION,
	BINMATOP_DIVISION,
	BINMATOP_MODULUS,
	BINMATOP_ADDANDASSIGN,
	BINMATOP_SUBTRACTANDASSIGN,
	BINMATOP_DIVIDEANDASSIGN,
	BINMATOP_MULTIPLYANDASSIGN,
	BINMATOP_MODULUSANDASSIGN,
	BINMATOP_XORANDASSIGN,
	BINMATOP_ORANDASSIGN,
	BINMATOP_ANDANDASSIGN,
	BINMATOP_XOR,
	BINMATOP_ARITHMATICAND,
	BINMATOP_ARITHMATICOR,
	BINMATOP_LEFTSHIFT,
	BINMATOP_RIGHTSHIFT,
	BINARYMAT_END,
	BINARY_END,
	OPERATOR_UNARYMAT,
	OPERATOR_UNARYREL,
	OPERATOR_BINARYMAT,
	OPERATOR_BINARYREL,
	OPERATOR_TERNARY,
	OPERATOR_END,
	DATATYPE_START,
	DATATYPE_VOID,
	DATATYPE_CHAR,
	DATATYPE_STRING,
	DATATYPE_DOUBLE,
	DATATYPE_INT,
	DATATYPE_FLOAT,
	DATATYPE_DECIMAL,
	DATATYPE_OBJECT,
	DATATYPE_DYNAMIC,
	DATATYPE_USERDEFINED,
	DATATYPE_OTHER,
	DATATYPE_END,
	IDENTIFIER_START,
	IDENTIFIER_VARIABLE,
	IDENTIFIER_FUNCTION,
	IDENTIFIER_CLASS,
	IDENTIFIER_NAMESPACE,
	IDENTIFIER_PACKAGE,
	IDENTIFIER_STRUCT,
	IDENTIFIER_ENUMERATION,
	IDENTIFIER_END,
	CONTAINER_START,
	CONTAINER_STRUCT,
	CONTAINER_ENUM,
	CONTAINER_CLASS,
	CONTAINER_NAMESPACE,
	CONTAINER_PACKAGE,
	CONTAINER_END,
	MODIFIER_START,
	MODIFIER_STATIC,
	MODIFIER_EXTERN,
	MODIFIER_VOLATILE,
	MODIFIER_CONST,
	MODIFIER_UNSIGNED,
	MODIFIER_SIGNED,
	MODIFIER_SHORT,
	MODIFIER_LONG,
	MODIFIER_END,
	SPL_START,
	SPL_LEFTPARANTHESIS,
	SPL_RIGHTPARANTHESIS,
	SPL_AMPERSAND,
	SPL_LEFTBRACE,
	SPL_RIGHTBRACE,
	SPL_LEFTSQUARE,
	SPL_RIGHTSQUARE,
	SPL_COLON,
	SPL_COMMA,
	SPL_SCOPERESOLUTION,
	SPL_QUESTIONMARK,
	SPL_STRUCTREFACCESS,
	SPL_PERIOD,
	SPL_RANGEOPERATOR,
	SPL_PREPROCESSOR,
	SPL_END,
	PREPROCESSOR_START,
	PREPROCESSOR_INCLUDE,
	PREPROCESSOR_DEFINE,
	PREPROCESSOR_PRAGMA,
	PREPROCESSOR_IF,
	PREPROCESSOR_IFDEF,
	PREPROCESSOR_UNDEF,
	PREPROCESSOR_ENDIF,
	PREPROCESSOR_IFNDEF,
	PREPROCESSOR_ELSE,
	PREPROCESSOR_ELIF,
	PREPROCESSOR_ERROR,
	PREPROCESSOR_DEFINED,
	PREPROCESSOR_END,
	TOKENMASTER_NA,
	TOKENMASTER_END
}TOKEN_MASTER;

typedef enum ModifierBitPos
{
	BIT_EXTERN = 0x01,
	BIT_VOLATILE = 0x02,
	BIT_CONST = 0x04,
	BIT_STATIC = 0x08,
	BIT_POINTER = 0x10,
	BIT_ARRAY = 0x20,
	BIT_SIGNED = 0x40,
	BIT_UNSIGNED = 0x80
}MODIFIER_BIT_POS;

typedef enum TokenType
{
	TOKENTYPE_CONSTANT,
	TOKENTYPE_SEMICOLON,
	TOKENTYPE_KEYWORD,
	TOKENTYPE_DATATYPE,
	TOKENTYPE_IDENTIFIER,
	TOKENTYPE_MODIFIER,
	TOKENTYPE_ACCESSSPECIFIER,
	TOKENTYPE_PREPROCESSOR,
	TOKENTYPE_SPECIALCHAR,
	TOKENTYPE_CONTAINER,
	TOKENTYPE_OPERATOR,
	TOKENTYPE_NA
}TOKEN_TYPE;

TOKEN_TYPE GetTokenType(TOKEN_MASTER token)
{
	switch(token)
	{
		case CONSTANT_START ... CONSTANT_END:{
			return(TOKENTYPE_CONSTANT);
			break;
		}
		case TOKEN_SEMICOLON:{
			return(TOKENTYPE_SEMICOLON);
			break;
		}
		case KEYWORD_START ... KEYWORD_END:{
			return(TOKENTYPE_KEYWORD);
			break;
		}
		case IDENTIFIER_START ... IDENTIFIER_END:{
			return(TOKENTYPE_IDENTIFIER);
			break;
		}
		case TOKEN_IDENTIFIER:{
			return(TOKENTYPE_IDENTIFIER);
			break;
		}
		case SPL_START ... SPL_END:{
			return(TOKENTYPE_SPECIALCHAR);
			break;
		}
		case TOKEN_SPECIALCHAR:{
			return(TOKENTYPE_SPECIALCHAR);
			break;
		}
		case MODIFIER_START ... MODIFIER_END:{
			return(TOKENTYPE_MODIFIER);
			break;
		}
		case OPERATOR_START ... OPERATOR_END:{
			return(TOKENTYPE_OPERATOR);
			break;
		}
		case ACCESSSPECIFIER_START ... ACCESSSPECIFIER_END:{
			return(TOKENTYPE_ACCESSSPECIFIER);
			break;
		}
		case PREPROCESSOR_START ... PREPROCESSOR_END:{
			return(TOKENTYPE_PREPROCESSOR);
			break;
		}
		case DATATYPE_START ... DATATYPE_END:{
			return(TOKENTYPE_DATATYPE);
			break;
		}
		case CONTAINER_START ... CONTAINER_END:{
			return(TOKENTYPE_CONTAINER);
			break;
		}
		default:{
			return(TOKENTYPE_NA);
			break;
		}
	}
	return(TOKENTYPE_NA);
}

char* GetTokenMasterType(TOKEN_MASTER token)
{
	switch(token)
	{
		case TOKEN_SEMICOLON:{
			return(SEM);
			break;
		}
		case TOKEN_OPERATOR:{
			return(OPT);
			break;
		}
		case TOKEN_IDENTIFIER:{
			return(IDF);
			break;
		}
		case CONSTANT_STR:{
			return(STR);
			break;
		}
		case CONSTANT_NUM:{
			return(NUM);
			break;
		}
		case CONSTANT_CHAR:{
			return(CHR);
			break;
		}
		case TOKEN_KEYWORD:{
			return(KEY);
			break;
		}
		case TOKEN_SPECIALCHAR:{
			return(SPL);
			break;
		}
		case KEYWORD_ACCESSSPECIFIER:{
			return("ACCESSSPECIFIER\0");
			break;
		}
		case KEYWORD_PREPROCESSOR:{
			return("PREPROCESSOR\0");
			break;
		}
		case KEYWORD_DATATYPE:{
			return("DATATYPE\0");
			break;
		}
		case KEYWORD_MODIFIER:{
			return("MODIFIER\0");
			break;
		}
		case KEYWORD_TYPEDEF:{
			return("TYPEDEF\0");
			break;
		}
		case KEYWORD_CONTAINER:{
			return("CONTAINER\0");
			break;
		}
		case KEYWORD_FUNCTION:{
			return("FUNCTION\0");
			break;
		}
		case KEYWORD_MALLOC:{
			return("MALLOC\0");
			break;
		}
		case KEYWORD_CALLOC:{
			return("CALLOC\0");
			break;
		}
		case KEYWORD_REALLOC:{
			return("REALLOC\0");
			break;
		}
		case KEYWORD_FREE:{
			return("FREE\0");
			break;
		}
		case KEYWORD_SIZEOF:{
			return("SIZEOF\0");
			break;
		}
		case KEYWORD_IF:{
			return("IF\0");
			break;
		}
		case KEYWORD_ELSE:{
			return("ELSE\0");
			break;
		}
		case KEYWORD_FSEEK:{
			return("FSEEK\0");
			break;
		}
		case KEYWORD_FCLOSE:{
			return("FCLOSE\0");
			break;
		}
		case KEYWORD_FOPEN:{
			return("FOPEN\0");
			break;
		}
		case KEYWORD_FPRINTF:{
			return("FPRINTF\0");
			break;
		}
		case KEYWORD_FSCANF:{
			return("FSCANF\0");
			break;
		}
		case KEYWORD_PRINTF:{
			return("PRINTF\0");
			break;
		}
		case KEYWORD_SCANF:{
			return("SCANF\0");
			break;
		}
		case KEYWORD_GETS:{
			return("GETS\0");
			break;
		}
		case KEYWORD_PUTS:{
			return("PUTS\0");
			break;
		}
		case KEYWORD_MAIN:{
			return("MAIN\0");
			break;
		}
		case KEYWORD_STRUCT:{
			return("STRUCT\0");
			break;
		}
		case KEYWORD_ENUM:{
			return("ENUM\0");
			break;
		}
		case KEYWORD_SWITCH:{
			return("SWITCH\0");
			break;
		}
		case KEYWORD_CASE:{
			return("CASE\0");
			break;
		}
		case KEYWORD_DEFAULT:{
			return("DEFAULT\0");
			break;
		}
		case KEYWORD_BREAK:{
			return("BREAK\0");
			break;
		}
		case KEYWORD_CONTINUE:{
			return("CONTINUE\0");
			break;
		}
		case KEYWORD_RETURN:{
			return("RETURN\0");
			break;
		}
		case KEYWORD_UNION:{
			return("UNION\0");
			break;
		}
		case KEYWORD_DO:{
			return("DO\0");
			break;
		}
		case KEYWORD_FOR:{
			return("FOR\0");
			break;
		}
		case KEYWORD_WHILE:{
			return("WHILE\0");
			break;
		}
		case ACCESSSPECIFIER_PUBLIC:{
			return("PUBLIC\0");
			break;
		}
		case ACCESSSPECIFIER_PRIVATE:{
			return("PRIVATE\0");
			break;
		}
		case ACCESSSPECIFIER_PROTECTED:{
			return("PROTECTED\0");
			break;
		}
		case ACCESSSPECIFIER_INTERNAL:{
			return("INTERNAL\0");
			break;
		}
		case TERNARYOP_TERNARY:{
			return("TERNARY\0");
			break;
		}
		case UNRELOP_LOGICALNOT:{
			return("LOGICALNOT\0");
			break;
		}
		case UNMATOP_DECREAMENT:{
			return("DECREAMENT\0");
			break;
		}
		case UNMATOP_INCREAMENT:{
			return("INCREAMENT\0");
			break;
		}
		case UNMATOP_ARITHMATICNOT:{
			return("ARITHMATICNOT\0");
			break;
		}
		case BINMATOP_RIGHTSHIFT:{
			return("RIGHTSHIFT\0");
			break;
		}
		case BINMATOP_LEFTSHIFT:{
			return("LEFTSHIFT\0");
			break;
		}
		case BINMATOP_ARITHMATICOR:{
			return("ARITHMATICOR\0");
			break;
		}
		case BINMATOP_ARITHMATICAND:{
			return("ARITHMATICAND\0");
			break;
		}
		case BINMATOP_XOR:{
			return("XOR\0");
			break;
		}
		case BINMATOP_MODULUSANDASSIGN:{
			return("MODULUSANDASSIGN\0");
			break;
		}
		case BINMATOP_MULTIPLYANDASSIGN:{
			return("MULTIPLYANDASSIGN\0");
			break;
		}
		case BINMATOP_ANDANDASSIGN:{
			return("ANDANDASSIGN\0");
			break;
		}
		case BINMATOP_ORANDASSIGN:{
			return("ORANDASSIGN\0");
			break;
		}
		case BINMATOP_XORANDASSIGN:{
			return("XORANDASSIGN\0");
			break;
		}
		case BINMATOP_DIVIDEANDASSIGN:{
			return("DIVIDEANDASSIGN\0");
			break;
		}
		case BINMATOP_SUBTRACTANDASSIGN:{
			return("SUBTRACTANDASSIGN\0");
			break;
		}
		case BINMATOP_ADDANDASSIGN:{
			return("ADDANDASSIGN\0");
			break;
		}
		case BINMATOP_MODULUS:{
			return("MODULUS\0");
			break;
		}
		case BINMATOP_DIVISION:{
			return("DIVISION\0");
			break;
		}
		case BINMATOP_MULTIPLICATION:{
			return("MULTIPLICATION\0");
			break;
		}
		case BINMATOP_SUBTRACTION:{
			return("SUBTRACTION\0");
			break;
		}
		case BINMATOP_ADDITION:{
			return("ADDITION\0");
			break;
		}
		case BINMATOP_ASSIGNMENT:{
			return("ASSIGNMENT\0");
			break;
		}
		case BINRELOP_LOGICALAND:{
			return("LOGICALAND\0");
			break;
		}
		case BINRELOP_LOGICALOR:{
			return("LOGICALOR\0");
			break;
		}
		case BINRELOP_LESSEROREQUAL:{
			return("LESSEROREQUAL\0");
			break;
		}
		case BINRELOP_GREATEROREQUAL:{
			return("GREATEROREQUAL\0");
			break;
		}
		case BINRELOP_LESSER:{
			return("LESSER\0");
			break;
		}
		case BINRELOP_GREATER:{
			return("GREATER\0");
			break;
		}
		case BINRELOP_EQUALITY:{
			return("EQUALITY\0");
			break;
		}
		case BINRELOP_NOTEQUALITY:{
			return("NOTEQUALITY\0");
			break;
		}
		case DATATYPE_USERDEFINED:{
			return("USERDEFINED\0");
			break;
		}
		case DATATYPE_DYNAMIC:{
			return("DYNAMIC\0");
			break;
		}
		case DATATYPE_OBJECT:{
			return("OBJECT\0");
			break;
		}
		case DATATYPE_DECIMAL:{
			return("DECIMAL\0");
			break;
		}
		case DATATYPE_FLOAT:{
			return("FLOAT\0");
			break;
		}
		case DATATYPE_DOUBLE:{
			return("DOUBLE\0");
			break;
		}
		case DATATYPE_STRING:{
			return("STRING\0");
			break;
		}
		case DATATYPE_CHAR:{
			return("CHAR\0");
			break;
		}
		case DATATYPE_INT:{
			return("INT\0");
			break;
		}
		case DATATYPE_OTHER:{
			return("DATATYPEOTHER\0");
			break;
		}
		case DATATYPE_VOID:{
			return("VOID\0");
			break;
		}
		case IDENTIFIER_ENUMERATION:{
			return("ENUMERATION\0");
			break;
		}
		case IDENTIFIER_STRUCT:{
			return("STRUCT\0");
			break;
		}
		case IDENTIFIER_PACKAGE:{
			return("PACKAGE\0");
			break;
		}
		case IDENTIFIER_NAMESPACE:{
			return("NAMESPACE\0");
			break;
		}
		case IDENTIFIER_CLASS:{
			return("CLASS\0");
			break;
		}
		case IDENTIFIER_FUNCTION:{
			return("FUNCTION\0");
			break;
		}
		case IDENTIFIER_VARIABLE:{
			return("VARIABLE\0");
			break;
		}
		case OPERATOR_TERNARY:{
			return("TERNARYOP\0");
			break;
		}
		case OPERATOR_BINARYMAT:{
			return("BINARYMATOP\0");
			break;
		}
		case OPERATOR_BINARYREL:{
			return("BINARYRELOP\0");
			break;
		}
		case OPERATOR_UNARYREL:{
			return("UNARYRELOP\0");
			break;
		}
		case OPERATOR_UNARYMAT:{
			return("UNARYMATOP\0");
			break;
		}
		case CONTAINER_PACKAGE:{
			return("PACKAGE\0");
			break;
		}
		case CONTAINER_NAMESPACE:{
			return("NAMESPACE\0");
			break;
		}
		case CONTAINER_CLASS:{
			return("CLASS\0");
			break;
		}
		case CONTAINER_ENUM:{
			return("ENUMERATION\0");
			break;
		}
		case CONTAINER_STRUCT:{
			return("STRUCT\0");
			break;
		}
		case MODIFIER_UNSIGNED:{
			return("UNSIGNED\0");
			break;
		}
		case MODIFIER_SIGNED:{
			return("SIGNED\0");
			break;
		}
		case MODIFIER_CONST:{
			return("CONST\0");
			break;
		}
		case MODIFIER_SHORT:{
			return("SHORT\0");
			break;
		}
		case MODIFIER_LONG:{
			return("LONG\0");
			break;
		}
		case MODIFIER_STATIC:{
			return("STATIC\0");
			break;
		}
		case MODIFIER_VOLATILE:{
			return("VOLATILE\0");
			break;
		}
		case MODIFIER_EXTERN:{
			return("EXTERN\0");
			break;
		}
		case SPL_PREPROCESSOR:{
			return("PREPROCESSORDIR\0");
			break;
		}
		case SPL_RANGEOPERATOR:{
			return("RANGEOPERATOR\0");
			break;
		}
		case SPL_PERIOD:{
			return("PERIOD\0");
			break;
		}
		case SPL_STRUCTREFACCESS:{
			return("STRUCTREFACCESS\0");
			break;
		}
		case SPL_QUESTIONMARK:{
			return("QUESTIONMARK\0");
			break;
		}
		case SPL_SCOPERESOLUTION:{
			return("SCOPERESOLUTION\0");
			break;
		}
		case SPL_COLON:{
			return("COLON\0");
			break;
		}
		case SPL_COMMA:{
			return("COMMA\0");
			break;
		}
		case SPL_RIGHTSQUARE:{
			return("RIGHTSQUARE\0");
			break;
		}
		case SPL_LEFTSQUARE:{
			return("LEFTSQUARE\0");
			break;
		}
		case SPL_RIGHTBRACE:{
			return("RIGHTBRACE\0");
			break;
		}
		case SPL_LEFTBRACE:{
			return("LEFTBRACE\0");
			break;
		}
		case SPL_RIGHTPARANTHESIS:{
			return("RIGHTPARANTHESIS\0");
			break;
		}
		case SPL_AMPERSAND:{
			return("AMPERSAND\0");
			break;
		}
		case SPL_LEFTPARANTHESIS:{
			return("LEFTPARANTHESIS\0");
			break;
		}
		case PREPROCESSOR_DEFINED:{
			return("PREPROCDEFINED\0");
			break;
		}
		case PREPROCESSOR_ERROR:{
			return("PREPROCERROR\0");
			break;
		}
		case PREPROCESSOR_ELIF:{
			return("PREPROCELIF\0");
			break;
		}
		case PREPROCESSOR_ELSE:{
			return("PREPROCELSE\0");
			break;
		}
		case PREPROCESSOR_IFNDEF:{
			return("PREPROCIFNDEF\0");
			break;
		}
		case PREPROCESSOR_ENDIF:{
			return("PREPROCENDIF\0");
			break;
		}
		case PREPROCESSOR_UNDEF:{
			return("PREPROCUNDEF\0");
			break;
		}
		case PREPROCESSOR_IFDEF:{
			return("PREPROCIFDEF\0");
			break;
		}
		case PREPROCESSOR_IF:{
			return("PREPROCIF\0");
			break;
		}
		case PREPROCESSOR_DEFINE:{
			return("PREPROCDEFINE\0");
			break;
		}
		case PREPROCESSOR_INCLUDE:{
			return("PREPROCINCLUDE\0");
			break;
		}
		case PREPROCESSOR_PRAGMA:{
			return("PREPROCPRAGMA\0");
			break;
		}
		case CONSTANT_NULL:{
			return("NULL\0");
			break;
		}
		default:{
			return("NA");
			break;
		}
	}
	return(NULL);
}

typedef struct SymbolTableEntry
{
	char Identifier[51];
	TOKEN_MASTER AccessSpecifier;
	TOKEN_MASTER IdentifierType;
	uint8_t IdentifierCharacteristics;
	uint8_t PointerLevel;
	TOKEN_MASTER DataType;
	uint8_t scopelevel;
	char* OtherDataType;
	uint32_t IdentifierSize;
	char Scope[51];
}SYMBOL;

typedef struct SymbolList
{
	struct SymbolList* next;
	SYMBOL* data;
}SYMBOL_LIST;

typedef struct SymbolTable
{
	SYMBOL_LIST* list[TABLESIZE];
}SYMBOL_TABLE;

SYMBOL_TABLE* GetSymbolTableNode()
{
	SYMBOL_TABLE* node = (SYMBOL_TABLE*)malloc(sizeof(SYMBOL_TABLE));
	int i = 0;
	for(i = 0;i < TABLESIZE;i++)
	{
		node->list[i] = NULL;
	}
	return(node);
}

SYMBOL_LIST* GetSymbolListNode(SYMBOL* t)
{
	SYMBOL_LIST* temp = (SYMBOL_LIST*)malloc(sizeof(SYMBOL_LIST));
	temp->data = t;
	temp->next = NULL;
	return(temp);
}

typedef struct Trie
{
	struct Trie* n[256];
	uint8_t c[256];
}TRIE;

typedef struct StackItem
{
	void* data;
	struct StackItem* next;
	struct StackItem* prev;
}STACK_ITEM;

typedef struct Stack
{
	STACK_ITEM* top;
	STACK_ITEM* head;
}* STACK;

STACK GetStackNode()
{
	STACK node = (STACK)malloc(sizeof(struct Stack));
	node->top = NULL;
	node->head = NULL;
	return(node);
}

STACK_ITEM* GetStackItemNode(void* data)
{
	STACK_ITEM* node = (STACK_ITEM*)malloc(sizeof(STACK_ITEM));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return(node);
}

void InsertInStack(STACK_ITEM** head, void* data, STACK_ITEM** top)
{
	if(*head == NULL)
	{
		*top = GetStackItemNode(data);
		*head = *top;
	}
	STACK_ITEM* temp = *top;
	temp->next = GetStackItemNode(data);
	temp->next->prev = temp;
	*top = temp->next;
}

void* DeleteFromStack(STACK_ITEM** head, STACK_ITEM** top)
{
	if(*head == NULL)
	{
		return(NULL);
	}
	STACK_ITEM* tofree = *top;
	void* toreturn = tofree->data;
	*top = (*top)->prev;
	if(*top == NULL)
	{
		*head = NULL;
	}
	free(tofree);
	return(toreturn);
}

void Push(STACK s, void* data)
{
	if(s == NULL)
	{
		return;
	}
	InsertInStack(&(s->head), data, &(s->top));
}

void* Pop(STACK s)
{
	if(s == NULL)
	{
		return(NULL);
	}
	return(DeleteFromStack(&(s->head), &(s->top)));
}

typedef struct Token
{
	char a[51];
	int line, col;
	uint8_t c;
}TOKEN;

typedef struct TokenList
{
	struct TokenList* next;
	struct TokenList* prev;
	struct TokenList* sublist;
	CONSTRUCT_TYPE type;
	TOKEN* data;
}TOKENLIST;

TRIE* GetTrieNode()
{
	TRIE* node = (TRIE*)malloc(sizeof(TRIE));
	int i = 0;
	for(i = 0;i < 256;i++)
	{
		node->n[i] = NULL;
		node->c[i] = TOKENMASTER_NA;
	}
	return(node);
}

TOKENLIST* GetTokenListNode(TOKEN* t)
{
	TOKENLIST* temp = (TOKENLIST*)malloc(sizeof(TOKENLIST));
	temp->data = t;
	temp->next = NULL;
	temp->prev = NULL;
	temp->sublist = NULL;
	temp->type = CONSTRUCT_NA;
	return(temp);
}

uint32_t GetDataSize(TOKEN_MASTER type, uint32_t size)
{
	switch(type)
	{
		case DATATYPE_VOID:{
			return(size * sizeof(void));
			break;
		}
		case DATATYPE_INT:{
			return(size * sizeof(int));
			break;
		}
		case DATATYPE_CHAR:{
			return(size * sizeof(char));
			break;
		}
		case DATATYPE_FLOAT:{
			return(size * sizeof(float));
			break;
		}
		case DATATYPE_DOUBLE:{
			return(size * sizeof(double));
			break;
		}
		case DATATYPE_STRING:{
			return(size * sizeof(char));
			break;
		}
		case DATATYPE_DECIMAL:{
			return(size * (4 * sizeof(int)));
			break;
		}
		case DATATYPE_USERDEFINED:{
			return(size);
			break;
		}
		default:{
			return(size * sizeof(void));
			break;
		}
	}
	return(0);
}

int PrintHelp()
{
	printf("\n%s\n", "GOOP()\n");
	printf("%s\n", "NAME");
	printf("\t%s\n", "goop : GNU Object Oriented Programming Compiler\n");
	printf("%s\n", "SYNOPSIS");
	printf("\t%s\n", "goop [-t|-T|-s|-S] [@filename]\n");
	printf("%s\n", "DESCRIPTION");
	printf("\t%s\n", "When you invoke GOOP, it normally does preprocessing, lexical");
	printf("\t%s\n", "analysis, parsing and execution of the input file and generates");
	printf("\t%s\n", "an output file. A token file and symbol file can also be generated");
	printf("\t%s\n", "(see options), containing the tokens list entries and symbol table");
	printf("\t%s\n", "entries respectively, which are used by the compiler during");
	printf("\t%s\n", "compilation.\n");
	printf("%s\n", "OPTIONS");
	printf("\t%s\n", "[-t] [-T] : Tells the compiler to generate a token file with file name");
	printf("\t%s\n", "[@filename] and file extension [.tok] that contains the tokens");
	printf("\t%s\n", "generated by the compiler in the tokens list during compilation.\n");
	printf("\t%s\n", "[-s] [-S] : Tells the compiler to generate a symbol file with file name");
	printf("\t%s\n", "[@filename] and file extension [.sym] that contains the symbols");
	printf("\t%s\n", "generated by the compiler in the symbols table during compilation.\n");
	printf("%s\n", "ARGUMENT");
	printf("\t%s\n", "[@filename] : The full name of the input file to be executed by the");
	printf("\t%s\n", "compiler i.e. [file_path/file_name.file_extension] should be provided");
	printf("\t%s\n", "after options have been mentioned. If the compiler file (goop.exe)");
	printf("\t%s\n", "is in the same directory as the present working directory, only the");
	printf("\t%s\n", "basename i.e. [file_name.file_extension] is required.\n");
	printf("%s\n", "AUTHOR");
	printf("\t%s\n", "Krishna Birla (krishnabirla16@gmail.com)");
	printf("\t%s\n", "All Rights Reserved (c) 2019");
	printf("%s\n", "END");
	return(0);
}

int CompStr(char* a, char* b)
{
	if(a == NULL || b == NULL)
	{
		return(1);
	}
	int j = 0;
	while(a[j] == b[j])
	{
		if(b[j] == '\0')
		{
			break;
		}
		j++;
	}
	return((a[j] == b[j]) ? 1 : 0);
}

void CpyStr(char* a, char* b)
{
	if(a == NULL || b == NULL)
	{
		return;
	}
	int i = 0;
	while(b[i] != '\0')
	{
		a[i] = b[i];
		i++;
	}
	a[i] = '\0';
}

int StrToNum(char* a)
{
	if(a == NULL)
	{
		return(0);
	}
	int ans = 0, i = 0;
	while(a[i] != '\0')
	{
		ans = ans * 10 + (a[i] - 48);
	}
	return(ans);
}

int LenStr(char* a)
{
	if(a == NULL)
	{
		return(0);
	}
	int i = 0;
	while(a[i] != '\0')
	{
		i++;
	}
	return(i);
}

int LenNum(int n)
{
	int i = 0;
	if(n == 0)
	{
		return(1);
	}
	if(n == INT_MIN)
	{
		return(11);
	}
	if(n < 0)
	{
		i++;
		n *= -1;
	}
	while(n > 0)
	{
		n /= 10;
		i++;
	}
	return(i);
}

int SymbolHash(char* c)
{
	if(c == NULL)
	{
		return(-1);
	}
	int val = 0, i = 0;
	while(c[i] != '\0')
	{
		val += ((int)c[i]) * (i + 1);
		i++;
	}
	return(val % TABLESIZE);
}

int IsChar(char c)
{
	return(((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) ? 1 : 0);
}

int IsNum(char c)
{
	return((c >= '0' && c <= '9') ? 1 : 0);
}

RAW_TYPE GetType(char c)
{
	if(IsChar(c) || IsNum(c))
	{
		return(RAW_CHARSCOREDIGIT);
	}
	if(c == ' ' || c == '\t' || c == '\n' || c == '\r')
	{
		return(RAW_ESCAPECHARS);
	}
	if(c == ';')
	{
		return(RAW_SEMICOLON);
	}
	if(c == '(')
	{
		return(RAW_OPENBRACKET1);
	}
	if(c == '{')
	{
		return(RAW_OPENBRACKET2);
	}
	if(c == '[')
	{
		return(RAW_OPENBRACKET3);
	}
	if(c == ')')
	{
		return(RAW_CLOSEBRACKET1);
	}
	if(c == '}')
	{
		return(RAW_CLOSEBRACKET2);
	}
	if(c == ']')
	{
		return(RAW_CLOSEBRACKET3);
	}
	return(RAW_OTHER);
}

TOKENLIST* InsertInTokenList(TOKENLIST* head, TOKEN* t)
{
	if(head == NULL)
	{
		return(GetTokenListNode(t));
	}
	TOKENLIST* prev = head;
	TOKENLIST* temp = head;
	while(temp != NULL)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = GetTokenListNode(t);
	prev->next->prev = prev;
	return(head);
}

void InsertInTokenSubList(TOKENLIST* head, TOKEN* t)
{
	head->sublist = InsertInTokenList(head->sublist, t);
}

TOKEN* FormToken(char a[], int line, int col, uint8_t tokentype)
{
	TOKEN* t = (TOKEN*)malloc(sizeof(TOKEN));
	CpyStr(t->a, a);
	t->line = line;
	t->col = col;
	t->c = tokentype;
	return(t);
}

uint8_t FormCharacteristics(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h)
{
	uint8_t ans = 0x00;
	ans = (a != 0) ? (ans | BIT_EXTERN) : (ans & (~BIT_EXTERN));
	ans = (b != 0) ? (ans | BIT_VOLATILE) : (ans & (~BIT_VOLATILE));
	ans = (c != 0) ? (ans | BIT_CONST) : (ans & (~BIT_CONST));
	ans = (d != 0) ? (ans | BIT_STATIC) : (ans & (~BIT_STATIC));
	ans = (e != 0) ? (ans | BIT_POINTER) : (ans & (~BIT_POINTER));
	ans = (f != 0) ? (ans | BIT_ARRAY) : (ans & (~BIT_ARRAY));
	ans = (g != 0) ? (ans | BIT_SIGNED) : (ans & (~BIT_SIGNED));
	ans = (h != 0) ? (ans | BIT_UNSIGNED) : (ans & (~BIT_UNSIGNED));
	return(ans);
}

SYMBOL* FormSymbol(char id[], TOKEN_MASTER access, TOKEN_MASTER type, uint8_t charac, uint8_t pLevel, TOKEN_MASTER datatype, char* othertype, uint32_t size, char scope[51], uint8_t scopelevel)
{
	SYMBOL* node = (SYMBOL*)malloc(sizeof(SYMBOL));
	CpyStr(node->Identifier, id);
	node->IdentifierType = type;
	node->IdentifierCharacteristics = charac;
	node->AccessSpecifier = access;
	node->IdentifierSize = ((charac & BIT_POINTER) ? sizeof(void*) : GetDataSize(datatype, size));
	node->PointerLevel = pLevel;
	node->DataType = datatype;
	node->scopelevel = scopelevel;
	CpyStr(node->OtherDataType, othertype);
	CpyStr(node->Scope, scope);
	return(node);
}

SYMBOL_LIST* InsertInSymbolList(SYMBOL_LIST* head, SYMBOL* t)
{
	if(head == NULL)
	{
		return(GetSymbolListNode(t));
	}
	SYMBOL_LIST* prev = head;
	SYMBOL_LIST* temp = head;
	while(temp != NULL)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = GetSymbolListNode(t);
	return(head);
}

void InsertInSymbolTable(SYMBOL_TABLE* tbl, SYMBOL* sym)
{
	int hval = SymbolHash(sym->Identifier);
	tbl->list[hval] = InsertInSymbolList(tbl->list[hval], sym);
}

void InsertInTrie(TRIE* root, char a[], uint8_t tokentype)
{
	int i = 0;
	TRIE* prev = root;
	for(i = 0;i < LenStr(a);i++)
	{
		if(root->n[a[i]] == NULL)
		{
			root->n[a[i]] = GetTrieNode();
		}
		prev = root;
		root = root->n[a[i]];
	}
	prev->c[a[i - 1]] = tokentype;
}

TRIE* MakeTrie()
{
	#ifdef ANSIC_LANG_COMPILER
	uint8_t dic[][51] = {";\0", {TOKEN_SEMICOLON}, \
						 ":\0", {SPL_COLON}, \
						 "?\0", {SPL_QUESTIONMARK}, \
						 "->\0", {SPL_STRUCTREFACCESS}, \
						 "(\0", {SPL_LEFTPARANTHESIS}, \
						 ")\0", {SPL_RIGHTPARANTHESIS}, \
						 ",\0", {SPL_COMMA}, \
						 "{\0", {SPL_LEFTBRACE}, \
						 "}\0", {SPL_RIGHTBRACE}, \
						 "[\0", {SPL_LEFTSQUARE}, \
						 "]\0", {SPL_RIGHTSQUARE}, \
						 "=\0", {BINMATOP_ASSIGNMENT}, \
						 ".\0", {SPL_PERIOD}, \
						 "...\0", {SPL_RANGEOPERATOR}, \
						 "==\0", {BINRELOP_EQUALITY}, \
						 "!=\0", {BINRELOP_NOTEQUALITY}, \
						 ">\0", {BINRELOP_GREATER}, \
						 "<\0", {BINRELOP_LESSER}, \
						 ">=\0", {BINRELOP_GREATEROREQUAL}, \
						 "<=\0", {BINRELOP_LESSEROREQUAL}, \
						 "+=\0", {BINMATOP_ADDANDASSIGN}, \
						 "-=\0", {BINMATOP_SUBTRACTANDASSIGN}, \
						 "*=\0", {BINMATOP_MULTIPLYANDASSIGN}, \
						 "/=\0", {BINMATOP_DIVIDEANDASSIGN}, \
						 "%=\0", {BINMATOP_MODULUSANDASSIGN}, \
						 "|=\0", {BINMATOP_ORANDASSIGN}, \
						 "&=\0", {BINMATOP_ANDANDASSIGN}, \
						 "^=\0", {BINMATOP_XORANDASSIGN}, \
						 "++\0", {UNMATOP_INCREAMENT}, \
						 "--\0", {UNMATOP_DECREAMENT}, \
						 "+\0", {BINMATOP_ADDITION}, \
						 "-\0", {BINMATOP_SUBTRACTION}, \
						 "*\0", {BINMATOP_MULTIPLICATION}, \
						 "/\0", {BINMATOP_DIVISION}, \
						 "%\0", {BINMATOP_MODULUS}, \
						 "^\0", {BINMATOP_XOR}, \
						 "|\0", {BINMATOP_ARITHMATICOR}, \
						 "&\0", {BINMATOP_ARITHMATICAND}, \
						 "||\0", {BINRELOP_LOGICALOR}, \
						 "&&\0", {BINRELOP_LOGICALAND}, \
						 "~\0", {UNMATOP_ARITHMATICNOT}, \
						 "!\0", {UNRELOP_LOGICALNOT}, \
						 "<<\0", {BINMATOP_LEFTSHIFT}, \
						 ">>\0", {BINMATOP_RIGHTSHIFT}, \
						 "#\0", {SPL_PREPROCESSOR}, \
						 "const\0", {MODIFIER_CONST}, \
						 "volatile\0", {MODIFIER_VOLATILE}, \
						 "static\0", {MODIFIER_STATIC}, \
						 "extern\0", {MODIFIER_EXTERN}, \
						 "int\0", {DATATYPE_INT}, \
						 "void\0", {DATATYPE_VOID}, \
						 "#include\0", {PREPROCESSOR_INCLUDE}, \
						 "#define\0", {PREPROCESSOR_DEFINE}, \
						 "#error\0", {PREPROCESSOR_ERROR}, \
						 "#pragma\0", {PREPROCESSOR_PRAGMA}, \
						 "#if\0", {PREPROCESSOR_IF}, \
						 "#else\0", {PREPROCESSOR_ELSE}, \
						 "#elif\0", {PREPROCESSOR_ELIF}, \
						 "#endif\0", {PREPROCESSOR_ENDIF}, \
						 "#undef\0", {PREPROCESSOR_UNDEF}, \
						 "#ifdef\0", {PREPROCESSOR_IFDEF}, \
						 "#ifndef\0", {PREPROCESSOR_IFNDEF}, \
						 "main\0", {KEYWORD_MAIN}, \
						 "char\0", {DATATYPE_CHAR}, \
						 "double\0", {DATATYPE_DOUBLE}, \
						 "unsigned\0", {MODIFIER_UNSIGNED}, \
						 "signed\0", {MODIFIER_SIGNED}, \
						 "long\0", {MODIFIER_LONG}, \
						 "short\0", {MODIFIER_SHORT}, \
						 "float\0", {DATATYPE_FLOAT}, \
						 "return\0", {KEYWORD_RETURN}, \
						 "FILE\0", {DATATYPE_OTHER}, \
						 "NULL\0", {CONSTANT_NULL}, \
						 "if\0", {KEYWORD_IF}, \
						 "else\0", {KEYWORD_ELSE}, \
						 "switch\0", {KEYWORD_SWITCH}, \
						 "scanf\0", {KEYWORD_SCANF}, \
						 "case\0", {KEYWORD_CASE}, \
						 "printf\0", {KEYWORD_PRINTF}, \
						 "break\0", {KEYWORD_BREAK}, \
						 "continue\0", {KEYWORD_CONTINUE}, \
						 "default\0", {KEYWORD_DEFAULT}, \
						 "for\0", {KEYWORD_FOR}, \
						 "do\0", {KEYWORD_DO}, \
						 "while\0", {KEYWORD_WHILE}, \
						 "struct\0", {KEYWORD_STRUCT}, \
						 "enum\0", {KEYWORD_ENUM}, \
						 "calloc\0", {KEYWORD_CALLOC}, \
						 "malloc\0", {KEYWORD_MALLOC}, \
						 "realloc\0", {KEYWORD_REALLOC}, \
						 "free\0", {KEYWORD_FREE}, \
						 "sizeof\0", {KEYWORD_SIZEOF}, \
						 "typedef\0", {KEYWORD_TYPEDEF}, \
						 "puts\0", {KEYWORD_PUTS}, \
						 "gets\0", {KEYWORD_GETS}, \
						 "fprintf\0", {KEYWORD_FPRINTF}, \
						 "fscanf\0", {KEYWORD_FSCANF}, \
						 "fseek\0", {KEYWORD_FSEEK}, \
						 "fopen\0", {KEYWORD_FOPEN}, \
						 "fclose\0", {KEYWORD_FCLOSE}, \
						 "END\0"};
	#endif /* ANSIC_LANG_COMPILER */
	TRIE* root = GetTrieNode();
	int i = 0;
	while(dic[2 * i][0] != 'E')
	{
		InsertInTrie(root, dic[2 * i], dic[2 * i + 1][0]);
		i++;
	}
	return(root);
}

uint8_t SearchInTrie(TRIE* root, char a[])
{
	int i;
	TRIE* prev = root;
	for(i = 0;i < LenStr(a);i++)
	{
		if(root->n[a[i]] == NULL)
		{
			return(TOKENMASTER_NA);
		}
		prev = root;
		root = root->n[a[i]];
	}
	return(prev->c[a[i - 1]]);
}

char* TokenToString(TOKEN* t)
{
	char* temptoken = GetTokenMasterType(t->c);
	int n = 1 + LenStr(t->a) + 2 + 5 + LenNum(t->line) + 2 + 4 + LenNum(t->col) + 2 + LenStr(temptoken) + 1 + 1;
	char* temp = (char*)malloc(sizeof(char) * n);
	temp[0] = '<';
	int i = 0, j = 0;
	for(i = 1, j = 0;j < LenStr(t->a);i++, j++)
	{
		temp[i] = t->a[j];
	}
	temp[i++] = ',';
	temp[i++] = ' ';
	temp[i++] = 'L';
	temp[i++] = 'i';
	temp[i++] = 'n';
	temp[i++] = 'e';
	temp[i++] = ' ';
	int x = t->line;
	j = i + LenNum(t->line) - 1;
	while(x > 0)
	{
		temp[j--] = (x % 10) + 48;
		x /= 10;
	}
	i += LenNum(t->line);
	temp[i++] = ',';
	temp[i++] = ' ';
	temp[i++] = 'C';
	temp[i++] = 'o';
	temp[i++] = 'l';
	temp[i++] = ' ';
	x = t->col;
	j = i + LenNum(t->col) - 1;
	while(x > 0)
	{
		temp[j--] = (x % 10) + 48;
		x /= 10;
	}
	i += LenNum(t->col);
	temp[i++] = ',';
	temp[i++] = ' ';
	for(j = 0;j < LenStr(temptoken);i++, j++)
	{
		temp[i] = temptoken[j];
	}
	temp[i++] = '>';
	temp[i++] = '\0';
	return(temp);
}

void PrintTokenList(TOKENLIST* head, FILE* op)
{
	if(!op)
	{
		return;
	}
	fprintf(op, "<lexeme, line no, col no, type>\n\n");
	while(head != NULL)
	{
		char* temp = TokenToString(head->data);
		fprintf(op, "%s\n", temp);
		free(temp);
		head = head->next;
	}
}

void DestroyTokenList(TOKENLIST* head)
{
	if(head == NULL)
	{
		return;
	}
	DestroyTokenList(head->sublist);
	TOKENLIST* temp;
	while(head != NULL)
	{
		temp = head->next;
		free(head->data);
		free(head);
		head = temp;
	}
}

void DestroyTrie(TRIE* root)
{
	if(root == NULL)
	{
		return;
	}
	int i;
	for(int i = 0;i < 256;i++)
	{
		DestroyTrie(root->n[i]);
	}
	free(root);
}

TOKENLIST* GenerateTokenList(FILE* fp)
{
	TRIE *root = MakeTrie();
	TOKENLIST *head = NULL;
	int line = 1, col = 0, marker = 0;
	char c = '\0', buf[51] = {'\0'};
	while((c = getc(fp)) != EOF && ++col)
	{
		marker = 0;
		if(c == '#')
		{
			int templine = line, tempcol = col;
			buf[marker++] = c;
			while((c = getc(fp)) != EOF && ++col)
			{
				if(GetType(c) == RAW_ESCAPECHARS)
				{
					if(c == '\n')
					{
						line++;
						col = 0;
					}
					break;
				}
				buf[marker++] = c;
			}
			buf[marker++] = '\0';
			TOKEN_MASTER tempc = SearchInTrie(root, buf);
			if(tempc == TOKENMASTER_NA)
			{	
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, TOKEN_SPECIALCHAR));
			}
			else
			{
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, tempc));
			}
		}
		if(c == '\'')
		{
			int templine = line, tempcol = col;
			while((c = getc(fp)) != EOF && ++col)
			{
				if(c == '\'')
				{
					break;
				}
				if(c == '\n')
				{
					line++;
					col = 0;
				}
				else
				{
					buf[marker++] = c;
				}
			}
			buf[marker++] = '\0';
			head = InsertInTokenList(head, FormToken(buf, templine, tempcol, CONSTANT_CHAR));
		}
		else if(c == '\"')
		{
			int templine = line, tempcol = col;
			while((c = getc(fp)) != EOF && ++col)
			{
				if(c == '\"')
				{
					break;
				}
				if(c == '\n')
				{
					line++;
					col = 0;
				}
				else
				{
					buf[marker++] = c;
				}
			}
			buf[marker++] = '\0';
			head = InsertInTokenList(head, FormToken(buf, templine, tempcol, CONSTANT_STR));
		}
		else if(c == '/')
		{
			int templine = line;
			int tempcol = col;
			buf[marker++] = c;
			c = getc(fp);
			col++;
			if(c == '\n')
			{
				line++;
				col = 0;
			}
			else if(c == EOF)
			{
				break;
			}
			else if(c == '/')
			{
				while((c = getc(fp)) != EOF && ++col)
				{
					if(c == '\n')
					{
						line++;
						col = 0;
						break;
					}
				}
			}
			else if(c == '*')
			{
				while((c = getc(fp)) != EOF && ++col)
				{
					if(c == '\n')
					{
						line++;
						col = 0;
					}
					else if(c == '*')
					{
						c = getc(fp);
						col++;
						if(c == '\n')
						{
							line++;
							col = 0;
						}
						if(c == '/')
						{
							break;
						}
					}
				}
			}
			else
			{
				fseek(fp, -1, SEEK_CUR);
				if(col == 0)
				{
					line--;
				}
				col--;
				while((c = getc(fp)) != EOF && ++col)
				{
					if(GetType(c) == RAW_CHARSCOREDIGIT || GetType(c) == RAW_ESCAPECHARS)
					{
						if(c == '\n')
						{
							line++;
							col = 0;
							break;
						}
						fseek(fp, -1, SEEK_CUR);
						if(col == 0)
						{
							line--;
						}
						col--;
						break;
					}
					buf[marker++] = c;
				}
				buf[marker++] = '\0';
				TOKEN_MASTER tempc = SearchInTrie(root, buf);
				if(tempc == TOKENMASTER_NA)
				{
					head = InsertInTokenList(head, FormToken(buf, templine, tempcol, TOKEN_SPECIALCHAR));
				}
				else
				{
					head = InsertInTokenList(head, FormToken(buf, templine, tempcol, tempc));
				}
			}
		}
		else if(IsChar(c))
		{
			int templine = line, tempcol = col;
			buf[marker++] = c;
			while((c = getc(fp)) != EOF && ++col)
			{
				if(GetType(c) != RAW_CHARSCOREDIGIT)
				{
					break;
				}
				buf[marker++] = c;
			}
			buf[marker++] = '\0';
			fseek(fp, -1, SEEK_CUR);
			if(col == 0)
			{
				line--;
			}
			col--;
			TOKEN_MASTER tempc = SearchInTrie(root, buf);
			if(tempc == TOKENMASTER_NA)
			{
				InsertInTrie(root, buf, TOKEN_IDENTIFIER);
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, TOKEN_IDENTIFIER));
			}
			else
			{
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, tempc));
			}
		}
		else if(IsNum(c))
		{
			int templine = line, tempcol = col;
			buf[marker++] = c;
			while((c = getc(fp)) != EOF && ++col)
			{
				if(!IsNum(c))
				{
					break;
				}
				buf[marker++] = c;
			}
			buf[marker] = '\0';
			fseek(fp, -1, SEEK_CUR);
			if(col == 0)
			{
				line--;
			}
			col--;
			TOKEN_MASTER tempc = SearchInTrie(root, buf);
			if(tempc == TOKENMASTER_NA)
			{
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, CONSTANT_NUM));
			}
			else
			{
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, tempc));
			}
		}
		else
		{
			if(GetType(c) == RAW_ESCAPECHARS)
			{
				if(c == '\n')
				{
					line++;
					col = 0;
				}
				continue;
			}
			int templine = line, tempcol = col;
			buf[marker++] = c;
			RAW_TYPE type = GetType(c);
			while((c = getc(fp)) != EOF && ++col)
			{
				if(type != GetType(c))
				{
					if(c == '\n')
					{
						line++;
						col = 0;
					}
					break;
				}
				buf[marker++] = c;
			}
			buf[marker++] = '\0';
			fseek(fp, -1, SEEK_CUR);
			if(col == 0)
			{
				line--;
			}
			col--;
			TOKEN_MASTER tempc = SearchInTrie(root, buf);
			if(tempc == TOKENMASTER_NA)
			{
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, TOKEN_SPECIALCHAR));
			}
			else
			{
				head = InsertInTokenList(head, FormToken(buf, templine, tempcol, tempc));
			}
		}
		if(col < 0)
		{
			col = 0;
		}
		if(c == EOF)
		{
			break;
		}
	}
	DestroyTrie(root);
	return(head);
}

TOKENLIST* ModifyTokenList(TOKENLIST* head)
{
	return(head);
}

int main(int args, char* argv[])
{
	int i = 0, GENERATE_TOKEN_FILE = 0, GENERATE_SYMBOL_FILE = 0;
	if(args <= 1)
	{
		printf("goop: fatal error: no input file\n");
		printf("Compilation terminated\n\nHint:\n");
		printf("\t%s\n", "Provide a read enabled input file and try again\n\tFor detailed manual, try 'goop --help'");
		return(0);
	}
	for(i = 1;i < args && argv[i][0] == '-';i++)
	{
		if(CompStr(argv[i], "--help") == 1)
		{
			return(PrintHelp());
		}
		else if((CompStr(argv[i], "-t") | CompStr(argv[i], "-T")) == 1)
		{
			GENERATE_TOKEN_FILE = 1;
		}
		else if((CompStr(argv[i], "-s") == 1 | CompStr(argv[i], "-S")) == 1)
		{
			GENERATE_SYMBOL_FILE = 1;
		}
		else
		{
			printf("-bash: fatal error: wrong options format\n");
			printf("Execution terminated\n\nHint:\n");
			printf("\t%s\n", "Provide valid options and try again\n\tFor detailed manual, try 'goop --help'");
			return(0);
		}
	}
	FILE *fp = fopen(argv[args - 1], "r"), *op = NULL, *os = NULL;
	if(!fp)
	{
		if(i != args)
		{
			printf("goop: error: '%s': no such file or directory\n", argv[args - 1]);
		}
		printf("goop: fatal error: no input file\n");
		printf("Compilation terminated\n\nHint:\n");
		printf("\t%s\n", "Provide a read enabled input file and try again\n\tFor detailed manual, try 'goop --help'");
		return(0);
	}
	if(GENERATE_TOKEN_FILE)
	{
		char filename[101] = {'\0'};
		for(i = 0;argv[args - 1][i] != '.';i++)
		{
			filename[i] = argv[args - 1][i];
		}
		filename[i++] = '.';
		filename[i++] = 't';
		filename[i++] = 'o';
		filename[i++] = 'k';
		filename[i++] = '\0';
		op = fopen(filename, "w");
	}
	if(GENERATE_SYMBOL_FILE)
	{
		char filename[101] = {'\0'};
		for(i = 0;argv[args - 1][i] != '.';i++)
		{
			filename[i] = argv[args - 1][i];
		}
		filename[i++] = '.';
		filename[i++] = 's';
		filename[i++] = 'y';
		filename[i++] = 'm';
		filename[i++] = '\0';
		os = fopen(filename, "w");
	}
	TOKENLIST *head = GenerateTokenList(fp);
	PrintTokenList(head, op);
	head = ModifyTokenList(head);
	SYMBOL_TABLE* symtbl = GetSymbolTableNode();
	uint8_t inProcess = 0;
	CONSTRUCT_TYPE ctype = CONSTRUCT_NA;
	char Identifier[51] = "";
    TOKEN_MASTER AccessSpecifier = TOKENMASTER_NA;
    TOKEN_MASTER IdentifierType = TOKENMASTER_NA;
    uint8_t IdentifierCharacteristics = 0;
    uint8_t PointerLevel = 0;
    TOKEN_MASTER DataType = DATATYPE_OTHER;
    char* OtherDataType = NULL;
    uint32_t IdentifierSize = 1;
    char scope[51] = "Global\0";
    char PrevScope[51] = "";
    uint8_t scopelevel = 0;
	while(head != NULL)
	{
		TOKEN *t = head->data;
		switch(GetTokenType(t->c))
		{
			case TOKENTYPE_ACCESSSPECIFIER:{
				if(ctype != CONSTRUCT_NA)
				{
					if(CompStr(scope, PrevScope) != 1)
					{
						CpyStr(PrevScope, scope);
						printf("%s: In scope '%s'\n", argv[args - 1], scope);
					}
					printf("%s: error: %d:%d: Wrong access specifier usage\n\n", argv[args - 1], t->line, t->col);
					break;
				}
				if(inProcess == 0)
				{
					inProcess = 1;
				}
				if(AccessSpecifier == TOKENMASTER_NA)
				{
					AccessSpecifier = t->c;
				}
				else
				{
					if(CompStr(scope, PrevScope) != 1)
					{
						CpyStr(PrevScope, scope);
						printf("%s: In scope of '%s'\n", argv[args - 1], scope);
					}
					if(AccessSpecifier == t->c)
					{
						printf("%s: error: %d:%d: Duplicate access specifier\n\n", argv[args - 1], t->line, t->col);
					}
					else
					{
						printf("%s: error: %d:%d: Ambiguous access specifier\n\n", argv[args - 1], t->line, t->col);
					}
				}
				break;
			}
			case TOKENTYPE_MODIFIER:{
				if(ctype != CONSTRUCT_NA)
				{
					if(CompStr(scope, PrevScope) != 1)
					{
						CpyStr(PrevScope, scope);
						printf("%s: In scope of '%s'\n", argv[args - 1], scope);
					}
					printf("%s: error: %d:%d: Wrong modofier usage\n\n", argv[args - 1], t->line, t->col);
					break;
				}
				if(inProcess == 0)
				{
					inProcess = 1;
				}
				switch(t->c)
				{
					case MODIFIER_VOLATILE:{
						if((IdentifierCharacteristics & BIT_VOLATILE))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Duplicate volatile modifier\n\n", argv[args - 1], t->line, t->col);
						}
						else
						{
							IdentifierCharacteristics |= BIT_VOLATILE;
						}
						break;
					}
					case MODIFIER_STATIC:{
						if((IdentifierCharacteristics & BIT_STATIC))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Duplicate static modifier\n", argv[args - 1], t->line, t->col);
						}
						else
						{
							IdentifierCharacteristics |= BIT_STATIC;
						}
						break;
					}
					case MODIFIER_CONST:{
						if((IdentifierCharacteristics & BIT_CONST))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Duplicate const modifier\n", argv[args - 1], t->line, t->col);
						}
						else
						{
							IdentifierCharacteristics |= BIT_CONST;
						}
						break;
					}
					case MODIFIER_EXTERN:{
						if(!(IdentifierCharacteristics & BIT_EXTERN) && (IdentifierCharacteristics & (~BIT_EXTERN)))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Wrong extern usage\n", argv[args - 1], t->line, t->col);
						}
						else if((IdentifierCharacteristics & BIT_EXTERN))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Duplicate extern modifier\n", argv[args - 1], t->line, t->col);
						}
						else
						{
							IdentifierCharacteristics |= BIT_EXTERN;
						}
						break;
					}
					case MODIFIER_SIGNED:{
						if((IdentifierCharacteristics & BIT_SIGNED))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Duplicate signed modifier\n", argv[args - 1], t->line, t->col);
						}
						else if((IdentifierCharacteristics & BIT_UNSIGNED))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Ambiguous sign modifier\n", argv[args - 1], t->line, t->col);
						}
						else
						{
							IdentifierCharacteristics |= BIT_SIGNED;
						}
						break;
					}
					case MODIFIER_UNSIGNED:{
						if((IdentifierCharacteristics & BIT_UNSIGNED))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Duplicate unsigned modifier\n", argv[args - 1], t->line, t->col);
						}
						else if((IdentifierCharacteristics & BIT_SIGNED))
						{
							if(CompStr(scope, PrevScope) != 1)
							{
								CpyStr(PrevScope, scope);
								printf("%s: In scope of '%s'\n", argv[args - 1], scope);
							}
							printf("%s: error: %d:%d: Ambiguous sign modifier\n", argv[args - 1], t->line, t->col);
						}
						else
						{
							IdentifierCharacteristics |= BIT_UNSIGNED;
						}
						break;
					}
				}
				break;
			}
			case TOKENTYPE_DATATYPE:{
				if(inProcess == 0)
				{
					inProcess = 1;
				}
				break;
			}
			case TOKENTYPE_IDENTIFIER:{
				if(AccessSpecifier == TOKENMASTER_NA)
				{
					AccessSpecifier = ACCESSSPECIFIER_PRIVATE;
				}
				break;
			}
			case TOKENTYPE_SPECIALCHAR:{
				break;
			}
			case TOKENTYPE_PREPROCESSOR:{
				break;
			}
			case TOKENTYPE_OPERATOR:{
				break;
			}
			case TOKENTYPE_SEMICOLON:{
				CpyStr(Identifier, "");
				inProcess = 0;
				ctype = CONSTRUCT_NA;
    			AccessSpecifier = TOKENMASTER_NA;
    			IdentifierType = TOKENMASTER_NA;
    			IdentifierCharacteristics = 0;
    			PointerLevel = 0;
    			DataType = DATATYPE_OTHER;
    			OtherDataType = NULL;
    			IdentifierSize = 1;
				break;
			}
			case TOKENTYPE_CONTAINER:{
				break;
			}
			case TOKENTYPE_KEYWORD:{
				break;
			}
			case TOKENTYPE_CONSTANT:{
				break;
			}
			default:{
				break;
			}
		}
		head = head->next;
	}
	DestroyTokenList(head);
	fclose(fp);
	if(op)
	{
		fclose(op);
	}
	if(os)
	{
		fclose(os);
	}
	return(0);
}