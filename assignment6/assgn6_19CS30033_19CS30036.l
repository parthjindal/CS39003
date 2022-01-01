/*
Name: Parth Jindal, Pranav Rajput
Course: CS39003
Group: 
*/

%{
    #include <stdio.h>
    #include <string.h>
    #include "assgn6_19CS30033_19CS30036_translator.h"
    #include "assgn6_19CS30033_19CS30036.tab.h"

    extern YYSTYPE yylval;
    extern int yylineno;
%}

%option noyywrap


/*Regex Definitions*/
/*until newline*/
SINGLE_LINE_COMMENT     "//"[^\n]*
MULTI_LINE_COMMENT      "/*"[^"*"]*"*"("*"|([^"/*"]*[^"*"]*"*"))*"/"

DIGIT               [0-9]
DIGIT_SEQ           {DIGIT}+
ALPHA               [a-zA-Z_]
NON_ZERO_DIGIT      [1-9]
SIGN                [+-]
EXP_PART            ([Ee]{SIGN}?{DIGIT_SEQ})
FRACTIONAL_CONST     {DIGIT_SEQ}\.|{DIGIT_SEQ}?\.{DIGIT_SEQ}

/*IDENTIFIER*/
IDENTIFIER              {ALPHA}({ALPHA}|{DIGIT})*
NON_ZERO_INTEGER        {NON_ZERO_DIGIT}({DIGIT})*
INTEGER_CONSTANT        {NON_ZERO_INTEGER}|"0"
FLOATING_CONSTANT       ({DIGIT_SEQ}{EXP_PART})|({FRACTIONAL_CONST}{EXP_PART}?)

ENUMERATION_CONSTANT   {IDENTIFIER}
ESCAPE_SEQ             [\\][\'\"\?\\abfnrtv]
C_CHAR                 {ESCAPE_SEQ}|[^("\'"|"\\"|"\n")]
C_CHAR_SEQ             {C_CHAR}+
CHAR_CONSTANT          \'({C_CHAR_SEQ})\'
S_CHAR                 [^\"\\\n]|{ESCAPE_SEQ}
S_CHAR_SEQ             {S_CHAR}+
S_LITERAL              \"({S_CHAR_SEQ})?\"
WS                     [ \t\n\v\f]

%%

\n                          { yylineno++;}
{WS}                        { ; }
{SINGLE_LINE_COMMENT}       { ; }
{MULTI_LINE_COMMENT}        { ; }
"sizeof"                    { return SIZEOF ; }
"extern"                    { return EXTERN ; }
"static"                    { return STATIC ; }
"auto"                      { return AUTO ; }
"register"                  { return REGISTER ; }
"void"                      { return VOID ; }
"char"                      { return CHAR ; }
"short"                     { return SHORT ; }
"int"                       { return INT ; }
"long"                      { return LONG ; }
"float"                     { return FLOAT ; }
"double"                    { return DOUBLE ; }
"signed"                    { return SIGNED ; }
"unsigned"                  { return UNSIGNED ; }
"_Bool"                     { return BOOL  ; }
"_Complex"                  { return COMPLEX  ; }
"_Imaginary"                { return IMAGINARY ; }
"enum"                      { return ENUM ; }
"case"                      { return CASE ;  }
"default"                   { return DEFAULT ; }
"const"                     { return CONST ; }
"restrict"                  { return RESTRICT ; }
"volatile"                  { return VOLATILE ; }
"union"                     { return UNION ; } 
"inline"                    { return INLINE ; }
"typedef"                   { return TYPEDEF ; }
"if"                        { return IF ; }
"else"                      { return ELSE ; }
"switch"                    { return SWITCH ; }
"while"                     { return WHILE ; }
"do"                        { return DO ; }
"for"                       { return FOR ; }
"goto"                      { return GOTO ; }
"continue"                  { return CONTINUE ; }
"break"                     { return BREAK ; }
"return"                    { return RETURN ; }

{IDENTIFIER}                {   yylval.sym = ST->lookup(yytext);                
                                return IDENTIFIER ; 
                            }

{INTEGER_CONSTANT}          {   yylval.intVal = atoi(yytext);
                                return INTEGER_CONSTANT ; 
                            }
{FLOATING_CONSTANT}         {   yylval.floatVal = atof(yytext);
                                return FLOATING_CONSTANT ; 
                            }

{CHAR_CONSTANT}             {   yylval.charVal = yytext;
                                return CHARACTER_CONSTANT ; 
                            }

{S_LITERAL}                 {   yylval.charVal = yytext;
                                return STRING_LITERAL ; 
                            }

"["					{ return '['; }
"]"					{ return ']'; }
"("					{ return '('; }
")"					{ return ')'; }
"{"					{ return '{'; }
"}"					{ return '}'; }
"."					{ return DOT; }
"->"				{ return ARROW; }
"++"				{ return INCREMENT; }
"--"				{ return DECREMENT; }
"&"					{ return BITWISEAND; }
"*"					{ return STAR; }
"+"					{ return PLUS; }
"-"					{ return MINUS; }
"~"					{ return NOT; }
"!"					{ return EXCLAMATION; }
"/"					{ return DIVIDE; }
"%"					{ return PERCENTAGE; }
"<<"				{ return LEFTSHIFT; }
">>"				{ return RIGHTSHIFT; }
"<"					{ return LESSTHAN; }
">"					{ return GREATERTHAN; }
"<="				{ return LESSEQUAL; }
">=" 				{ return GREATEREQUAL; }
"=="				{ return EQUAL; }
"!="				{ return NOTEQUAL; }
"^"					{ return XOR; }
"|"					{ return BITWISEOR; }
"&&"				{ return AND; }
"||"				{ return OR; }
"?"					{ return QUESTIONMARK; }
":"					{ return COLON; }
";"					{ return SEMICOLON; }
"..."				{ return ELLIPSIS; }
"="					{ return ASSIGN; }
"*="				{ return MULTIPLYEQUAL; }
"/="				{ return DIVIDEEQUAL; }
"%="				{ return MODULOEQUAL; }
"+="				{ return PLUSEQUAL; }
"-="				{ return MINUSEQUAL; }
"<<="				{ return SHIFTLEFTEQUAL; }
">>="				{ return SHIFTRIGHTEQUAL; }
"&="				{ return ANDEQUAL; }
"^="				{ return XOREQUAL; }
"|="				{ return OREQUAL; }
","					{ return COMMA; }
"#" 				{ return HASH; }
%%
