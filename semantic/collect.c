#include <nyalang/symtable.h>
#include <nyalang/ast.h>

static void collect_stmt_list_decls(StatementList *list, SymbolTable *st);

static void collect_stmt_decls(Statement *stmt, SymbolTable *st)
{
    switch (stmt->type) {
    case ST_VARDECL:
    {
	char *name = stmt->content.variable_declaration.var->name;
	VariableInfo *info = new_variable_info(name, "type");
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

static void collect_stmt_list_decls(StatementList *list, SymbolTable *st)
{
    while (list != NULL) {
	Statement *stmt = list->self;
	collect_stmt_decls(stmt, st);
	list = list->next;
    }
}

void collect_decls(NyaProgram *ast, SymbolTable *st)
{
    collect_stmt_list_decls(ast, st);
}



