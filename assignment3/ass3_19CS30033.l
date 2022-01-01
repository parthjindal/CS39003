%{
    #include "header.h"    
%}

/*Regex Definitions*/
/*until newline*/
SINGLE_LINE_COMMENT     "//"[^\n]*
MULTI_LINE_COMMENT      "/*"[^"*"]*"*"("*"|([^"/*"]*[^"*"]*"*"))*"/"


/*KEYWORDS(For convenience written on different lines)*/
KEYWORD_1            "auto"|"enum"|"restrict"|"unsigned"|"break"|"extern"|"return"|"void"
KEYWORD_2            "case"|"float"|"short"|"volatile"|"char"|"for"|"signed"|"while"
KEYWORD_3            "const"|"goto"|"sizeof"|"_Bool"|"continue"|"if"|"static"|"_Complex"
KEYWORD_4            "default"|"inline"|"struct"|"_Imaginary"|"do"|"int"|"switch"|"double"
KEYWORD_5            "long"|"typedef"|"else"|"register"|"union"
KEYWORD              {KEYWORD_1}|{KEYWORD_2}|{KEYWORD_3}|{KEYWORD_4}|{KEYWORD_5}


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


S_CHAR                 {ESCAPE_SEQ}|[^("\n"|"\""|"\\")]
S_CHAR_SEQ             {S_CHAR}+
S_LITERAL              \"({S_CHAR_SEQ})\"


/*PUNCTUATORS*/
PUNCTUATOR			    "["|"]"|"("|")"|"{"|"}"|"."|"->"|"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"|"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"|"?"|":"|";"|"..."|"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="|","|"#"

WS                     [ \t\n\v\f]

%%
{SINGLE_LINE_COMMENT}     {return SINGLE_LINE_COMMENT;}
{MULTI_LINE_COMMENT}      {return MULTI_LINE_COMMENT;}
{KEYWORD}                 {return KEYWORD;}
{IDENTIFIER}              {return IDENTIFIER;}
{INTEGER_CONSTANT}        {return INTEGER_CONSTANT;}
{FLOATING_CONSTANT}       {return FLOATING_CONSTANT;}
{CHAR_CONSTANT}           {return CHARACTER_CONSTANT;}
{S_LITERAL}               {return STRING_LITERAL;}
{PUNCTUATOR}              {return PUNCTUATOR;}
{WS}                      {/*nothing*/;}
%%