#ifndef UNFO_UTILS_H
#define UNFO_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

#include "unfo_dict.h"

#define UNFO_NORETURN

#define UNFO_Check_NULL(OBJ, RET) if (OBJ == NULL) return RET;
#define UNFO_Check_Malloc(obj, ret)
#define UNFO_STR(string) #string

#define CONCAT(A,B) CONCAT2(A, B)
#define CONCAT2(A, B) A ## B

#define UNFO_CREATE_u(NAME, TYPE) void CONCAT(CONCAT(unfo_, NAME), _create_u)\
                                                        (UNFO_Object *uobj,\
                                                         UNFO_Object **args) {\
    CONCAT(CONCAT(unfo_, NAME),_create)((TYPE*)uobj, args);\
}

#define UNFO_COPY_u(NAME, TYPE) UNFO_Object* CONCAT(CONCAT(unfo_,NAME),_copy_u)\
                                                            (UNFO_Object* obj){\
  return (UNFO_Object*) CONCAT(CONCAT(unfo_, NAME),_copy) ((TYPE*)obj);\
}

#define UNFO_DESTROY_u(NAME, TYPE) void CONCAT(CONCAT(unfo_, NAME), _destroy_u)\
                                                            (UNFO_Object* obj){\
    CONCAT(CONCAT(unfo_, NAME),_destroy) ((TYPE*)obj);\
}

#define UNFO_CMP_u(NAME, TYPE) signed char CONCAT(CONCAT(unfo_, NAME), _cmp_u)\
                                                           (UNFO_Object* obj1,\
                                                            UNFO_Object* obj2){\
    return CONCAT(CONCAT(unfo_, NAME),_cmp) ((TYPE*)obj1, (TYPE*)obj2);\
}

#define UNFO_SET_ATTR(OBJTYPE, OBJNAME, ATTR) \
int CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ATTR), _set)\
                                        (OBJTYPE * obj, const char *val){\
    if (!obj) return 0;\
    unfo_rtree_set(obj->attrs, #ATTR, (char*)val);\
    return 1;\
}\
int CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ATTR), _set_u)\
                                        (UNFO_Object * obj, const char *val){\
   return CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ATTR), _set)\
                                                        ((OBJTYPE*)obj, val);\
}

#define UNFO_GET_ATTR(OBJTYPE, OBJNAME, ATTR)\
char* CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ATTR), _get)\
                                        (OBJTYPE * obj){\
    if (!obj) return NULL;\
    return (char*) unfo_rtree_get(obj->attrs, #ATTR);\
}\
char* CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ATTR), _get_u)\
                                        (UNFO_Object * obj){\
    return CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ATTR), _get)\
                                        ((OBJTYPE*)obj);\
}

#define UNFO_GETSET_ATTR(OBJTYPE, OBJNAME, ATTR) UNFO_GET_ATTR(OBJTYPE,\
                                                               OBJNAME, ATTR)\
                                                 UNFO_SET_ATTR(OBJTYPE,\
                                                               OBJNAME, ATTR)



#define UNFO_OBJLIST_APPEND(OBJTYPE, OBJNAME, LIST, ITEMNAME, ITEMTYPE)\
    int CONCAT(CONCAT(CONCAT(CONCAT(unfo_, OBJNAME), _), ITEMNAME), _append)\
                                (OBJTYPE *obj, ITEMTYPE *item) {\
        return unfo_objlist_append((UNFO_ObjList*)obj+offsetof(OBJTYPE, LIST),\
                                   (UNFO_Object*)item);\
    }

void* __unfo_str_clone(void *str);
char __unfo_iswhitespace(const char *str, int len);
int __unfo_strcmp(const char *str1, const char *str2);
char *attrs2str(UNFO_RTree *attrs, const char *kwds[], int kwds_len);

#endif

