#include <nyalang/symtable.h>
#include <nyalang/ast.h>

#include <stdio.h>

static Type *get_typeexp_type(TypeExpression *typeExp, ScopeSymbolTable *st) {
    switch (typeExp->kind) {
    case TEK_IDENT:;
	TypeInfo *typeInfo = lookup_type_symtable(st, typeExp->content.ident.name);
	if (typeInfo == NULL) {
	    return NULL;
	}

	return typeInfo->type;
    case TEK_ARRAY:;
	Type *type = new_array_type(
	    get_typeexp_type(typeExp->content.array.typeExp, st),
	    typeExp->content.array.length
	);

	return type;
    case TEK_VOID:
	return new_void_type();
    default:
	return NULL;
    }
}

static void collect_stmt_list_decls(StatementList *list, ScopeSymbolTable *st);

static void collect_stmt_decls(Statement *stmt, ScopeSymbolTable *st)
{
    switch (stmt->type) {
    case ST_VARDECL:
    {
	char *name = stmt->content.variable_declaration.var->name;
	VariableInfo *info = new_variable_info(name, "type");

	TypeExpression *typeExp = stmt->content.variable_declaration.typeExp;

	Type *type = get_typeexp_type(typeExp, st);
	if (!type) {
	    puts("failed to get type");
	    return;
	}

	symtable_insert_variable(st, name, info);

	break;
    }
    case ST_FUNCDECL:
    {
	char *name = stmt->content.function_declaration.func->name;
	FunctionInfo *info = new_function_info(name, "type");
	symtable_insert_function(st, name, info);

	collect_stmt_list_decls(stmt->content.function_declaration.body, st);
	break;
    }
    default:
	break;
    }
}

static void collect_stmt_list_decls(StatementList *list, ScopeSymbolTable *st)
{
    while (list != NULL) {
	Statement *stmt = list->self;
	collect_stmt_decls(stmt, st);
	list = list->next;
    }
}

void collect_decls(NyaProgram *ast, ScopeSymbolTable *st)
{
    collect_stmt_list_decls(ast, st);
}



