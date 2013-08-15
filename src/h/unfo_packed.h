#ifndef UNFO_PACKED_H
#define UNFO_PACKED_H

#include "unfo_obj.h"
#include <stdarg.h>

struct UNFO_Packed {
    UNFO_Object_HEAD
    unsigned int len;
    UNFO_Object **items;
};

void unfo_packed_create(UNFO_Packed *packed, UNFO_Object **args);
void unfo_packed_create_u(UNFO_Object *packed, UNFO_Object **args);
void unfo_packed_destroy(UNFO_Packed *packed);
void unfo_packed_destroy_u(UNFO_Object *packed);

extern UNFO_ObjectInfo UNFO_Packed_ObjInfo;

#endif //UNFO_PACKED_H
