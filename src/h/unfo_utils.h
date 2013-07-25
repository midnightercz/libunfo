#ifndef UNFO_UTILS_H
#define UNFO_UTILS_H

#include <stdlib.h>
#include <string.h>

#define UNFO_NORETURN

#define UNFO_Check_NULL(OBJ, RET) if (OBJ == NULL) return RET;
#define UNFO_Check_Malloc(obj, ret)
#define UNFO_STR(string) #string

#define CONCAT(A,B) CONCAT2(A, B)
#define CONCAT2(A, B) A ## B

#define UNFO_CREATE_u(NAME, TYPE) UNFO_Object* CONCAT(CONCAT(unfo_, NAME), _create_u)() {\
    return (UNFO_Object*) CONCAT(CONCAT(unfo_, NAME),_create)();\
}

#define UNFO_COPY_u(NAME, TYPE) UNFO_Object* CONCAT(CONCAT(unfo_,NAME),_copy_u)\
                                                            (UNFO_Object* obj){\
  return (UNFO_Object*) CONCAT(CONCAT(unfo_, NAME),_copy) ((TYPE*)obj);\
}

#define UNFO_DESTROY_u(NAME, TYPE) void CONCAT(CONCAT(unfo_, NAME), _destroy_u)\
                                                            (UNFO_Object* obj){\
    CONCAT(CONCAT(unfo_, NAME),_destroy) ((TYPE*)obj);\
}

void* __unfo_str_clone(void *str);

#endif

