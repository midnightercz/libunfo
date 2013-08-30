#ifndef PYUNFO_DOC_H
#define PYUNFO_DOC_H

#include <Python.h>
#include "structmember.h"
#include "stddef.h"

#include "23macros.h"
#include "pyunfo_utils.h"
#include "pyunfo_docupdate.h"

#include "libunfo/unfo_doc.h"
#include "libunfo/unfo_parse.h"

#include "pyunfo_docupdate.h"

typedef struct PyUNFO_Doc {
    PyObject_HEAD
    UNFO_Doc *doc;
    UNFO_Log *log;
} PyUNFO_Doc;

extern PyTypeObject PyUNFO_Doc_Type;

#endif


