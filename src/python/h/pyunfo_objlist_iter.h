#ifndef PYUNFO_OBJLIST_ITER_H
#define PYUNFO_OBJLIST_ITER_H

#include <Python.h>
#include "structmember.h"

#include "23macros.h"
#include "pyunfo_objlist.h"

#include "libunfo/unfo_objlist.h"

typedef struct PyUNFO_ObjListIter{
    PyObject_HEAD
    PyObject *seq;
    UNFO_ObjListIt *it;
    long pos;
} PyUNFO_ObjListIter;

PyObject* PyUNFO_ObjListIter_new(PyTypeObject *type,
                                 PyObject *args, PyObject *kwds);
int PyUNFO_ObjListIter_init(PyUNFO_ObjListIter *self,
                             PyObject *args,
                             PyObject *kwds);

extern PyTypeObject PyUNFO_ObjListIter_Type;
#endif
