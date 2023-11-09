#ifndef _AST_TOOLS_H
#define _AST_TOOLS_H

#include <nyalang/ast.h>

void print_ast(NyaProgram *prog);
Expression *new_binary_expression(Expression *left, Expression *right, ExpressionOp op);
Expression *new_variable_expression(Variable *variable);
Expression *new_literal_expression(Literal *lit);
Expression *new_call_expression(Variable *func);
Literal *new_int_literal(IntToken token);
Literal *new_str_literal(StrToken token);
TypeExpression *new_ident_type_expression(IdentToken token);
TypeExpression *new_void_type_expression(void);
Variable *new_variable(IdentToken token);
Statement *new_assign_statment(Variable *var, Expression *exp);
Statement *new_vardecl_statement(Variable *var, TypeExpression *typeExp, Expression *opt_exp);
Statement *new_funcdecl_statement(Variable *var, TypeExpression *typeExp, StatementList *body);
StatementList *new_statement_list(Statement *self, StatementList *next);
Statement *new_call_statement(Variable *func);

#endif

