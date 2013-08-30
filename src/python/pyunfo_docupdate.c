#include "h/pyunfo_docupdate.h"

PyUNFO_NEW(DocUpdate, UNFO_DocUpdate_ObjInfo,
           UNFO_DocUpdate, PyUNFO_DocUpdate, update)
//PyUNFO_INIT(DocUpdate, PyUNFO_DocUpdate)
PyUNFO_DEALLOC(DocUpdate, PyUNFO_DocUpdate, update)
PyUNFO_CMP(DocUpdate, PyUNFO_DocUpdate, update)
PyUNFO_STR(DocUpdate, PyUNFO_DocUpdate, update)

int PyUNFO_DocUpdate_init(PyObject *self, PyObject *args, PyObject *kwargs) {
    char* keywords[] = {"from", "status", "type", "version", "id", "title",
                        "rights", "summary", "description", "solution", NULL};
    char *from=NULL, *status=NULL, *type=NULL, *version=NULL, *id=NULL,
         *title=NULL, *rights=NULL, *summary=NULL,
         *description=NULL, *solution=NULL;
    #define c_update ((PyUNFO_DocUpdate*)self)->update
    if (args) {
        if (PyArg_ParseTupleAndKeywords(args, kwargs, "|ssssssssss", keywords,
                                        &from, &status, &type, &version, &id,
                                        &title, &rights, &summary, &description,
                                        &solution)) {
            if (from)
                unfo_doc_update_id_set(c_update, from);
            if (status)
                unfo_doc_update_status_set(c_update, status);
            if (type)
                unfo_doc_update_type_set(c_update, type);
            if (version)
                unfo_doc_update_version_set(c_update, version);
            if (id)
                unfo_doc_update_id_set(c_update, id);
            if (title)
                unfo_doc_update_title_set(c_update, title);
            if (rights)
                unfo_doc_update_rights_set(c_update, rights);
            if (summary)
                unfo_doc_update_summary_set(c_update, summary);
            if (description)
                unfo_doc_update_description_set(c_update, description);
            if (solution)
                unfo_doc_update_solution_set(c_update, solution);
            return 0;
        } else {
            return -1;
        }
    } else {
        return 0;
    }
    return -1;
    #undef c_update
}

static PyMemberDef PyUNFO_DocUpdate_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_DocUpdate_methods[] = {
    {NULL}  /* Sentinel */
};

PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), from)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), status)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), type)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), version)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), id)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), title)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), rights)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), summary)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), description)
PYUNFO_STR_GETSET_CLOSURE(DocUpdate, doc_update,
                          offsetof(PyUNFO_DocUpdate, update), solution)

PyUNFO_ObjListGetSet_Closure PyUNFO_DocRefsClosure = {
    .c_offset = offsetof(PyUNFO_DocUpdate, update),
    .l_offset = offsetof(UNFO_DocUpdate, refs),
    .name = "references",
    .list_type = &PyUNFO_DocRefs_Type
};

PyUNFO_ObjListGetSet_Closure PyUNFO_DocCollsClosure = {
    .c_offset = offsetof(PyUNFO_DocUpdate, update),
    .l_offset = offsetof(UNFO_DocUpdate, colls),
    .name = "collections",
    .list_type = &PyUNFO_DocColls_Type
};

PyGetSetDef PyUNFO_DocUpdate_getset[] = {
    {"from",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate from attribute", &PyUNFO_DocUpdate_from_closure},
    {"status",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate status attribute", &PyUNFO_DocUpdate_status_closure},
    {"type",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate type attribute", &PyUNFO_DocUpdate_type_closure},
    {"version",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate version attribute", &PyUNFO_DocUpdate_version_closure},
    {"id",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate id attribute", &PyUNFO_DocUpdate_id_closure},
    {"title",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate title attribute", &PyUNFO_DocUpdate_title_closure},
    {"rights",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate rights attribute", &PyUNFO_DocUpdate_rights_closure},
    {"summary",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate summary attribute", &PyUNFO_DocUpdate_summary_closure},
    {"description",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate description attribute", &PyUNFO_DocUpdate_description_closure},
    {"solution",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocUpdate solution attribute", &PyUNFO_DocUpdate_solution_closure},

    {"references",
     (getter)pyunfo_objlist_getter, (setter)pyunfo_objlist_setter,
     "collection packages list", &PyUNFO_DocRefsClosure},
    {"collections",
     (getter)pyunfo_objlist_getter, (setter)pyunfo_objlist_setter,
     "collection packages list", &PyUNFO_DocCollsClosure},
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
    PyUNFO_DocUpdate_str,      /*tp_str*/
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
    &PyUNFO_DocUpdate_new,     /* tp_new */
    PYTYPEOBJECT_END};



UNFO_Object* PyUNFO_DocUpdate_acceptfunc(PyObject * self) {
    return (UNFO_Object*)((PyUNFO_DocUpdate*)self)->update;
}
PyObject* PyUNFO_DocUpdate_outfunc(UNFO_Object *uobj) {
    PyUNFO_DocUpdate *self;
    self = (PyUNFO_DocUpdate*) PyUNFO_DocUpdate_Type.tp_alloc(
                                                      &PyUNFO_DocUpdate_Type, 0);
    if (!self)
        return NULL;
    self->update = (UNFO_DocUpdate*)uobj;
    return (PyObject*)self;
}


PyUNFO_ObjList_Info  PyUNFO_DocUpdates_ItemInfo = {
    .out_func = &PyUNFO_DocUpdate_outfunc,
    .accept_func = &PyUNFO_DocUpdate_acceptfunc,
    .accept_types = (PyTypeObject*[]){&PyUNFO_DocUpdate_Type, NULL}
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
    sizeof(PyUNFO_DocUpdate),  /*tp_itemsize*/
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
    "libunfo DocUpdates",      /* tp_doc */
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
    &PyUNFO_ObjList_new,        /* tp_new */
    PYTYPEOBJECT_END};
