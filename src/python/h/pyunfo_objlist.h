#ifndef PYUNFO_OBJLIST_H
#define PYUNFO_OBJLIST_H

#include <Python.h>
#include "structmember.h"

#include "23macros.h"
#include "pyunfo_utils.h"
#include "pyunfo_objlist_iter.h"

#include "libunfo/unfo_obj.h"
#include "libunfo/unfo_objlist.h"
#include "libunfo/unfo_hslist.h"


typedef UNFO_Object*(*PyObjList_accept_func)(PyObject*);
typedef PyObject*(*PyObjList_out_func)(UNFO_Object*);

typedef struct PyUNFO_ObjList_Info {
    PyObjList_out_func out_func;
    PyObjList_accept_func accept_func;
    PyTypeObject **accept_types;
} PyUNFO_ObjList_Info;

typedef struct PyUNFO_ObjList {
    PyObject_HEAD
    UNFO_ObjList *list;
    PyUNFO_ObjList_Info *item_info;
} PyUNFO_ObjList;

PyObject *pyobjlist_getitem(PyObject *self, Py_ssize_t index);

PyObject* PyUNFO_ObjList_new(PyTypeObject *type,
                             PyObject *args, PyObject *kwargs);
void PyUNFO_ObjList_dealloc(PyUNFO_ObjList *self);

int PyUNFO_ObjList_print(PyObject *self, FILE *f, int flags);
PyObject* PyUNFO_ObjList_str(PyObject *self);

extern PyTypeObject PyUNFO_ObjList_Type;

#endif
