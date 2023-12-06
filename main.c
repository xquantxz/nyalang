#include <stdio.h>
#include <stdlib.h>

#include <nyalang/semantic.h>
#include <nyalang/symtable.h>
#include "analysis/ast_tools.h"
#include "analysis/y.tab.h"
#include "include/nyalang/semantic.h"
#include "include/nyalang/symtable.h"


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

    ScopeSymbolTable *symtable = new_root_symtable();

    collect_decls(program, symtable);

    fclose(yyin);
    return 0;
}

