#ifndef PYUNFO_DOCPKG_H
#define PYUNFO_DOCPKG_H

#include <Python.h>
#include "structmember.h"
#include "stddef.h"

#include "23macros.h"
#include "pyunfo_utils.h"
#include "pyunfo_objlist.h"

#include "libunfo/unfo_docpkg.h"

typedef struct PyUNFO_DocPkg {
    PyObject_HEAD
    UNFO_DocPkg *pkg;
} PyUNFO_DocPkg;

extern PyTypeObject PyUNFO_DocPkg_Type;
extern PyTypeObject PyUNFO_DocPkgs_Type;

#endif



