%option pointer
%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nyalang/ast.h>
#include "y.tab.h"

size_t cur_line = 1;
void lexical_error(size_t line, char *msg);

%}

DIGIT [0-9]
LETTER [a-zA-Z]

%%

[\r\t\ ] {  }

\n {
    cur_line++;
    }

\/\/[^\n]* { /*comment*/ }


"func" { yylval.token.line = cur_line; return FUNCKW; }
"if" { yylval.token.line = cur_line; return IFKW; }
"else" { yylval.token.line = cur_line; return ELSEKW; }
"var" { yylval.token.line = cur_line; return VARKW; }
"return" { yylval.token.line = cur_line; return RETKW; }

"(" { yylval.token.line = cur_line; return LPAREN; }
")" { yylval.token.line = cur_line; return RPAREN; }
"{" { yylval.token.line = cur_line; return LBRACE; }
"}" { yylval.token.line = cur_line; return RBRACE; }
":" { yylval.token.line = cur_line; return COLON; }
";" { yylval.token.line = cur_line; return SEMICLN; }
"," { yylval.token.line = cur_line; return COMMA; }
"=" { yylval.token.line = cur_line; return ASSIGN;}

"+" { yylval.token.line = cur_line; return PLUSOP; }
"-" { yylval.token.line = cur_line; return MINUSOP; }
"*" { yylval.token.line = cur_line; return MULOP; }
"/" { yylval.token.line = cur_line; return DIVOP; }
"==" { yylval.token.line = cur_line; return EQOP; }
"!=" { yylval.token.line = cur_line; return NEQOP; }
"||" { yylval.token.line = cur_line; return OROP; }
"&&" { yylval.token.line = cur_line; return ANDOP; }
"!" { yylval.token.line = cur_line; return NEGOP; }
">" { yylval.token.line = cur_line; return GTOP; }
"<" { yylval.token.line = cur_line; return LTOP; }
">=" { yylval.token.line = cur_line; return GTEOP; }
"<=" { yylval.token.line = cur_line; return LTEOP; }

{DIGIT}+ {
	    yylval.intToken.line = cur_line;
	    yylval.intToken.value = atoi(yytext);
	    return INTLIT;
	    }
\"[^\"\n]*\" { yylval.strToken.line = cur_line;
		yylval.strToken.value = malloc(yyleng-1);
		strncpy(yylval.strToken.value, &yytext[1], yyleng-2);
		return STRLIT;
	    }
\'[^\'\n]*\' { yylval.strToken.line = cur_line;
		yylval.strToken.value = malloc(yyleng-1);
		strncpy(yylval.strToken.value, &yytext[1], yyleng-2);
		return STRLIT;
	    }

{LETTER}({LETTER}|{DIGIT}|_)* {
	yylval.identToken.line = cur_line;
	yylval.identToken.name = malloc(yyleng);
	strncpy(yylval.identToken.name, yytext, yyleng);
	return IDENT;
	}

. {
    lexical_error(cur_line, yytext);
    //yyterminate();
    return ERR;
    }

%%

void lexical_error(size_t line, char *msg) {
    fprintf(stderr, "unrecognized token at line %ld: %s\n", line, msg);
}

#define LOG(_n)	\
case _n:	\
    printf("%s at line %ld\n", #_n, cur_line);	\
    break;

