#include <stdlib.h>
#include <stdio.h>

#include <nyalang/ast.h>

#define ALLOC(_type) check_null_malloc(malloc(sizeof(_type)))

static inline __attribute__((always_inline)) void *check_null_malloc(void *ptr) {
    if (!ptr) {
	puts("malloc failed");
	exit(1);
    }
    return ptr;
}


Expression *new_binary_expression(Expression *left, Expression *right, ExpressionOp op)
{
    Expression *exp = ALLOC(Expression);

    exp->type = ET_BINARYEXP;
    exp->content.binary_exp.left = left;
    exp->content.binary_exp.right = right;

    return exp;
}


Expression *new_variable_expression(Variable *var)
{
    Expression *exp = ALLOC(Expression);

    exp->type = ET_VARIABLE;
    exp->content.var = var;

    return exp;
}

Expression *new_literal_expression(Literal *lit)
{
    Expression *exp = ALLOC(Expression);

    exp->type = ET_LITERAL;
    exp->content.lit = lit;

    return exp;
}

Expression *new_call_expression(Variable *func)
{
    Expression *exp = ALLOC(Expression);

    exp->type = ET_CALL;
    exp->content.call.func = func;

    return exp;
}

Literal *new_int_literal(IntToken token)
{
    Literal *lit = ALLOC(Literal);
    lit->type = LT_INTEGER;
    lit->value.integer = token.value;
    return lit;
}

Literal *new_str_literal(StrToken token)
{
    Literal *lit = ALLOC(Literal);
    lit->type = LT_STRING;
    lit->value.string = token.value;
    return lit;
}

Variable *new_variable(IdentToken token)
{
    Variable *var = ALLOC(Variable);
    var->name = token.name;
    return var;
}

Statement *new_assign_statment(Variable *var, Expression *exp)
{
    Statement *stmt = ALLOC(Statement);

    stmt->type = ST_ASSIGN;
    stmt->content.assignment.var = var;
    stmt->content.assignment.exp = exp;
    return stmt;
}

Statement *new_vardecl_statement(Variable *var, Expression *opt_exp)
{
    Statement *stmt = ALLOC(Statement);

    stmt->type = ST_VARDECL;
    stmt->content.variable_declaration.var = var;
    stmt->content.variable_declaration.opt_exp = opt_exp;
    return stmt;
}

Statement *new_funcdecl_statement(Variable *func, StatementList *body)
{
    Statement *stmt = ALLOC(Statement);

    stmt->type = ST_FUNCDECL;
    stmt->content.function_declaration.func = func;
    stmt->content.function_declaration.body = body;
    return stmt;
}

Statement *new_call_statement(Variable *func)
{
    Statement *stmt = ALLOC(Statement);

    stmt->type = ST_CALL;
    stmt->content.call.func = func;
    return stmt;
}

StatementList *new_statement_list(Statement *self, StatementList *next)
{
    StatementList *list = ALLOC(StatementList);
    list->self = self;
    list->next = next;
    return list;
}

