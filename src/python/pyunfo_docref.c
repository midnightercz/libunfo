#include "h/pyunfo_docref.h"

PyUNFO_NEW(DocRef, UNFO_DocRef_ObjInfo,
           UNFO_DocRef, PyUNFO_DocRef, ref)
//PyUNFO_INIT(DocRef, PyUNFO_DocRef)
PyUNFO_DEALLOC(DocRef, PyUNFO_DocRef, ref)
PyUNFO_CMP(DocRef, PyUNFO_DocRef, ref)
PyUNFO_STR(DocRef, PyUNFO_DocRef, ref)

int PyUNFO_DocRef_init(PyObject *self, PyObject *args, PyObject *kwargs) {
    char* keywords[] = {"url", "type", "id", "title", NULL};
    char *url=NULL, *type=NULL, *id=NULL, *title=NULL;
    #define c_ref ((PyUNFO_DocRef*)self)->ref
    if (args) {
        if (PyArg_ParseTupleAndKeywords(args, kwargs, "|ssss", keywords,
                                        &url, &type, &id, &title)) {
            if (url)
                unfo_doc_ref_url_set(c_ref, url);
            if (type)
                unfo_doc_ref_url_set(c_ref, type);
            if (id)
                unfo_doc_ref_url_set(c_ref, id);
            if (title)
                unfo_doc_ref_url_set(c_ref, title);
            return 0;
        } else {
            return -1;
        }
    } else {
        return 0;
    }
    return -1;
    #undef c_ref
}

static PyMemberDef PyUNFO_DocRef_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_DocRef_methods[] = {
    {NULL}  /* Sentinel */
};

PYUNFO_STR_GETSET_CLOSURE(DocRef, doc_ref,
                          offsetof(PyUNFO_DocRef, ref), url)
PYUNFO_STR_GETSET_CLOSURE(DocRef, doc_ref,
                          offsetof(PyUNFO_DocRef, ref), type)
PYUNFO_STR_GETSET_CLOSURE(DocRef, doc_ref,
                          offsetof(PyUNFO_DocRef, ref), title)
PYUNFO_STR_GETSET_CLOSURE(DocRef, doc_ref,
                          offsetof(PyUNFO_DocRef, ref), id)

PyGetSetDef PyUNFO_DocRef_getset[] = {
    {"url",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'url' attribute", &PyUNFO_DocRef_url_closure},
    {"type",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'type' attribute", &PyUNFO_DocRef_type_closure},
    {"title",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'title' attribute", &PyUNFO_DocRef_title_closure},
    {"id",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'id' attribute", &PyUNFO_DocRef_id_closure},
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_DocRef_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocRef",     /*tp_name*/
    sizeof(PyUNFO_DocRef),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PyUNFO_DocRef_dealloc, /*tp_dealloc*/
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
    PyUNFO_DocRef_str,         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    0,                         /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    &PyUNFO_DocRef_cmp,     /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PyUNFO_DocRef_methods,  /* tp_methods */
    PyUNFO_DocRef_members,  /* tp_members */
    PyUNFO_DocRef_getset,   /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_DocRef_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_DocRef_new,     /* tp_new */};



UNFO_Object* PyUNFO_DocRef_acceptfunc(PyObject * self) {
    return (UNFO_Object*)((PyUNFO_DocRef*)self)->ref;
}
PyObject* PyUNFO_DocRef_outfunc(UNFO_Object *uobj) {
    PyUNFO_DocRef *self;
    self = (PyUNFO_DocRef*) PyUNFO_DocRef_Type.tp_alloc(
                                                      &PyUNFO_DocRef_Type, 0);
    if (!self)
        return NULL;
    self->ref = (UNFO_DocRef*)uobj;
    return (PyObject*)self;
}


PyUNFO_ObjList_Info  PyUNFO_DocRefs_ItemInfo = {
    .out_func = &PyUNFO_DocRef_outfunc,
    .accept_func = &PyUNFO_DocRef_acceptfunc,
    .accept_types = (PyTypeObject*[]){&PyUNFO_DocRef_Type, NULL}
};

int PyUNFO_DocRefs_init(PyUNFO_ObjList *self, PyObject *args, PyObject *kwds){
    (void)kwds;
    (void)args;
    self->item_info = &PyUNFO_DocRefs_ItemInfo;
    return 0;
}

PyTypeObject PyUNFO_DocRefs_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocRefs",   /*tp_name*/
    sizeof(PyUNFO_ObjList),    /*tp_basicsize*/
    sizeof(PyUNFO_DocRef),  /*tp_itemsize*/
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
    "libunfo DocRefs",      /* tp_doc */
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
    (initproc)PyUNFO_DocRefs_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_ObjList_new,        /* tp_new */};
