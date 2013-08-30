#ifndef PYUNFO_UTILS_H
#define PYUNFO_UTILS_H

#include <Python.h>

#include "pyunfo_objlist.h"

#include "libunfo/unfo_obj.h"

#define CONCAT(A,B) CONCAT2(A, B)
#define CONCAT2(A, B) A ## B

#define PyUNFO_NEW(OBJNAME, CTYPE_OBJINFO, CTYPE, PTYPE, UOBJ)\
PyObject* CONCAT(PyUNFO_, CONCAT(OBJNAME, _new))(PyTypeObject *type,\
                                                 PyObject *args,\
                                                 PyObject *kwds)\
{\
    PTYPE *self;\
    (void)args;\
    (void)kwds;\
    self = (PTYPE*) type->tp_alloc(type, 0);\
    if (!self)\
        return NULL;\
    self->UOBJ = (CTYPE*) unfo_object_create(&CTYPE_OBJINFO, NULL);\
    return (PyObject*) self;\
}

#define PyUNFO_DEALLOC(OBJNAME, PTYPE, UOBJ)\
void CONCAT(PyUNFO_, CONCAT(OBJNAME, _dealloc))(PTYPE *self)\
{\
    unfo_object_destroy((UNFO_Object*)self->UOBJ);\
    Py_TYPE(self)->tp_free((PyObject*)self);\
}

#define PyUNFO_INIT(OBJNAME, PTYPE)\
int CONCAT(CONCAT(PyUNFO_, OBJNAME), _init)(PTYPE *self,\
                                            PyObject *args,\
                                            PyObject *kwds)\
{\
    (void)args;\
    (void)kwds;\
    (void)self;\
    return 0;\
}

#define PyUNFO_CMP(OBJNAME, PTYPE, UOBJ)\
    PyObject* CONCAT(CONCAT(PyUNFO_, OBJNAME), _cmp)(PyObject *self,\
                                                      PyObject *other,\
                                                      int op) {\
    if (unfo_object_cmp((UNFO_Object*)((PTYPE*)self)->UOBJ,\
                        (UNFO_Object*)((PTYPE*)other)->UOBJ)) {\
        if (op == Py_EQ) Py_RETURN_TRUE;\
        else if (op == Py_NE) Py_RETURN_FALSE;\
        else return Py_INCREF(Py_NotImplemented), Py_NotImplemented;\
    } else {\
        if (op == Py_EQ) Py_RETURN_FALSE;\
        else if (op == Py_NE) Py_RETURN_TRUE;\
        else return Py_INCREF(Py_NotImplemented), Py_NotImplemented;\
    }\
}

#define PyUNFO_STR(OBJNAME, PTYPE, UOBJ)\
    PyObject* CONCAT(CONCAT(PyUNFO_, OBJNAME), _str)(PyObject *self) {\
    PyObject *ret;\
    char *str = unfo_object_tostr((UNFO_Object*)((PTYPE*)self)->UOBJ);\
    ret = PyUnicode_FromString(str);\
    free (str);\
    return ret;\
}

#define PYUNFO_STR_GETSET_CLOSURE(PNAME, CNAME, OFFSET, ATTR)\
PyUNFO_StrGetSet_Closure CONCAT(CONCAT(CONCAT(CONCAT(PyUNFO_, PNAME),_), ATTR), _closure) = {\
    .c_offset = OFFSET,\
    .getter = CONCAT(CONCAT(CONCAT(CONCAT(&unfo_, CNAME), _), ATTR), _get_u),\
    .setter = CONCAT(CONCAT(CONCAT(CONCAT(&unfo_, CNAME), _), ATTR), _set_u),\
    .name = #ATTR\
};

typedef struct PyUNFO_StrGetSet_Closure {
    size_t c_offset;
    char* (*getter)(UNFO_Object*);
    int (*setter)(UNFO_Object*, const char*);
    const char *name;
} PyUNFO_StrGetSet_Closure;

typedef struct PyUNFO_ObjListGetSet_Closure {
    size_t c_offset;
    size_t l_offset;
    const char *name;
    PyTypeObject *list_type;
} PyUNFO_ObjListGetSet_Closure;

char * Py2Str(PyObject *obj);
PyObject* pyunfo_strattr_getter(PyObject *self, void *closure);
int pyunfo_strattr_setter(PyObject *self, PyObject *other, void *closure);

PyObject* pyunfo_objlist_getter(PyObject *self, void *closure);
int pyunfo_objlist_setter(PyObject *self, PyObject *other, void *closure);

#endif
