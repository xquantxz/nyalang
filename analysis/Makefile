
CFLAGS += -I../include
PARSER_OBJS := y.tab.o main.o ast.o ast_tools.o
LEXER_OBJS := lex.yy.o
LEX := flex
YACC := yacc

__all: libnyalex.a nyaparser

nyaparser: libnyalex.a $(PARSER_OBJS)
	$(CC) $^ libnyalex.a -o $@

parser_src y.tab.h y.tab.c:
	$(YACC) --debug -d parser.y

libnyalex.a: sym_header $(LEXER_OBJS)
	ar rcs $@ $(LEXER_OBJS)

sym_header: parser_src

lex.yy.c:
	$(LEX) scanner.l

clean:
	rm -rf y.tab.h y.tab.c *.o *.gv nyaparser
	rm -rf lex.yy.c libnyalex.a


.PHONY: clean src nyaparser sym_header

