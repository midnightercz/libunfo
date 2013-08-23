#include "h/pyunfo_docupdate.h"

PyUNFO_NEW(DocUpdate, UNFO_DocUpdate_ObjInfo,
           UNFO_DocUpdate, PyUNFO_DocUpdate, update)
PyUNFO_INIT(DocUpdate, PyUNFO_DocUpdate)
PyUNFO_DEALLOC(DocUpdate, PyUNFO_DocUpdate, update)
PyUNFO_CMP(DocUpdate, PyUNFO_DocUpdate, update)

static PyMemberDef PyUNFO_DocUpdate_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_DocUpdate_methods[] = {
    {NULL}  /* Sentinel */
};

PyGetSetDef PyUNFO_DocUpdate_getset[] = {
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_DocUpdate_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocUpdate",     /*tp_name*/
    sizeof(PyUNFO_DocUpdate),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PyUNFO_DocUpdate_dealloc, /*tp_dealloc*/
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
    0,                         /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    &PyUNFO_DocUpdate_cmp,     /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PyUNFO_DocUpdate_methods,  /* tp_methods */
    PyUNFO_DocUpdate_members,  /* tp_members */
    PyUNFO_DocUpdate_getset,   /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_DocUpdate_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_DocUpdate_new,     /* tp_new */};



UNFO_Object* PyUNFO_DocUpdate_acceptfunc(PyObject * self) {
    return (UNFO_Object*)((PyUNFO_DocUpdate*)self)->update;
}
PyObject* PyUNFO_DocUpdate_outfunc(UNFO_Object *uobj) {
    PyUNFO_DocUpdate *self;
    self = (PyUNFO_DocUpdate*) PyUNFO_DocUpdate_Type.tp_alloc(
                                                      &PyUNFO_DocUpdate_Type, 0);
    if (!self)
        return NULL;
    self->update = (UNFO_DocUpdate*)unfo_object_copy(uobj);
    return (PyObject*)self;
}


PyUNFO_ObjList_Info  PyUNFO_DocUpdates_ItemInfo = {
    .out_func = &PyUNFO_DocUpdate_outfunc,
    .accept_func = &PyUNFO_DocUpdate_acceptfunc,
    .accept_types = (PyTypeObject*[]){&PyUNFO_DocUpdate_Type}
};

int PyUNFO_DocUpdates_init(PyUNFO_ObjList *self, PyObject *args, PyObject *kwds){
    (void)kwds;
    (void)args;
    self->item_info = &PyUNFO_DocUpdates_ItemInfo;
    return 0;
}

PyTypeObject PyUNFO_DocUpdates_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocUpdates",   /*tp_name*/
    sizeof(PyUNFO_ObjList),    /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
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
    0,                         /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    0,                         /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    &PyUNFO_ObjList_Type,      /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_DocUpdates_init,      /* tp_init */
    0,                         /* tp_alloc */
    0,                         /* tp_new */};
