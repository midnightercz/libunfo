#include "h/pyunfo_doc.h"

PyUNFO_NEW(Doc, UNFO_Doc_ObjInfo, UNFO_Doc, PyUNFO_Doc, doc)
PyUNFO_INIT(Doc, PyUNFO_Doc)
PyUNFO_DEALLOC(Doc, PyUNFO_Doc, doc)
PyUNFO_CMP(Doc, PyUNFO_Doc, doc)

PyUNFO_GetSetObjClosure PyUNFO_DocGetSetUpdatesClosure = {
    .type = &PyUNFO_DocUpdates_Type,
    .path = (size_t[]){offsetof(PyUNFO_Doc, doc),
                       offsetof(UNFO_Doc, updates), -1}
};


PyGetSetDef PyUNFO_Doc_getset[] = {
    {"updates",
     (getter)PyUNFO_getobjlist, (setter)PyUNFO_setobjlist,
     "updates list", &PyUNFO_DocGetSetUpdatesClosure},
    {NULL}  /* Sentinel */
};

static PyMemberDef PyUNFO_Doc_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_Doc_methods[] = {
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_Doc_Type = {
    PY_OBJ_HEAD_INIT
    "libpyunfo.Doc",             /*tp_name*/
    sizeof(PyUNFO_Doc), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PyUNFO_Doc_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "doc",                         /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    &PyUNFO_Doc_cmp,               /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PyUNFO_Doc_methods,           /* tp_methods */
    PyUNFO_Doc_members,           /* tp_members */
    PyUNFO_Doc_getset,            /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_Doc_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_Doc_new,                /* tp_new */};
