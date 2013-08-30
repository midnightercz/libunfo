#include "h/pyunfo_doccoll.h"

PyUNFO_NEW(DocColl, UNFO_DocColl_ObjInfo,
           UNFO_DocColl, PyUNFO_DocColl, coll)
//PyUNFO_INIT(DocColl, PyUNFO_DocColl)
PyUNFO_DEALLOC(DocColl, PyUNFO_DocColl, coll)
PyUNFO_CMP(DocColl, PyUNFO_DocColl, coll)
PyUNFO_STR(DocColl, PyUNFO_DocColl, coll)

int PyUNFO_DocColl_init(PyObject *self, PyObject *args, PyObject *kwargs) {
    char* keywords[] = {"short", "name", NULL};
    char *_short=NULL, *name=NULL;
    #define c_coll ((PyUNFO_DocColl*)self)->coll
    if (args) {
        if (PyArg_ParseTupleAndKeywords(args, kwargs, "|ss", keywords,
                                        &_short, &name)) {
            if (_short)
                unfo_doc_coll_short_set(c_coll, _short);
            if (name)
                unfo_doc_coll_name_set(c_coll, name);
            return 0;
        } else {
            return -1;
        }
    } else {
        return 0;
    }
    return -1;
    #undef c_coll
}

static PyMemberDef PyUNFO_DocColl_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_DocColl_methods[] = {
    {NULL}  /* Sentinel */
};

PyUNFO_ObjListGetSet_Closure PyUNFO_DocPackagesClosure = {
    .c_offset = offsetof(PyUNFO_DocColl, coll),
    .l_offset = offsetof(UNFO_DocColl, pkgs),
    .name = "packages",
    .list_type = &PyUNFO_DocPkgs_Type
};

PYUNFO_STR_GETSET_CLOSURE(DocColl, doc_coll,
                          offsetof(PyUNFO_DocColl, coll), short)
PYUNFO_STR_GETSET_CLOSURE(DocColl, doc_coll,
                          offsetof(PyUNFO_DocColl, coll), name)

PyGetSetDef PyUNFO_DocColl_getset[] = {
    {"short",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'short' attribute", &PyUNFO_DocColl_short_closure},
    {"name",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'name' attribute", &PyUNFO_DocColl_name_closure},

    {"packages",
     (getter)pyunfo_objlist_getter, (setter)pyunfo_objlist_setter,
     "collection packages list", &PyUNFO_DocPackagesClosure},
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_DocColl_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocColl",     /*tp_name*/
    sizeof(PyUNFO_DocColl),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PyUNFO_DocColl_dealloc, /*tp_dealloc*/
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
    PyUNFO_DocColl_str,        /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    0,                         /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    &PyUNFO_DocColl_cmp,     /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PyUNFO_DocColl_methods,  /* tp_methods */
    PyUNFO_DocColl_members,  /* tp_members */
    PyUNFO_DocColl_getset,   /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_DocColl_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_DocColl_new,     /* tp_new */};



UNFO_Object* PyUNFO_DocColl_acceptfunc(PyObject * self) {
    return (UNFO_Object*)((PyUNFO_DocColl*)self)->coll;
}
PyObject* PyUNFO_DocColl_outfunc(UNFO_Object *uobj) {
    PyUNFO_DocColl *self;
    self = (PyUNFO_DocColl*) PyUNFO_DocColl_Type.tp_alloc(
                                                      &PyUNFO_DocColl_Type, 0);
    if (!self)
        return NULL;
    self->coll = (UNFO_DocColl*)uobj;
    return (PyObject*)self;
}


PyUNFO_ObjList_Info  PyUNFO_DocColls_ItemInfo = {
    .out_func = &PyUNFO_DocColl_outfunc,
    .accept_func = &PyUNFO_DocColl_acceptfunc,
    .accept_types = (PyTypeObject*[]){&PyUNFO_DocColl_Type, NULL}
};

int PyUNFO_DocColls_init(PyUNFO_ObjList *self, PyObject *args, PyObject *kwds){
    (void)kwds;
    (void)args;
    self->item_info = &PyUNFO_DocColls_ItemInfo;
    return 0;
}

PyTypeObject PyUNFO_DocColls_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocColls",   /*tp_name*/
    sizeof(PyUNFO_ObjList),    /*tp_basicsize*/
    sizeof(PyUNFO_DocColl),  /*tp_itemsize*/
    (destructor)PyUNFO_ObjList_dealloc, /*tp_dealloc*/
    &PyUNFO_ObjList_print,     /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    &PyUNFO_ObjList_str,       /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_TYPE_SUBCLASS,        /*tp_flags*/
    "libunfo DocColls",      /* tp_doc */
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
    (initproc)PyUNFO_DocColls_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_ObjList_new,        /* tp_new */};

