/**
 * @file ass3_19CS30033.c
 * @author Parth Jindal, Pranav Rajput
 * @brief Group 22 
 */



#include <stdio.h>

#include "header.h"
extern char* yytext;
extern int   yylex();

int main() {
    int token;
    while (token = yylex()) {
        switch (token) {
            case SINGLE_LINE_COMMENT:
                printf("<SINGLE_LINE_COMMENT>, %d, %s\n", token, yytext);
                break;
            case MULTI_LINE_COMMENT:
                printf("<MULTI_LINE_COMMENT>, %d, %s\n", token, yytext);
                break;
            case IDENTIFIER:
                printf("<IDENTIFIER>, %d, %s\n", token, yytext);
                break;
            case INTEGER_CONSTANT:
                printf("<INTEGER_CONSTANT>, %d, %s\n", token, yytext);
                break;
            case FLOATING_CONSTANT:
                printf("<FLOATING_CONSTANT>, %d, %s\n", token, yytext);
                break;
            case CHARACTER_CONSTANT:
                printf("<CHARACTER_CONSTANT>, %d, %s\n", token, yytext);
                break;
            case STRING_LITERAL:
                printf("<STRING_LITERAL>, %d, %s\n", token, yytext);
                break;
            case PUNCTUATOR:
                printf("<PUNCTUATOR>, %d, %s\n", token, yytext);
                break;
            case KEYWORD:
                printf("<KEYWORD>, %d, %s\n", token, yytext);
                break;
            default:
                printf("Invalid Literal");
        }
    };
    return 0;
}