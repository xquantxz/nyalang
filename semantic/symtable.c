#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>
#include <gio/gio.h>

#include <nyalang/ast.h>
#include <nyalang/symtable.h>

SymbolTable *new_symtable(void)
{
    SymbolTable *st = malloc(sizeof(SymbolTable));

    st->parent = NULL;
    st->var_symtable.entries = g_hash_table_new(g_str_hash, g_str_equal);
    st->func_symtable.entries = g_hash_table_new(g_str_hash, g_str_equal);
    return st;
}

void symtable_insert_variable(SymbolTable *st, char *ident, VariableInfo *info)
{
    gboolean new = g_hash_table_insert(st->var_symtable.entries, ident, info);
    printf("added variable %s\n", ident);

    if (!new) {
	printf("found duplicate symbol %s in scope\n", ident);
    }
}

void symtable_insert_function(SymbolTable *st, char *ident, FunctionInfo *info)
{
    gboolean new = g_hash_table_insert(st->func_symtable.entries, ident, info);
    printf("added function %s\n", ident);

    if (!new) {
	printf("found duplicate symbol %s in scope\n", ident);
    }
}

FunctionInfo *new_function_info(char *name, char *returnType)
{
    FunctionInfo *info = (FunctionInfo *)malloc(sizeof(FunctionInfo));
    info->name = name;
    info->returnType = returnType;
    info->symtable = new_symtable();

    return info;
}

VariableInfo *new_variable_info(char *name, char *type)
{
    VariableInfo *info = (VariableInfo *)malloc(sizeof(FunctionInfo));
    info->name = name;
    info->type = type;

    return info;
}

