#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>
#include <gio/gio.h>

typedef struct {
    GHashTable *entries;
} VariableSymbolTable;

typedef struct {
    GHashTable *entries;
} FunctionSymbolTable;

typedef struct {
    struct SymbolTable *parent;
    FunctionSymbolTable func_symtable;
    VariableSymbolTable var_symtable;
} SymbolTable;

SymbolTable *new_symtable(void);

typedef struct {
    char *name;
    char *returnType;
    SymbolTable *symtable;
} FunctionInfo;

typedef struct {
    char *name;
    char *type;
} VariableInfo;

FunctionInfo *new_function_info(char *name, char *returnType);
VariableInfo *new_variable_info(char *name, char *type);
void symtable_insert_variable(SymbolTable *st, char *ident, VariableInfo *info);
void symtable_insert_function(SymbolTable *st, char *ident, FunctionInfo *info);

#endif

