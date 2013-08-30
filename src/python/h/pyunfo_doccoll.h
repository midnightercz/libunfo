#ifndef PYUNFO_DOCCOLL_H
#define PYUNFO_DOCCOLL_H

#include <Python.h>
#include "structmember.h"
#include "stddef.h"

#include "23macros.h"
#include "pyunfo_utils.h"
#include "pyunfo_objlist.h"
#include "pyunfo_docpkg.h"

#include "libunfo/unfo_doccoll.h"

typedef struct PyUNFO_DocColl {
    PyObject_HEAD
    UNFO_DocColl *coll;
} PyUNFO_DocColl;

extern PyTypeObject PyUNFO_DocColl_Type;
extern PyTypeObject PyUNFO_DocColls_Type;

#endif



