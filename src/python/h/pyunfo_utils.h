#ifndef PYUNFO_UTILS_H
#define PYUNFO_UTILS_H

#include <Python.h>

#include "pyunfo_objlist.h"

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

#endif
