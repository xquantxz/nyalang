#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>
#include <gio/gio.h>

#include <nyalang/type.h>

typedef struct {
    GHashTable *entries;
} SymbolTable;

typedef SymbolTable FunctionSymbolTable;
typedef SymbolTable VariableSymbolTable;
typedef SymbolTable TypeSymbolTable;

typedef struct {
    struct ScopeSymbolTable *parent;
    FunctionSymbolTable func_symtable;
    VariableSymbolTable var_symtable;
    TypeSymbolTable type_symtable;
} ScopeSymbolTable;

ScopeSymbolTable *new_symtable(void);
ScopeSymbolTable *new_root_symtable(void);

typedef struct {
    char *name;
    char *returnType;
    SymbolTable *symtable;
} FunctionInfo;

typedef struct {
    char *name;
    Type *type;
} VariableInfo;

typedef struct {
    char *name;
    Type *type;
} TypeInfo;

FunctionInfo *new_function_info(char *name, char *returnType);
VariableInfo *new_variable_info(char *name, Type *type);
TypeInfo *new_type_info(char *name, Type *type);
void symtable_insert_variable(ScopeSymbolTable *st, char *ident, VariableInfo *info);
void symtable_insert_function(ScopeSymbolTable *st, char *ident, FunctionInfo *info);
void symtable_insert_type(ScopeSymbolTable *st, char *ident, TypeInfo *info);

/* lookup */
TypeInfo *lookup_type_symtable(ScopeSymbolTable *st, char *name);

#endif

