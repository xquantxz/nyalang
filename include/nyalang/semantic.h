#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include <nyalang/ast.h>
#include <nyalang/symtable.h>

void collect_decls(NyaProgram *ast, ScopeSymbolTable *symtable);

#endif

