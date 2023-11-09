#ifndef _AST_H
#define _AST_H

#include <stddef.h>
#include <stdlib.h>

typedef struct str_token {
    size_t line;
    char *value;
} StrToken;

typedef struct ident_token {
    size_t line;
    char *name;
} IdentToken;

typedef struct int_token {
    size_t line;
    int value;
} IntToken;

typedef struct token {
    size_t line;
} Token;

typedef struct variable {
    char *name;
} Variable;

typedef enum {
    LT_INTEGER,
    LT_STRING,
} LiteralType;

typedef struct literal {
    LiteralType type;
    union {
	size_t integer;
	char *string;
    } value;
} Literal;

typedef enum {
    TEK_IDENT,
    TEK_ARRAY,
    TEK_VOID
} TypeExpressionKind;

typedef struct type_expression {
    TypeExpressionKind kind;
    union {
	IdentToken ident;
	struct {
	    struct type_expression *typeExp;
	    size_t length;
	} array;
    } content;
} TypeExpression;

typedef enum {
    EO_ADD,
    EO_SUB,
    EO_MUL,
    EO_DIV,
    EO_AND,
    EO_OR,
    EO_GT,
    EO_LT,
    EO_GTE,
    EO_LTE,
} ExpressionOp;

typedef enum {
    ET_LITERAL,
    ET_VARIABLE,
    ET_CALL,
    ET_BINARYEXP,
} ExpressionType;

typedef struct expression {
    ExpressionType type;
    union {
	struct {
	    ExpressionOp op;
	    struct expression *left, *right;
	} binary_exp;
	Variable *var;
	Literal *lit;
	struct {
	    Variable *func;
	} call;
    } content;
} Expression;

typedef enum {
    ST_ASSIGN,
    ST_FUNCDECL,
    ST_VARDECL,
    ST_CALL,
} StatementType;

typedef struct statement {
    StatementType type;
    union {
	struct {
	    Variable *var;
	    Expression *exp;
	} assignment;

	struct {
	    Variable *func;
	    TypeExpression *typeExp;
	    struct statment_list *body;
	} function_declaration;

	struct {
	    Variable *var;
	    TypeExpression *typeExp;
	    Expression *opt_exp;
	} variable_declaration;

	struct {
	    Variable *func;
	} call;
    } content;
} Statement;

typedef struct statement_list {
    Statement *self;
    struct statement_list *next;
} StatementList;

typedef StatementList NyaProgram;

#endif

