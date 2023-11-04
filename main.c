#include <stdio.h>
#include <stdlib.h>

#include "analysis/ast_tools.h"
#include "analysis/y.tab.h"

extern FILE *yyin;
extern size_t cur_line;

int yyparse(NyaProgram **program);
int yylex(void);

#define LOG(_n)	\
case _n:	\
    printf("%s at line %ld\n", #_n, cur_line);	\
    break;

int main(int argc, char **argv)
{
    int token;

    if (argc > 1) {
	char *path = argv[1];
	FILE *f = fopen(path, "r");

	if (!f) {
	    perror("fopen()");
	    return 1;
	}

	yyin = f;
    } else {
	yyin = stdin;
    }

    yydebug = 1;

    NyaProgram *program = NULL;
    int res = yyparse(&program);

    printf("prog: %p\n", program);

    if (res == 0) {
	puts("program recognized");
	print_ast(program);
    } else {
	puts("program NOT recognized");
    }

    fclose(yyin);
    return 0;
}

