#include "h/pyunfo_doc.h"

PyObject* PyUNFO_Doc_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    (void)args;
    (void)kwargs;
    PyUNFO_Doc *self;
    self = (PyUNFO_Doc*) type->tp_alloc(type, 0);
    self->doc = (UNFO_Doc*) unfo_object_create(&UNFO_Doc_ObjInfo, NULL);
    self->log = (UNFO_Log*) unfo_object_create(&UNFO_Log_ObjInfo, NULL);
    return (PyObject*)self;
}

void PyUNFO_Doc_dealloc(PyUNFO_Doc *self) {
    unfo_object_destroy((UNFO_Object*)self->log);
    unfo_object_destroy((UNFO_Object*)self->doc);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

//PyUNFO_NEW(Doc, UNFO_Doc_ObjInfo, UNFO_Doc, PyUNFO_Doc, doc)
PyUNFO_INIT(Doc, PyUNFO_Doc)
//PyUNFO_DEALLOC(Doc, PyUNFO_Doc, doc)
PyUNFO_CMP(Doc, PyUNFO_Doc, doc)

PyUNFO_ObjListGetSet_Closure PyUNFO_DocUpdatesClosure = {
    .c_offset = offsetof(PyUNFO_Doc, doc),
    .l_offset = offsetof(UNFO_Doc, updates),
    .name = "updates",
    .list_type = &PyUNFO_DocUpdates_Type
};

PyGetSetDef PyUNFO_Doc_getset[] = {
    {"updates",
     (getter)pyunfo_objlist_getter, (setter)pyunfo_objlist_setter,
     "updates list", &PyUNFO_DocUpdatesClosure},
    {NULL}  /* Sentinel */
};

PyObject* PyUNFO_Doc_fromxml_f(PyUNFO_Doc *self, PyObject *param) {
    UNFO_ParseData *data;
    data = unfo_parse_data_create("UTF-8");
    char *filename = Py2Str(param);
    signed char ret;
    if (!filename) {
        PyErr_Format(PyExc_TypeError,
                    "Filename must be unicode or str instance");
    }
    ret = unfo_parse_file(filename, "UTF-8", data);
    //free(filename);
    if (ret != -1) {
        unfo_object_destroy((UNFO_Object*)self->doc);
        self->doc = (UNFO_Doc*)unfo_object_copy((UNFO_Object*)data->unfo_doc);
    } else {
        unfo_object_destroy((UNFO_Object*)self->doc);
        self->doc = (UNFO_Doc*)unfo_object_create(&UNFO_Doc_ObjInfo, NULL);
    }
    unfo_object_destroy((UNFO_Object*)self->log);
    self->log = (UNFO_Log*)unfo_object_copy((UNFO_Object*)data->log);
    unfo_parse_data_destroy(data);
    return PyINT_FROM_LONG(ret);
}

PyObject *PyUNFO_Doc_fromxml_gzf(PyUNFO_Doc *self, PyObject *param) {
    UNFO_ParseData *data;
    data = unfo_parse_data_create("UTF-8");
    char *filename = Py2Str(param);
    signed char ret;
    if (!filename) {
        PyErr_Format(PyExc_TypeError,
                    "Filename must be unicode or str instance");
    }
    ret = unfo_parse_gzfile(filename, "UTF-8", data);
    //free(filename);
    if (ret != -1) {
        unfo_object_destroy((UNFO_Object*)self->doc);
        self->doc = (UNFO_Doc*)unfo_object_copy((UNFO_Object*)data->unfo_doc);
    } else {
        unfo_object_destroy((UNFO_Object*)self->doc);
        self->doc = (UNFO_Doc*)unfo_object_create(&UNFO_Doc_ObjInfo, NULL);
    }
    unfo_object_destroy((UNFO_Object*)self->log);
    self->log = (UNFO_Log*)unfo_object_copy((UNFO_Object*)data->log);
    unfo_parse_data_destroy(data);
    return PyINT_FROM_LONG(ret);
}

PyObject *PyUNFO_Doc_fromxml_str(PyUNFO_Doc *self, PyObject *param) {
    UNFO_ParseData *data;
    data = unfo_parse_data_create("UTF-8");
    char *str = Py2Str(param);
    signed char ret;
    if (!str) {
        PyErr_Format(PyExc_TypeError,
                    "parametr must be unicode or str instance");
    }
    ret = unfo_parse_str(str, data);
    free(str);
    if (ret != -1) {
        unfo_object_destroy((UNFO_Object*)self->doc);
        self->doc = (UNFO_Doc*)unfo_object_copy((UNFO_Object*)data->unfo_doc);
    } else {
        unfo_object_destroy((UNFO_Object*)self->doc);
        self->doc = (UNFO_Doc*)unfo_object_create(&UNFO_Doc_ObjInfo, NULL);
    }
        return PyINT_FROM_LONG(ret);
}

PyObject *PyUNFO_Doc_xml_f(PyUNFO_Doc *self, PyObject *param) {
    char *filename = Py2Str(param);
    if (!filename) {
        PyErr_Format(PyExc_TypeError,
                    "Filename must be unicode or str instance");
    }
    unfo_hslist_clear(self->log->entries);
    unfo_doc_xml_f(self->doc, filename, "UTF-8", self->log);
    Py_RETURN_NONE;
}

PyObject *PyUNFO_Doc_xml_str(PyUNFO_Doc *self) {
    char* ret;
    unfo_hslist_clear(self->log->entries);
    ret = unfo_doc_xml_str(self->doc, "UTF-8", self->log);
    return PyUnicode_FromString(ret);
}

PyObject* PyUNFO_Doc_get_last_log(PyUNFO_Doc *self) {
    UNFO_HSListItem *it;
    PyObject *ret;
    ret = PyList_New(0);
    for (it = self->log->entries->first; it != NULL; it = it->next) {
        PyList_Append(ret,
                      PyUnicode_FromString(unfo_log_entry_str((UNFO_LogEntry*)it->data)));
    }
    return ret;
}

static PyMemberDef PyUNFO_Doc_members[] = {
    {NULL}
};

static PyMethodDef PyUNFO_Doc_methods[] = {
    {"fromxml_f", (PyCFunction)PyUNFO_Doc_fromxml_f,
     METH_O, "loads update.xml file"},
    {"fromxml_gzf", (PyCFunction)PyUNFO_Doc_fromxml_gzf,
     METH_O, "loads update.xml.gz file"},
    {"fromxml_str", (PyCFunction)PyUNFO_Doc_fromxml_str,
     METH_O, "loads updateinfo from string"},
    {"xml_f", (PyCFunction)PyUNFO_Doc_xml_f,
     METH_O, "Dump updateinfo structure into xml file"},
    {"xml_str", (PyCFunction)PyUNFO_Doc_xml_str,
     METH_NOARGS, "Dump udateinfo structire into xml string"},
    {"get_last_log", (PyCFunction)PyUNFO_Doc_get_last_log,
    METH_NOARGS, "Get log from last operation"},
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_Doc_Type = {
    PY_OBJ_HEAD_INIT
    "libunfo.Doc",             /*tp_name*/
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
    &PyUNFO_Doc_new,                /* tp_new */
    PYTYPEOBJECT_END};
