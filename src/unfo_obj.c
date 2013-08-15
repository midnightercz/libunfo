#include "h/unfo_obj.h"

#include <math.h>
#include <stdio.h>

UNFO_Object * unfo_object_create(UNFO_ObjectInfo *obj_info, UNFO_Object **args){
    UNFO_Object *obj;
    obj = malloc(obj_info->obj_size);
     
    UNFO_Check_Malloc(obj, NULL)

    obj->obj_info = obj_info;
    obj->refc = unfo_refc_create((void*)obj,
                                 (void (*)(void*)) obj_info->destructor);
    obj_info->constructor(obj, args);
    return obj;
}

void unfo_object_destroy(UNFO_Object *unfo_obj) {
    UNFO_Check_NULL(unfo_obj, )
    if (unfo_obj->refc->ref_count)
        unfo_refc_destroy(unfo_obj->refc);
    else {
        unfo_refc_destroy(unfo_obj->refc);
        free(unfo_obj);
    }
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

signed char unfo_object_cmp(UNFO_Object *obj1, UNFO_Object *obj2) {
    if (obj1->obj_info->obj_cmp) {
        return obj1->obj_info->obj_cmp(obj1, obj2);
    } else {
        return -1;
    }
}

char* unfo_object_tostr(UNFO_Object *obj1) {
    char *ret;
    if (obj1->obj_info->to_str != NULL) {
       return obj1->obj_info->to_str(obj1);
    } else {
        ret = malloc(sizeof(char));
        ret[0]=0;
        return ret;;
    }
}


void unfo_num_create(UNFO_Num* num, UNFO_Object **args){
    if (args && args[0]->obj_info == &UNFO_Num_ObjInfo) {
        num->val = ((UNFO_Num*)args[0])->val;
    } else
        num->val = 0;
}
UNFO_CREATE_u(num, UNFO_Num)

UNFO_Num* unfo_num_copy(UNFO_Num *num) {
    return (UNFO_Num*)unfo_object_create(&UNFO_Num_ObjInfo,
                                        (UNFO_Object*[]){(UNFO_Object*)num});
}
UNFO_COPY_u(num, UNFO_Num)

void unfo_num_destroy(UNFO_Num *num){
    (void)num;
}
UNFO_DESTROY_u(num, UNFO_Num)

char* unfo_num_tostr(UNFO_Object *num) {
    char *ret;
    int x;

    if (((UNFO_Num*)num)->val == 0)
        x = 1;
    else
        x = (int)(log10(((UNFO_Num*)num)->val)) + 1;
    ret = malloc(sizeof(char)*(x+1));
    sprintf(ret, "%d", ((UNFO_Num*)num)->val);
    return ret;
}

void unfo_str_create(UNFO_Str* str, UNFO_Object **args){
    if (args && args[0]->obj_info == &UNFO_Str_ObjInfo) {
        str->val = malloc(sizeof(char) * (strlen(((UNFO_Str*)args[0])->val)+1));
        strcpy(str->val, ((UNFO_Str*)args[0])->val);
    }
}
UNFO_CREATE_u(str, UNFO_Str)

UNFO_Str* unfo_str_copy(UNFO_Str *str) {
    return (UNFO_Str*)unfo_object_copy((UNFO_Object*)str);
}

UNFO_COPY_u(str, UNFO_Str)

void unfo_str_destroy(UNFO_Str *str){
    (void)str;
    free(str->val);
}
UNFO_DESTROY_u(str, UNFO_Str)

char* unfo_str_tostr(UNFO_Object *str) {
    char *ret;
    ret = malloc(sizeof(char)*(strlen(((UNFO_Str*)str)->val)+1));
    strcpy(ret, ((UNFO_Str*)str)->val);
    return ret;
}


UNFO_Num* unfo_num(int n) {
    UNFO_Num *ret = (UNFO_Num*)unfo_object_create(&UNFO_Num_ObjInfo, NULL);
    ret->val = n;
    return ret;
}

UNFO_Str* unfo_str(const char *s) {
    UNFO_Str *ret = (UNFO_Str*)unfo_object_create(&UNFO_Str_ObjInfo, NULL);
    ret->val = malloc(sizeof(char) * ((strlen(s)+1)));
    strcpy(ret->val, s);
    return ret;
}

UNFO_ObjectInfo UNFO_Num_ObjInfo = {
    .obj_size = sizeof(UNFO_Num),
    .constructor = &unfo_num_create_u,
    .destructor = &unfo_num_destroy_u,
    .deep_copy = &unfo_num_copy_u,
    .to_str = &unfo_num_tostr
};

UNFO_ObjectInfo UNFO_Str_ObjInfo = {
    .obj_size = sizeof(UNFO_Str),
    .constructor = &unfo_str_create_u,
    .destructor = &unfo_str_destroy_u,
    .deep_copy = &unfo_str_copy_u,
    .to_str = &unfo_str_tostr
};

