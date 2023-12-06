#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>
#include <gio/gio.h>

#include <nyalang/ast.h>
#include <nyalang/symtable.h>
#include <nyalang/type.h>
#include <nyalang/util.h>

ScopeSymbolTable *new_symtable(void)
{
    ScopeSymbolTable *st = malloc(sizeof(ScopeSymbolTable));

    st->parent = NULL;
    st->var_symtable.entries = g_hash_table_new(g_str_hash, g_str_equal);
    st->func_symtable.entries = g_hash_table_new(g_str_hash, g_str_equal);
    st->type_symtable.entries = g_hash_table_new(g_str_hash, g_str_equal);
    return st;
}

ScopeSymbolTable *new_root_symtable(void)
{
    ScopeSymbolTable *st = new_symtable();

    Type *intType = new_primitive_type(PTK_INT32);
    Type *voidType = new_void_type();
    TypeInfo *intInfo = new_type_info("int", intType);
    TypeInfo *voidInfo = new_type_info("void", voidType);
    symtable_insert_type(st, "int", intInfo);
    symtable_insert_type(st, "void", voidInfo);
    return st;
}

void symtable_insert_variable(ScopeSymbolTable *st, char *ident, VariableInfo *info)
{
    gboolean new = g_hash_table_insert(st->var_symtable.entries, ident, info);
    printf("added variable %s\n", ident);

    if (!new) {
	printf("found duplicate symbol %s in scope\n", ident);
    }
}

void symtable_insert_function(ScopeSymbolTable *st, char *ident, FunctionInfo *info)
{
    gboolean new = g_hash_table_insert(st->func_symtable.entries, ident, info);
    printf("added function %s\n", ident);

    if (!new) {
	printf("found duplicate symbol %s in scope\n", ident);
    }
}


void symtable_insert_type(ScopeSymbolTable *st, char *ident, TypeInfo *info)
{
    gboolean new = g_hash_table_insert(st->type_symtable.entries, ident, info);
    printf("added type %s\n", ident);

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

VariableInfo *new_variable_info(char *name, Type *type)
{
    VariableInfo *info = (VariableInfo *)malloc(sizeof(VariableInfo));
    info->name = name;
    info->type = type;

    return info;
}

TypeInfo *new_type_info(char *name, Type *type)
{
    TypeInfo *info = (TypeInfo *)malloc(sizeof(TypeInfo));
    info->name = name;
    info->type = type;
    return info;
}

TypeInfo *lookup_type_symtable(ScopeSymbolTable *st, char *name)
{
    TypeInfo *info = g_hash_table_lookup(st->type_symtable.entries, name);
    if (info == NULL && st->parent != NULL)
	return lookup_type_symtable(st->parent, name);
    return info;
}

