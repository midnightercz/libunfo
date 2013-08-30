#ifndef PYUNFO_DOCREF_H
#define PYUNFO_DOCREF_H

#include <Python.h>
#include "structmember.h"
#include "stddef.h"

#include "23macros.h"
#include "pyunfo_utils.h"
#include "pyunfo_objlist.h"

#include "libunfo/unfo_docref.h"

typedef struct PyUNFO_DocRef {
    PyObject_HEAD
    UNFO_DocRef *ref;
} PyUNFO_DocRef;

extern PyTypeObject PyUNFO_DocRef_Type;
extern PyTypeObject PyUNFO_DocRefs_Type;

#endif



