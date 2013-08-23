#ifndef PYUNFO_DOCUPDATE_H
#define PYUNFO_DOCUPDATE_H

#include <Python.h>
#include "structmember.h"
#include "stddef.h"

#include "23macros.h"
#include "pyunfo_utils.h"
#include "pyunfo_objlist.h"

#include "libunfo/unfo_docupdate.h"

typedef struct PyUNFO_DocUpdate {
    PyObject_HEAD
    UNFO_DocUpdate *update;
} PyUNFO_DocUpdate;


extern PyTypeObject PyUNFO_DocUpdate_Type;
extern PyTypeObject PyUNFO_DocUpdates_Type;

#endif



