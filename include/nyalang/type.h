#ifndef _TYPE_H
#define _TYPE_H

#include <stdlib.h>

typedef enum {
    TK_VOID,
    TK_PRIMITIVE,
    TK_ARRAY
} TypeKind;

typedef enum {
    PTK_INT8,
    PTK_INT16,
    PTK_INT32,
    PTK_INT64
} PrimitiveTypeKind;

typedef struct _type {
    TypeKind kind;
    const char *name;

    union {
	struct {
	    PrimitiveTypeKind primitive_kind;
	} primitive;

	struct {
	    size_t length;
	    struct _type *innerType;
	} array;
    } u;
} Type;

Type *new_primitive_type(PrimitiveTypeKind kind);
Type *new_void_type(void);
Type *new_array_type(Type *innerType, size_t length);

#endif

