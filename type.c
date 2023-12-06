#include <nyalang/type.h>
#include <nyalang/util.h>
#include <stddef.h>

Type *new_primitive_type(PrimitiveTypeKind kind)
{
    Type *type = ALLOC(Type);
    type->kind = TK_PRIMITIVE;
    type->u.primitive.primitive_kind = kind;
    return type;
}

Type *new_void_type(void)
{
    Type *type = ALLOC(Type);
    type->kind = TK_VOID;
    return type;
}

Type *new_array_type(Type *innerType, size_t length)
{
    Type *type = ALLOC(Type);
    type->kind = TK_ARRAY;
    type->u.array.innerType = innerType;
    type->u.array.length = length;
    return type;
}

