#include <stdio.h>
#include "ast_tools.h"

static void print_stmt_list(StatementList *list);

static void print_var(Variable *var)
{
    printf("%s", var->name);
}

static void print_literal(Literal *literal)
{
    switch (literal->type) {
    case LT_INTEGER:
	printf("%ld", literal->value.integer);
	break;
    case LT_STRING:
	printf("\"%s\"", literal->value.string);
	break;
    }
}


static void print_exp(Expression *exp)
{
    printf("Expression(");
    switch (exp->type) {
    case ET_LITERAL:
	printf("LIT,");
	print_literal(exp->content.lit);
	break;
    case ET_VARIABLE:
	printf("VAR,");
	print_var(exp->content.var);
	break;
    case ET_CALL:
	printf("CALL,");
	print_var(exp->content.call.func);
	break;
    case ET_BINARYEXP:
	printf("BINARYEXP,");
	print_exp(exp->content.binary_exp.left);
	printf(",OP,");
	print_exp(exp->content.binary_exp.right);
	break;
    }

    printf(")");
}

static void print_stmt(Statement *statement)
{
    printf("Statement(");
    switch (statement->type) {
    case ST_ASSIGN:
	printf("ASSIGN,");
	print_var(statement->content.assignment.var);
	printf(",");
	print_exp(statement->content.assignment.exp);
	break;
    case ST_FUNCDECL:
	printf("FUNCDECL,");
	print_var(statement->content.function_declaration.func);
	printf(",");
	print_stmt_list(statement->content.function_declaration.body);
	break;
    case ST_VARDECL:
	printf("VARDECL,");
	print_var(statement->content.variable_declaration.var);
	printf(",");
	if (statement->content.variable_declaration.opt_exp)
	    print_exp(statement->content.variable_declaration.opt_exp);
	else printf("NULL");
	break;
    case ST_CALL:
	printf("CALL,");
	print_var(statement->content.call.func);
	break;
    default:
	printf("default??");
	break;
    }
    printf(")");
}

static void print_stmt_list(StatementList *list)
{
    printf("StatementList(");
    while (list) {
	print_stmt(list->self);
	printf(",");
	list = list->next;
    }
    printf("NULL");
    printf(")");
}

void print_ast(NyaProgram *prog)
{
    print_stmt_list(prog);
    printf("\n");
}

