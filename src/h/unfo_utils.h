#ifndef UNFO_UTILS_H
#define UNFO_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

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

#define UNFO_SET_ATTR(OBJTYPE, OBJNAME, ATTR) int CONCAT(\
                                                     CONCAT(\
                                                       CONCAT(\
                                                         CONCAT(unfo_,\
                                                                OBJNAME), _),\
                                                        ATTR), _set)\
                                        (OBJTYPE * obj, const char *val){\
    if (!obj) return 0;\
    unfo_rtree_set(obj->attrs, #ATTR, (char*)val);\
    return 1;\
}

#define UNFO_GET_ATTR(OBJTYPE, OBJNAME, ATTR) char* CONCAT(\
                                                     CONCAT(\
                                                       CONCAT(\
                                                         CONCAT(unfo_,\
                                                                OBJNAME), _),\
                                                        ATTR), _get)\
                                        (OBJTYPE * obj){\
    if (!obj) return NULL;\
    return (char*) unfo_rtree_get(obj->attrs, #ATTR);\
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

#endif

