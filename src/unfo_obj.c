#include "h/unfo_obj.h"

UNFO_Object * unfo_object_create(UNFO_ObjectInfo *obj_info){
    UNFO_Object *obj;
    obj = malloc(obj_info->obj_size);
    UNFO_Check_Malloc(obj, NULL)

    obj->obj_info = obj_info;
    obj->refc = unfo_refc_create((void*)obj,
                                 (void (*)(void*)) obj_info->destructor);
    return obj;
}

void unfo_object_destroy(UNFO_Object *unfo_obj) {
    UNFO_Check_NULL(unfo_obj, )
    unfo_refc_destroy(unfo_obj->refc);
    //free(unfo_obj);
}

void unfo_object_destroy_v(void *unfo_obj) {
    unfo_object_destroy((UNFO_Object*) unfo_obj);
}

UNFO_Object* unfo_object_copy(UNFO_Object *unfo_obj) {
    unfo_refc_incref(unfo_obj->refc);
    return unfo_obj;
}

UNFO_Object* unfo_object_copy_deep(UNFO_Object *unfo_obj) {
   (void) unfo_obj;
    return NULL;
}

