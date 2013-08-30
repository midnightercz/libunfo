#ifndef MACROS23_H
#define MACROS23_H

#include <Python.h>

#if PY_MAJOR_VERSION >= 3
    #define MODINIT_RET_NONE return NULL
    #define PY_OBJ_HEAD_INIT PyVarObject_HEAD_INIT(NULL, 0)
    #define IS_PY3K
    #define PyINT_CHECK(OB) PyLong_Check(OB)
    #define PyINT_ASLONG(OB) PyLong_AsLong(OB)
    #define PyINT_FROM_LONG(OB) PyLong_FromLong(OB)
    #define SLICE_CAST PyObject*
    #define PYCOMPS_DICT_ITERITEMS "items"
#else
    #define MODINIT_RET_NONE return
    #define PY_OBJ_HEAD_INIT PyObject_HEAD_INIT(NULL)\
                             0,
    #define PyINT_CHECK(OB) PyInt_Check(OB)
    #define PyINT_ASLONG(OB) PyInt_AsLong(OB)
    #define PyINT_FROM_LONG(OB) PyInt_FromLong(OB)

    #define SLICE_CAST PySliceObject*
    #define PYCOMPS_DICT_ITERITEMS "iteritems"
#endif

#if PY_MAJOR_VERSION >= 3
    #define PYINIT_FUNC PyInit__libpyunfo
#else
    #define PYINIT_FUNC init_libpyunfo
#endif

#define PYTYPEOBJECT_END\
    0,\
    0,\
    0,\
    0,\
    0,\
    0,\
    0

#endif

