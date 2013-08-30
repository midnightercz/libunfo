#include "h/pyunfo_docpkg.h"

PyUNFO_NEW(DocPkg, UNFO_DocPkg_ObjInfo,
           UNFO_DocPkg, PyUNFO_DocPkg, pkg)
//PyUNFO_INIT(DocPkg, PyUNFO_DocPkg)
PyUNFO_DEALLOC(DocPkg, PyUNFO_DocPkg, pkg)
PyUNFO_CMP(DocPkg, PyUNFO_DocPkg, pkg)
PyUNFO_STR(DocPkg, PyUNFO_DocPkg, pkg)

int PyUNFO_DocPkg_init(PyObject *self, PyObject *args, PyObject *kwargs) {
    char* keywords[] = {"name", "version", "release", "epoch", "arch", "src",
                        "filename", "sum", "sumtype", NULL};
    char *name=NULL, *version=NULL, *release=NULL, *epoch=NULL, *arch=NULL,
         *src=NULL, *filename=NULL, *sum=NULL, *sumtype=NULL;
    #define c_pkg ((PyUNFO_DocPkg*)self)->pkg
    if (args) {
        if (PyArg_ParseTupleAndKeywords(args, kwargs, "|sssssssss", keywords,
                                        &name, &version, &release, &epoch,
                                        &arch, &src, &filename, &sum,
                                        &sumtype)) {
            if (name)
                unfo_doc_pkg_name_set(c_pkg, name);
            if (version)
                unfo_doc_pkg_version_set(c_pkg, version);
            if (release)
                unfo_doc_pkg_release_set(c_pkg, release);
            if (epoch)
                unfo_doc_pkg_epoch_set(c_pkg, epoch);
            if (arch)
                unfo_doc_pkg_arch_set(c_pkg, arch);
            if (src)
                unfo_doc_pkg_src_set(c_pkg, src);
            if (filename)
                unfo_doc_pkg_filename_set(c_pkg, filename);
            if (sum)
                unfo_doc_pkg_sum_set(c_pkg, sum);
            if (sumtype)
                unfo_doc_pkg_sumtype_set(c_pkg, sumtype);
            return 0;
        } else {
            return -1;
        }
    } else {
        return 0;
    }
    return -1;
    #undef c_pkg
}

static PyMemberDef PyUNFO_DocPkg_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_DocPkg_methods[] = {
    {NULL}  /* Sentinel */
};

PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), name)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), version)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), release)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), epoch)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), arch)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), src)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), filename)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), sum)
PYUNFO_STR_GETSET_CLOSURE(DocPkg, doc_pkg,
                          offsetof(PyUNFO_DocPkg, pkg), sumtype)

PyGetSetDef PyUNFO_DocPkg_getset[] = {
    {"name",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'name' attribute", &PyUNFO_DocPkg_name_closure},
    {"version",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'version' attribute", &PyUNFO_DocPkg_version_closure},
    {"release",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'release' attribute", &PyUNFO_DocPkg_release_closure},
    {"epoch",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'epoch' attribute", &PyUNFO_DocPkg_epoch_closure},
    {"arch",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'arch' attribute", &PyUNFO_DocPkg_arch_closure},
    {"src",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'src' attribute", &PyUNFO_DocPkg_src_closure},
    {"filename",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'filename' attribute", &PyUNFO_DocPkg_filename_closure},
    {"sum",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'sum' attribute", &PyUNFO_DocPkg_sum_closure},
    {"sumtype",
     (getter)pyunfo_strattr_getter, (setter)pyunfo_strattr_setter,
     "DocRef 'sumtype' attribute", &PyUNFO_DocPkg_sumtype_closure},
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_DocPkg_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocPkg",     /*tp_name*/
    sizeof(PyUNFO_DocPkg),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PyUNFO_DocPkg_dealloc, /*tp_dealloc*/
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
    PyUNFO_DocPkg_str,         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    0,                         /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    &PyUNFO_DocPkg_cmp,     /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PyUNFO_DocPkg_methods,  /* tp_methods */
    PyUNFO_DocPkg_members,  /* tp_members */
    PyUNFO_DocPkg_getset,   /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_DocPkg_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_DocPkg_new,     /* tp_new */};



UNFO_Object* PyUNFO_DocPkg_acceptfunc(PyObject * self) {
    return (UNFO_Object*)((PyUNFO_DocPkg*)self)->pkg;
}
PyObject* PyUNFO_DocPkg_outfunc(UNFO_Object *uobj) {
    PyUNFO_DocPkg *self;
    self = (PyUNFO_DocPkg*) PyUNFO_DocPkg_Type.tp_alloc(
                                                      &PyUNFO_DocPkg_Type, 0);
    if (!self)
        return NULL;
    self->pkg = (UNFO_DocPkg*)uobj;
    return (PyObject*)self;
}


PyUNFO_ObjList_Info  PyUNFO_DocPkgs_ItemInfo = {
    .out_func = &PyUNFO_DocPkg_outfunc,
    .accept_func = &PyUNFO_DocPkg_acceptfunc,
    .accept_types = (PyTypeObject*[]){&PyUNFO_DocPkg_Type, NULL}
};

int PyUNFO_DocPkgs_init(PyUNFO_ObjList *self, PyObject *args, PyObject *kwds){
    (void)kwds;
    (void)args;
    self->item_info = &PyUNFO_DocPkgs_ItemInfo;
    return 0;
}

PyTypeObject PyUNFO_DocPkgs_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.DocPkgs",   /*tp_name*/
    sizeof(PyUNFO_ObjList),    /*tp_basicsize*/
    sizeof(PyUNFO_DocPkg),  /*tp_itemsize*/
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
    "libunfo DocPkgs",      /* tp_doc */
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
    (initproc)PyUNFO_DocPkgs_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_ObjList_new,        /* tp_new */};
