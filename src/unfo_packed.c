#include "h/unfo_packed.h"

void unfo_packed_create(UNFO_Packed *packed, UNFO_Object **args){
    (void) args;
    packed->len = 0;
    packed->items = NULL;
}
UNFO_CREATE_u(packed, UNFO_Packed)

UNFO_Packed* unfo_packed_copy(UNFO_Packed *packed) {
    UNFO_Packed *ret;

    ret = (UNFO_Packed*) unfo_object_copy((UNFO_Object*)packed);
    for (unsigned int i = 0; i < packed->len; i++) {
        ret->items[i] = unfo_object_copy(packed->items[i]);
    }
    return ret;
}
UNFO_COPY_u(packed, UNFO_Packed)

void unfo_packed_destroy(UNFO_Packed *packed){
    for (unsigned int i = 0; i < packed->len; i++) {
        unfo_object_destroy(packed->items[i]);
    }
    free(packed->items);
}
UNFO_DESTROY_u(packed, UNFO_Packed)


UNFO_Packed* unfo_packed_pack(int len, ...) {
    UNFO_Packed *packed;
    va_list vl;
    int i;

    va_start(vl, len);

    packed = (UNFO_Packed*)unfo_object_create(&UNFO_Packed_ObjInfo, NULL);

    for (i = 0; i < len; i++) {
        packed->items[i] = unfo_object_copy(va_arg(vl, UNFO_Object*));
    }
    return packed;
}

UNFO_ObjectInfo UNFO_Packed_ObjInfo = {
    .obj_size = sizeof(UNFO_Packed),
    .constructor = &unfo_packed_create_u,
    .destructor = &unfo_packed_destroy_u,
    .deep_copy = &unfo_packed_copy_u
};
