
%{
#include <stdio.h>
#include <nyalang/ast.h>

#include "ast_tools.h"

void yyerror(NyaProgram **program, const char *msg);
int yylex(void);

%}

%union {
    struct int_token intToken;
    struct str_token strToken;
    struct ident_token identToken;
    struct token token;
    Expression *expression;
    Literal *literal;
    Variable *variable;
    TypeExpression *type;
    Statement *statement;
    StatementList *statement_list;
}

%token <token> LPAREN
%token <token> RPAREN
%token <token> LBRACK
%token <token> RBRACK
%token <token> LBRACE
%token <token> RBRACE
%token <token> SEMICLN
%token <token> COMMA
%token <token> ASSIGN
%token <token> PLUSOP
%token <token> MINUSOP
%token <token> MULOP
%token <token> COLON
%token <token> DIVOP
%token <token> EQOP
%token <token> NEQOP
%token <token> OROP
%token <token> ANDOP
%token <token> NEGOP
%token <token> GTOP LTOP GTEOP LTEOP
%token <identToken> IDENT
%token <intToken> INTLIT
%token <strToken> STRLIT
%token <token> FUNCKW
%token <token> IFKW
%token <token> ELSEKW
%token <token> VARKW
%token <token> RETKW
%token <token> ERR

%type <expression> Expression AtomicExpression PlusMinusExpression MultDivExpression BooleanExpression FunctionCall
%type <statement> Statement DeclarationStatement VariableDeclaration FunctionDeclaration AssignmentStatement SingleStatement FunctionCallStatement
%type <literal> Literal
%type <variable> Variable
%type <type> TypeExpression
%type <statement_list> NyaProgram StatementList DeclarationStatementList

%parse-param {NyaProgram **program}

%start NyaProgram

%%

NyaProgram:	DeclarationStatementList { *program = $1; };
DeclarationStatementList: /*epsilon*/ { $$ = NULL; }
			| DeclarationStatement DeclarationStatementList { $$ = new_statement_list($1, $2); };
DeclarationStatement:	FunctionDeclaration | VariableDeclaration;

VariableDeclaration:	VARKW Variable COLON TypeExpression StatementDelimiter { $$ = new_vardecl_statement($2, $4, NULL); }
			| VARKW Variable COLON TypeExpression ASSIGN Expression StatementDelimiter { $$ = new_vardecl_statement($2, $4, $6); };
FunctionDeclaration:	FUNCKW Variable LPAREN OptionalParamList RPAREN LBRACE StatementList RBRACE { $$ = new_funcdecl_statement($2, new_void_type_expression(),$7); }
		   |	FUNCKW Variable LPAREN OptionalParamList RPAREN COLON TypeExpression LBRACE StatementList RBRACE { $$ = new_funcdecl_statement($2, $7, $9); };

StatementList: /*epsilon*/ { $$ = NULL; }
	     | Statement StatementList { $$ = new_statement_list($1, $2); };

OptionalParamList:	/*epsilon*/ | ParamList;
ParamList:	Param | Param COMMA ParamList;
Param:	Variable COLON TypeExpression;

Statement:	SingleStatement;

SingleStatement:	DeclarationStatement | AssignmentStatement | FunctionCallStatement
AssignmentStatement:	Variable ASSIGN Expression StatementDelimiter { $$ = new_assign_statment($1, $3); };
FunctionCallStatement:	Variable LPAREN RPAREN StatementDelimiter { $$ = new_call_statement($1); }

IfStatement:	IFKW LPAREN Expression RPAREN Statement
		| IFKW LPAREN Expression RPAREN Statement ElseStatement;
ElseStatement: ELSEKW Statement;

ReturnStatement: RETKW Expression StatementDelimiter;

Expression:	PlusMinusExpression;
AtomicExpression:	Variable { $$ = new_variable_expression($1); }
			| Literal { $$ = new_literal_expression($1); }
			| FunctionCall
			| LPAREN Expression RPAREN { $$ = $2; };

Literal:	INTLIT { $$ = new_int_literal($1); }
		| STRLIT { $$ = new_str_literal($1); };
TypeExpression:	IDENT { $$ = new_ident_type_expression($1); }
	      | LBRACK TypeExpression SEMICLN INTLIT RBRACK { $$ = new_array_type_expression($2, $4); };

FunctionCall:	Variable LPAREN RPAREN { $$ = new_call_expression($1); };
Variable:	IDENT { $$ = new_variable($1); };
PlusMinusExpression:	PlusMinusExpression PLUSOP MultDivExpression { $$ = new_binary_expression($1, $3, EO_ADD); }
			| PlusMinusExpression MINUSOP MultDivExpression { $$ = new_binary_expression($1, $3, EO_SUB); }
			| MultDivExpression;
MultDivExpression:	MultDivExpression MULOP BooleanExpression { $$ = new_binary_expression($1, $3, EO_MUL); }
			| MultDivExpression DIVOP BooleanExpression { $$ = new_binary_expression($1, $3, EO_DIV); }
			| BooleanExpression;
BooleanExpression:	BooleanExpression ANDOP AtomicExpression { $$ = new_binary_expression($1, $3, EO_AND); }
			| BooleanExpression OROP AtomicExpression { $$ = new_binary_expression($1, $3, EO_OR); }
			| BooleanExpression GTOP AtomicExpression { $$ = new_binary_expression($1, $3, EO_GT); }
			| BooleanExpression LTOP AtomicExpression { $$ = new_binary_expression($1, $3, EO_LT); }
			| BooleanExpression GTEOP AtomicExpression { $$ = new_binary_expression($1, $3, EO_GTE); }
			| BooleanExpression LTEOP AtomicExpression { $$ = new_binary_expression($1, $3, EO_LTE); }
			| AtomicExpression;

StatementDelimiter:	SEMICLN;

%%

void yyerror(NyaProgram **program, const char *msg)
{
    fprintf(stderr, "an error occurred: %s\n", msg);
}

