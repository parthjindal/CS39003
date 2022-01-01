/*
Name: Parth Jindal, Pranav Rajput
Course: CS39003
Group: 
*/

%{  /* C Declarations and Definitions */
	#include <string.h>
	#include <stdio.h>
	extern int yylex();
	void yyerror(char *s);
	extern int yylineno;
	extern char *yytext;
%}

%union {
	int intValue;
	double doubleValue;
	char charValue;
	char chArr[256];
	char *stringValue;
}

//keywords
%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO ELSE
%token ENUM EXTERN REGISTER FLOAT FOR GOTO IF INLINE LONG
%token RESTRICT RETURN SHORT  SIGNED SIZEOF STATIC STRUCT SWITCH
%token INT DOUBLE TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE BOOL COMPLEX IMAGINARY

%token <charArray> IDENTIFIER
%token <stringValue> STRING_LITERAL
%token <intValue> INTEGER_CONSTANT
%token <doubleValue> FLOATING_CONSTANT
%token <charValue> CHARACTER_CONSTANT

// Comments
%token SINGLE_LINE_COMMENT
%token MULTI_LINE_COMMENT

// Punctuators and operators
%token DOT
%token ARROW
%token INCREMENT
%token DECREMENT
%token BITWISEAND
%token STAR
%token PLUS
%token MINUS
%token NOT
%token EXCLAMATION
%token DIVIDE
%token PERCENTAGE
%token LEFTSHIFT
%token RIGHTSHIFT
%token LESSTHAN
%token GREATERTHAN
%token LESSEQUAL
%token GREATEREQUAL
%token EQUAL
%token NOTEQUAL
%token XOR
%token BITWISEOR
%token AND
%token OR
%token QUESTIONMARK
%token COLON
%token SEMICOLON
%token ELLIPSIS
%token ASSIGN
%token MULTIPLYEQUAL
%token DIVIDEEQUAL
%token MODULOEQUAL
%token PLUSEQUAL
%token MINUSEQUAL
%token SHIFTLEFTEQUAL
%token SHIFTRIGHTEQUAL
%token ANDEQUAL
%token XOREQUAL
%token OREQUAL
%token COMMA
%token HASH

%nonassoc ')'
%nonassoc ELSE
%start translation_unit
%%

// 1.EXPRESSIONS

CONSTANT : INTEGER_CONSTANT 
         | FLOATING_CONSTANT 
         | CHARACTER_CONSTANT 
         ;
         
primary_expression : IDENTIFIER
				   { printf("primary_expression :- identifier\n"); }
				   | CONSTANT 
				   { printf("primary_expression :- constant\n"); }
				   | STRING_LITERAL 
				   { printf("primary_expression :- string_literal\n"); }
				   | '(' expression ')' 
				   { printf("primary_expression :- '(' expression ')'\n"); }
				   ;

postfix_expression : primary_expression 
				   { printf("postfix_expression :- primary_expression\n"); }
				   | postfix_expression '[' expression ']' 
				   { printf("postfix_expression :- postfix_expression '[' expression ']'\n"); }
				   | postfix_expression '(' argument_expression_list_opt ')' 
				   { printf("postfix_expression :- postfix_expression '(' argument_expression_list_opt ')'\n"); }
				   | postfix_expression '.' IDENTIFIER 
				   { printf("postfix_expression :- postfix_expression '.' identifier\n"); }
				   | postfix_expression ARROW IDENTIFIER 
				   { printf("postfix_expression :- postfix_expression ':-' identifier\n"); }
				   | postfix_expression INCREMENT 
				   { printf("postfix_expression :- postfix_expression '++'\n"); }
				   | postfix_expression DECREMENT 
				   { printf("postfix_expression :- postfix_expression '--'\n"); }
				   | '(' type_name ')' '{' initializer_list '}' 
				   { printf("postfix_expression :- '(' type_name ')' '{' initializer_list '}'\n"); }
				   | '(' type_name ')' '{' initializer_list COMMA '}' 
				   { printf("postfix_expression :- '(' type_name ')' '{' initializer_list ',' '}'\n"); }
				   ;

argument_expression_list_opt : /*epsilon*/
							 | argument_expression_list
							 ;

argument_expression_list : assignment_expression 
						 { printf("argument_expression_list :- assignment_expression\n"); }
						 | argument_expression_list COMMA assignment_expression 
						 { printf("argument_expression_list :- argument_expression_list ',' assignment_expression\n"); }
						 ;

unary_expression : postfix_expression 
				 { printf("unary_expression :- postfix_expression\n"); }
				 | INCREMENT unary_expression 
				 { printf("unary_expression :- '++' unary_expression\n"); }
				 | DECREMENT unary_expression 
				 { printf("unary_expression :- '--' unary_expression\n"); }
				 | unary_operator cast_expression 
				 { printf("unary_expression :- unary_operator cast_expression\n"); }
				 | SIZEOF unary_expression 
				 { printf("unary_expression :- 'sizeof' unary_expression\n"); }
				 | SIZEOF '(' type_name ')' 
				 { printf("unary_expression :- 'sizeof' '(' type_name ')'\n"); }
				 ;

unary_operator	: BITWISEAND
				{ printf("unary_operator :- '&'\n"); }
				| STAR 
				{ printf("unary_operator :- '*'\n"); }
				| PLUS 
				{ printf("unary_operator :- '+'\n"); }
				| MINUS 
				{ printf("unary_operator :- '-'\n"); }
				| NOT 
				{ printf("unary_operator :- '~'\n"); }
				| EXCLAMATION 
				{ printf("unary_operator :- '!'\n"); }
				;

cast_expression : unary_expression 
				{ printf("cast_expression :- unary_expression\n"); }
				| '(' type_name ')' cast_expression 
				{ printf("cast_expression :- '(' type_name ')' cast_expression\n"); }
				;

multiplicative_expression : cast_expression 
						  { printf("multiplicative_expression :- cast_expression\n"); }
						  | multiplicative_expression STAR cast_expression 
						  { printf("multiplicative_expression :- multiplicative_expression * cast_expression\n"); }
						  | multiplicative_expression DIVIDE cast_expression 
						  { printf("multiplicative_expression :- multiplicative_expression / cast_expression\n"); }
						  | multiplicative_expression PERCENTAGE cast_expression 
						  { printf("multiplicative_expression :- multiplicative_expression modulo cast_expression\n"); }						  
						  ;

additive_expression : multiplicative_expression 
					{ printf("additive_expression :- multiplicative_expression\n"); }
					| additive_expression PLUS multiplicative_expression 
					{ printf("additive_expression :- additive_expression '+' multiplicative_expression\n"); }
					| additive_expression MINUS multiplicative_expression 
					{ printf("additive_expression :- additive_expression '-' multiplicative_expression\n"); }
					;

shift_expression : additive_expression
				 { printf("shift_expression :- additive_expression\n"); }
				 | shift_expression LEFTSHIFT additive_expression 
				 { printf("shift_expression :- shift_expression '<<' additive_expression\n"); }
				 | shift_expression RIGHTSHIFT additive_expression 
				 { printf("shift_expression :- shift_expression '>>' additive_expression\n"); }				 
				 ;

relational_expression : shift_expression 
					  { printf("relational_expression :- shift_expression\n"); }
					  | relational_expression LESSTHAN shift_expression 
					  { printf("relational_expression :- relational_expression '<' shift_expression\n"); }
					  | relational_expression GREATERTHAN shift_expression 
					  { printf("relational_expression :- relational_expression '>' shift_expression\n"); }
					  | relational_expression LESSEQUAL shift_expression 
					  { printf("relational_expression :- relational_expression '<=' shift_expression\n"); }
					  | relational_expression GREATEREQUAL shift_expression 
					  { printf("relational_expression :- relational_expression '>=' shift_expression\n"); }
					  ;

equality_expression : relational_expression 
					{ printf("equality_expression :- relational_expression\n"); }
					| equality_expression EQUAL relational_expression 
					{ printf("equality_expression :- equality_expression '==' relational_expression\n"); }
					| equality_expression NOTEQUAL relational_expression 
					{ printf("equality_expression :- equality_expression '!=' relational_expression\n"); }					
					;

and_expression : equality_expression 
			   { printf("and_expression :- equality_expression\n"); }
			   | and_expression BITWISEAND equality_expression 
			   { printf("and_expression :- and_expression '&' equality_expression\n"); }
			   ;

exclusive_or_expression : and_expression 
						{ printf("exclusive_or_expression :- and_expression\n"); }
						| exclusive_or_expression XOR and_expression 
						{ printf("exclusive_or_expression :- exclusive_or_expression '^' and_expression\n"); }
						; 

inclusive_or_expression : exclusive_or_expression 
						{ printf("inclusive_or_expression :- exclusive_or_expression\n"); }
						| inclusive_or_expression BITWISEOR exclusive_or_expression 
						{ printf("inclusive_or_expression :- inclusive_or_expression '|' exclusive_or_expression\n"); }
						;

logical_and_expression : inclusive_or_expression 
					   { printf("logical_and_expression :- inclusive_or_expression\n"); }
					   | logical_and_expression AND inclusive_or_expression 
					   { printf("logical_and_expression :- logical_and_expression '&&' inclusive_or_expression\n"); }
					   ;

logical_or_expression : logical_and_expression
					  { printf("logical_or_expression :- logical_and_expression\n"); }
					  | logical_or_expression OR logical_and_expression 
					  { printf("logical_or_expression :- logical_or_expression '||' logical_and_expression\n"); }
					  ;

conditional_expression : logical_or_expression 
					   { printf("conditional_expression :- logical_or_expression\n"); }	
					   | logical_or_expression QUESTIONMARK expression COLON conditional_expression 
					   { printf("conditional_expression :- logical_or_expression '?' expression ':' conditional_expression\n"); }
					   ;

assignment_expression : conditional_expression 
					  { printf("assignment_expression :- conditional_expression\n"); }
					  | unary_expression assignment_operator assignment_expression 
					  { printf("assignment_expression :- unary_expression assignment_operator assignment_expression\n"); }
					  ;

assignment_operator : ASSIGN 
					{ printf("assignment_operator :- '='\n"); }
					| MULTIPLYEQUAL 
					{ printf("assignment_operator :- '*='\n"); }
					| DIVIDEEQUAL 
					{ printf("assignment_operator :- '/='\n"); }
					| MODULOEQUAL 
					{ printf("assignment_operator :- modulo= \n"); }
					| PLUSEQUAL 
					{ printf("assignment_operator :- '+='\n"); }
					| MINUSEQUAL 
					{ printf("assignment_operator :- '-='\n"); }
					| SHIFTLEFTEQUAL 
					{ printf("assignment_operator :- '<<='\n"); }
					| SHIFTRIGHTEQUAL 
					{ printf("assignment_operator :- '>>='\n"); }
					| ANDEQUAL 
					{ printf("assignment_operator :- '&='\n"); }
					| XOREQUAL 
					{ printf("assignment_operator :- '^='\n"); }
					| OREQUAL 
					{ printf("assignment_operator :- '|='\n"); }
					;

expression : assignment_expression 
		   { printf("expression :- assignment_expression\n"); }
		   | expression COMMA assignment_expression 
		   { printf("expression :- expression ',' assignment_expression\n"); }
		   ;

constant_expression : conditional_expression 
					{ printf("constant_expression :- conditional_expression\n"); }
					;

// 2.DECLARATIONS

declaration : declaration_specifiers init_declarator_list_opt SEMICOLON 
			{ printf("declaration :- declaration_specifiers init_declarator_list_opt ;\n"); }
			;

init_declarator_list_opt : 
						 | init_declarator_list
						 ;

declaration_specifiers : storage_class_specifier declaration_specifiers_opt
					   { printf("declaration_specifiers :- storage_class_specifier declaration_specifiers_opt\n"); }
					   | type_specifier declaration_specifiers_opt 
					   { printf("declaration_specifiers :- type_specifier declaration_specifiers_opt\n"); }
					   | type_qualifier declaration_specifiers_opt 
					   { printf("declaration_specifiers :- type_qualifier declaration_specifiers_opt\n"); }
					   | function_specifier declaration_specifiers_opt 
					   { printf("declaration_specifiers :- function_specifier declaration_specifiers_opt\n"); }	
					   ;

declaration_specifiers_opt : 
						   | declaration_specifiers
						   ;

init_declarator_list : init_declarator 
                     { printf("init_declarator_list :- init_declarator\n"); }
					 | init_declarator_list COMMA init_declarator
					 { printf("init_declarator_list :- init_declarator_list , init_declarator\n"); }
					 ;

init_declarator : declarator
				{ printf("init_declarator :- declarator\n"); }
                | declarator ASSIGN initializer 
				{ printf("init_declarator :- declarator = initializer\n"); }
				;

storage_class_specifier : EXTERN 
						{ printf("storage_class_specifier :- extern\n"); }
						| STATIC 
						{ printf("storage_class_specifier :- static\n"); }
						| AUTO 
						{ printf("storage_class_specifier :- auto\n"); }
						| REGISTER 
						{ printf("storage_class_specifier :- register\n"); }
						;

// Type Specifier
type_specifier : VOID 
			   { printf("type_specifier :- void\n"); }
			   | CHAR 
			   { printf("type_specifier :- char\n"); }
			   | SHORT 
			   { printf("type_specifier :- short\n"); }
			   | INT 
			   { printf("type_specifer :- int\n"); }
			   | LONG 
			   { printf("type_specifier :- long\n"); }
			   | FLOAT 
			   { printf("type_specifier :- float\n"); }
			   | DOUBLE 
			   { printf("type_specifier :- double\n"); }
			   | SIGNED 
			   { printf("type_specifier :- signed\n"); }
			   | UNSIGNED 
			   { printf("type_specifier :- unsigned\n"); }
			   | BOOL 
			   { printf("type_specifier :- bool\n"); }
			   | COMPLEX 
			   { printf("type_specifier :- complex\n"); }
			   | IMAGINARY 
			   { printf("type_specifier :- imaginary\n"); }
			   | enum_specifier 
			   { printf("type_specifer :- enum_specifier\n"); }
			   ;

specifier_qualifier_list : type_specifier specifier_qualifier_list_opt
						 { printf("specifier_qualifier_list :- type_specifier specifier_qualifier_list_opt\n"); }
						 | type_qualifier specifier_qualifier_list
						 { printf("specifier_qualifier_list :- type_qualifier specifier_qualifier_list\n"); }
						 ;

specifier_qualifier_list_opt : 
							 | specifier_qualifier_list
							 ;


enum_specifier : ENUM identifier_opt '{' enumerator_list '}'
               { printf("enum_specifier :- enum identifier_opt { enumerator_list }\n"); }
			   | ENUM identifier_opt '{' enumerator_list COMMA '}'
			   { printf("enum_specifier :- enum identifier_opt { enumerator_list , }\n"); }
			   | ENUM IDENTIFIER 
			   { printf("enum_specifier :- enum identifier\n"); }
			   ;

identifier_opt : 
			   | IDENTIFIER
			   ;

enumerator_list : enumerator 
				{ printf("enumerator_list :- enumerator\n"); }
				| enumerator_list COMMA enumerator 
				{ printf("enumerator_list :- enumerator_list , enumerator\n"); }
				;

enumerator : IDENTIFIER 
		   { printf("enumerator :- enumeration_constant\n"); }
		   | IDENTIFIER ASSIGN constant_expression 
		   { printf("enumerator :- enumeration_constant = constant_expression\n"); }
		   ;

type_qualifier : CONST 
			   { printf("type_qualifier :- const\n"); }
			   | VOLATILE 
			   { printf("type_qualifier :- volatile\n"); }
			   | RESTRICT 
			   { printf("type_qualifier :- restrict\n"); }
			   ;

function_specifier : INLINE 
				   { printf("function_specifier :- inline\n"); }
				   ;

declarator : pointer_opt direct_declarator 
		   { printf("declarator :- pointer_opt direct_declarator\n"); }
		   ;

pointer_opt : 
			| pointer
			;

direct_declarator : IDENTIFIER 
				  { printf("direct_declarator :- IDENTIFIER\n"); }
				  | '(' declarator ')' 
				  { printf("direct_declarator :- ( declarator )\n"); }
				  | direct_declarator '['  type_qualifier_list_opt assignment_expression_opt ']' 
				  { printf("direct_declarator :- direct_declarator [ type_qualifier_list_opt assignment_expression_opt ]\n"); }
				  | direct_declarator '[' STATIC type_qualifier_list_opt assignment_expression ']' 
				  { printf("direct_declarator :- direct_declarator [ static type_qualifier_list_opt assignment_expression ]\n"); }
				  | direct_declarator '[' type_qualifier_list STATIC assignment_expression ']' 
				  { printf("direct_declarator :- direct_declarator [ type_qualifier_list static assignment_expression ]\n"); }
				  | direct_declarator '[' type_qualifier_list_opt STAR ']' 
				  { printf("direct_declarator :- direct_declarator [ type_qualifier_list_opt * ]\n"); }
				  | direct_declarator '(' parameter_type_list ')' 
				  { printf("direct_declarator :- direct_declarator ( parameter_type_list )\n"); }
				  | direct_declarator '(' identifier_list_opt ')' 
				  { printf("direct_declarator :- direct_declarator ( identifier_list_opt )\n"); }
				  ;

type_qualifier_list_opt : 
						| type_qualifier_list
						;
assignment_expression_opt :  
						  | assignment_expression
						  ;						
identifier_list_opt : 
					| identifier_list 
					;

pointer : STAR type_qualifier_list_opt
		 { printf("pointer :- * type_qualifier_list_opt\n"); }
		| STAR type_qualifier_list_opt pointer 
		{ printf("pointer :- * type_qualifier_list_opt pointer\n"); }
		;

type_qualifier_list : type_qualifier
					{ printf("type_qualifier_list :- type_qualifier\n"); }
					| type_qualifier_list type_qualifier 
					{ printf("type_qualifier_list :- type_qualifier_list type_qualifier\n"); }
					;

parameter_type_list : parameter_list 
					{ printf("parameter_type_list :- parameter_list\n"); }
					| parameter_list COMMA ELLIPSIS 
					{ printf("parameter_type_list :- parameter_list , ...\n"); }
					;

parameter_list : parameter_declaration 
               { printf("parameter_list :- parameter_declaration\n"); }
			   | parameter_list COMMA parameter_declaration 
			   { printf("parameter_list :- parameter_list , parameter_declaration\n"); }
			   ;

parameter_declaration : declaration_specifiers declarator
					  { printf("parameter_declaration :- declaration_specifiers declarator\n"); }
					  | declaration_specifiers 
					  { printf("parameter_declaration :- declaration_specifiers\n"); }
					  ;

identifier_list : IDENTIFIER
				{ printf("identifier_list :- IDENTIFIER\n"); }
				| identifier_list COMMA IDENTIFIER 
				{ printf("identifier_list :- identifier_list , IDENTIFIER\n"); }
				;

type_name : specifier_qualifier_list 
		  { printf("type_name :- specifier_qualifier_list\n"); }
		  ;

initializer : assignment_expression 
			{ printf("initializer :- assignment_expression\n"); }
			| '{' initializer_list '}' 
			{ printf("initializer :- { initializer_list }\n"); }
			| '{' initializer_list COMMA '}' 
			{ printf("initializer :- { initializer_list , }\n"); }
			;

initializer_list : designation_opt initializer
				 { printf("initializer_list :- designation_opt initializer\n"); }
				 | initializer_list COMMA designation_opt initializer 
				 { printf("initializer_list :- initializer_list , designation_opt initializer\n"); }
				 ;

designation_opt :
				| designation
				;

designation : designator_list ASSIGN 
			{ printf("designation :- designator_list =\n"); }			
			;

designator_list : designator 
				{ printf("designator_list :- designator\n"); }
				| designator_list designator 
				{ printf("designator_list :- designator_list designator\n"); }
				;

designator : '[' constant_expression ']' 
		   { printf("designator :- [ constant_expression ]\n"); }
		   | DOT IDENTIFIER 
		   { printf("designator :- . IDENTIFIER\n"); }
		   ;


// 3.STATEMENTS
statement : labeled_statement
		  { printf("statement :- labeled_statement\n"); }
		  | compound_statement 
		  { printf("statement :- compound_statement\n"); }
		  | expression_statement 
		  { printf("statement :- expression_statement\n"); }
		  | selection_statement 
		  { printf("statement :- selection_statement\n"); }
		  | iteration_statement 
		  { printf("statement :- iteration_statement\n"); }
		  | jump_statement 
		  { printf("statement :- jump_statement\n"); }
		  ;

labeled_statement : IDENTIFIER COLON statement 
				  { printf("labeled_statement :- identifier : statement\n"); }
				  | CASE constant_expression COLON statement 
				  { printf("labeled_statement :- case constant_expression : statement\n"); }
				  | DEFAULT COLON statement 
				  { printf("labeled_statement :- default : statement\n"); }
				  ;

compound_statement : '{' block_item_list_opt '}' 
				   { printf("compound_statement :- { block_item_list_opt } \n"); }
				   ;

block_item_list_opt :
					| block_item_list
					;

block_item_list : block_item 
				{ printf("block_item_list :- block_item\n"); }
				| block_item_list block_item 
				{ printf("block_item_list :- block_item_list block_item\n"); }
				;

block_item : declaration
		   {printf("block_item :- declaration \n"); }
		   | statement 
		   {printf("block_item :- statement \n"); }
		   ;

expression_statement : expression_opt SEMICOLON
					 { printf("expression_statement :- expression_opt ; \n"); }
					 ;

selection_statement : IF '(' expression ')' statement
					{ printf("selection_statement :- if ( expression ) statement \n"); }
					| IF '(' expression ')' statement ELSE statement 
					{ printf("selection_statement :- if ( expression ) statement else statement \n"); }
					| SWITCH '(' expression ')' statement 
					{ printf("selection_statement :- switch ( expression ) statement \n"); }
					;

iteration_statement : WHILE '(' expression ')' statement 
					{ printf("iteration_statement :- while ( expression) statement\n"); }
                    | DO statement WHILE '(' expression ')' SEMICOLON
					{ printf("iteration_statement :- do statement while ( expression) ;\n"); } 
					| FOR '(' expression_opt SEMICOLON expression_opt SEMICOLON expression_opt ')' statement 
					{ printf("iteration_statement :- for ( expression_opt ; expression_opt ; expression_opt ) statement\n"); }
					| FOR '(' declaration expression_opt SEMICOLON expression_opt ')' statement
					{ printf("iteration_statement :- for ( declaration expression_opt ; expression_opt ) statement\n"); }
					;
expression_opt : 
			   | expression
			   ;

jump_statement : GOTO IDENTIFIER SEMICOLON
			   { printf("jump_statement :- goto identifier ;\n"); }
			   | CONTINUE SEMICOLON 
			   { printf("jump_statement :- continue ;\n"); }
			   | BREAK SEMICOLON 
			   { printf("jump_statement :- break ;\n"); }
			   | RETURN expression_opt SEMICOLON 
			   { printf("jump_statement :- return expression_opt ;\n"); }
			   ;


// 4.EXTERNAL DEFINITIONS
translation_unit : external_declaration 
				 { printf("translation_unit :- external_declaration\n"); }
				 | translation_unit external_declaration 
				 { printf("translation_unit :- translation_unit external_declaration\n"); }
				 ;

external_declaration : function_definition 
					 { printf("external_declaration :- function_definition\n"); }
				     | declaration 
					 { printf("external_declaration :- declaration\n"); }
					 ;

function_definition : declaration_specifiers declarator declaration_list_opt compound_statement 
					{ printf("function_definition\n"); }
					;

declaration_list_opt : 
					 | declaration_list
					 ;

declaration_list : declaration
				 { printf("declaration_list :- declaration\n"); }
				 | declaration_list declaration 
				 { printf("declaration_list :- declaration_list declaration\n"); }	
				 ;
%%

void yyerror(char *s) {
	printf ("Error: %s, Line no: %d, <%s>\n",s, yylineno, yytext);
}