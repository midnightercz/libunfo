#ifndef UNFO_OBJECT_H
#define UNFO_OBJECT_H

#include "unfo_mm.h"

#define UNFO_Object_HEAD UNFO_RefC *refc;\
                         UNFO_ObjectInfo *obj_info;

typedef struct UNFO_Object UNFO_Object;
typedef struct UNFO_ObjectInfo UNFO_ObjectInfo;

struct UNFO_ObjectInfo {
    size_t obj_size;
    void (*constructor)(UNFO_Object*);
    void (*destructor)(UNFO_Object*);
    UNFO_Object* (*deep_copy)(UNFO_Object*);
    int (*obj_cmp)(UNFO_Object*, UNFO_Object*);
};

struct UNFO_Object {
    UNFO_RefC *refc;
    UNFO_ObjectInfo *obj_info;
};


UNFO_Object* unfo_object_create(UNFO_ObjectInfo *obj_info);
void unfo_object_destroy(UNFO_Object *unfo_obj);
void unfo_object_destroy_v(void *unfo_obj);
UNFO_Object* unfo_object_copy(UNFO_Object *unfo_obj);

#endif
