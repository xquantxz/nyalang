CFLAGS += -I../include
PARSER_OBJS := y.tab.o ast.o ast_tools.o
LEXER_OBJS := lex.yy.o
LEX := flex
YACC := yacc

__all: libnlex.a libnparse.a

parser_src y.tab.h y.tab.c:
	$(YACC) --debug -d parser.y

libnlex.a: sym_header $(LEXER_OBJS)
	ar rcs $@ $(LEXER_OBJS)

libnparse.a: $(PARSER_OBJS)
	ar rcs $@ $(PARSER_OBJS)

sym_header: parser_src

lex.yy.c:
	$(LEX) scanner.l

clean:
	rm -rf y.tab.h y.tab.c *.o *.gv nyaparser
	rm -rf lex.yy.c libnlex.a libnparse.a

.PHONY: clean src nyaparser sym_header

