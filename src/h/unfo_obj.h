#ifndef UNFO_OBJECT_H
#define UNFO_OBJECT_H

#include "unfo_mm.h"
#include "unfo_utils.h"

#define UNFO_Object_HEAD UNFO_RefC *refc;\
                         UNFO_ObjectInfo *obj_info;

typedef struct UNFO_Object UNFO_Object;
typedef struct UNFO_ObjectInfo UNFO_ObjectInfo;
typedef struct UNFO_Packed UNFO_Packed;
typedef struct UNFO_Num UNFO_Num;
typedef struct UNFO_Str UNFO_Str;


struct UNFO_ObjectInfo {
    size_t obj_size;
    void (*constructor)(UNFO_Object*, UNFO_Object **);
    void (*destructor)(UNFO_Object*);
    UNFO_Object* (*deep_copy)(UNFO_Object*);
    signed char (*obj_cmp)(UNFO_Object*, UNFO_Object*);
    char* (*to_str)(UNFO_Object*);
};

struct UNFO_Object {
    UNFO_RefC *refc;
    UNFO_ObjectInfo *obj_info;
};

struct UNFO_Num {
    UNFO_Object_HEAD
    int val;
};

struct UNFO_Str {
    UNFO_Object_HEAD
    char *val;
};


UNFO_Object* unfo_object_create(UNFO_ObjectInfo *obj_info, UNFO_Object **args);
void unfo_object_destroy(UNFO_Object *unfo_obj);
void unfo_object_destroy_v(void *unfo_obj);
UNFO_Object* unfo_object_copy(UNFO_Object *unfo_obj);
signed char unfo_object_cmp(UNFO_Object *obj1, UNFO_Object *obj2);
char* unfo_object_tostr(UNFO_Object *obj1);

UNFO_Num* unfo_num(int n);
UNFO_Str* unfo_str(const char *s);

extern UNFO_ObjectInfo UNFO_Num_ObjInfo;
extern UNFO_ObjectInfo UNFO_Str_ObjInfo;

#endif
