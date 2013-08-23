#include "h/pyunfo_objlist_iter.h"

PyObject* PyUNFO_ObjListIter_new(PyTypeObject *type,
                                 PyObject *args, PyObject *kwds)
{
    (void)args;
    (void)kwds;
    PyUNFO_ObjListIter *self;

    self = (PyUNFO_ObjListIter*) type->tp_alloc(type, 0);
    return (PyObject*) self;
}
void PyUNFO_ObjListIter_dealloc(PyObject *self) {
    Py_TYPE(self)->tp_free((PyObject*)self);
}

int PyUNFO_ObjListIter_init(PyUNFO_ObjListIter *self,
                             PyObject *args,
                             PyObject *kwds) {
    (void)args;
    (void)kwds;

    self->it = NULL;
    self->pos = 0;
    return 0;
}

PyObject* PyUNFO_ObjListIter_iternext(PyObject *self) {
    PyObject *ret;
    if (((PyUNFO_ObjListIter*)self)->it) {
        ret = pyobjlist_getitem(((PyUNFO_ObjListIter*)self)->seq,
                                 ((PyUNFO_ObjListIter*)self)->pos);
    }
    if (((PyUNFO_ObjListIter*)self)->it) {
        ((PyUNFO_ObjListIter*)self)->it = ((PyUNFO_ObjListIter*)self)->it->next;
        ((PyUNFO_ObjListIter*)self)->pos += 1;
    } else {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
    return ret;
}

PyObject * PyUNFO_ObjListIter_getattr(PyObject * self, char * attr) {
    return PyObject_GetAttrString(self, attr);
}

PyMemberDef PyUNFO_ObjListIter_members[] = {
    {NULL}};

PyMethodDef PyUNFO_ObjListIter_methods[] = {
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_ObjListIter_Type = {
    PY_OBJ_HEAD_INIT
    "libunfo.ObjListIter",   /*tp_name*/
    sizeof(PyUNFO_ObjListIter), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    PyUNFO_ObjListIter_dealloc,    /*tp_dealloc*/
    0,                         /*tp_print*/
    &PyUNFO_ObjListIter_getattr,   /*tp_getattr*/
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
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Unfo ObjList Iterator",  /* tp_doc */
    0,                          /* tp_traverse */
    0,                          /* tp_clear */
    0,                          /* tp_richcompare */
    0,                          /* tp_weaklistoffset */
    0,//PyCOMPSCtoPySeq_getiter,    /* tp_iter */
    PyUNFO_ObjListIter_iternext,   /* tp_iternext */
    PyUNFO_ObjListIter_methods,/* tp_methods */
    PyUNFO_ObjListIter_members,/* tp_members */
    0,                          /* tp_getset */
    0,                          /* tp_base */
    0,                          /* tp_dict */
    0,                          /* tp_descr_get */
    0,                          /* tp_descr_set */
    0,                          /* tp_dictoffset */
    (initproc)PyUNFO_ObjListIter_init,  /* tp_init */
    0,                              /* tp_alloc */
    PyUNFO_ObjListIter_new,             /* tp_new */};

