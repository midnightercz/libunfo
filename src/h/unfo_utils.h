#ifndef UNFO_UTILS_H
#define UNFO_UTILS_H

#define UNFO_NORETURN

#define UNFO_Check_NULL(OBJ, RET) if (OBJ == NULL) return RET;
#define UNFO_Check_Malloc(obj, ret)
#define UNFO_STR(string) #string

#define UNFO_CREATE_u(NAME, TYPE) UNFO_Object* unfo_ ## #NAME ## _create_u()\
                                  return (UNFO_Object*)unfo_ ## #NAME ## _create();

#endif

