#include "h/pyunfo.h"

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
            PyModuleDef_HEAD_INIT,
            MODULE_NAME,
            MODULE_DESC,
            -1,
            NULL, //myextension_methods,
            NULL,
            NULL, //myextension_traverse,
            NULL, //myextension_clear,
            NULL
    };
#endif

typedef struct PyCOMPS_Category{
    PyObject_HEAD
} PyCOMPS_Category;

PyTypeObject PyCOMPS_CatType = {
    PY_OBJ_HEAD_INIT
    "libunfo.Category",   /*tp_name*/
    sizeof(PyCOMPS_Category), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,//(destructor)PyCOMPSCat_dealloc, /*tp_dealloc*/
    0,//PyCOMPSCat_print,          /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,//PyCOMPSCat_cmp,            /*tp_compare*/
    0,                         /*tp_repr*/
    0,//&PyCOMPSCat_Nums,          /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,//&PyCOMPS_hash,          /*tp_hash */
    0,                         /*tp_call*/
    0,//&PyCOMPSCat_str,            /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "Comps Category",          /* tp_doc */
    0,                    /* tp_traverse */
    0,                     /* tp_clear */
    0,//&PyCOMPSCat_cmp,       /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    0,//PyCOMPSCat_methods,        /* tp_methods */
    0,//PyCOMPSCat_members,        /* tp_members */
    0,//PyCOMPSCat_getset,         /* tp_getset */
    0,//&PyCOMPS_SeqItemType,      /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)PyCOMPSCat_init,      /* tp_init */
    0,                               /* tp_alloc */
    0,//&PyCOMPSCat_new,                 /* tp_new */};
};
PyMODINIT_FUNC
PYINIT_FUNC(void) {
PyObject *m;
    #if PY_MAJOR_VERSION >= 3
        m = PyModule_Create(&moduledef);
    #else
        m = Py_InitModule(MODULE_NAME, NULL);
    #endif
    if (PyType_Ready(&PyUNFO_Doc_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocUpdate_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocUpdates_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_ObjList_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_ObjListIter_Type) < 0)
        return;

    Py_INCREF(&PyUNFO_Doc_Type);
    PyModule_AddObject(m, "Doc", (PyObject*) &PyUNFO_Doc_Type);
    Py_INCREF(&PyUNFO_DocUpdate_Type);
    PyModule_AddObject(m, "DocUpdate", (PyObject*) &PyUNFO_DocUpdate_Type);
    Py_INCREF(&PyUNFO_DocUpdates_Type);
    PyModule_AddObject(m, "DocUpdates", (PyObject*) &PyUNFO_DocUpdates_Type);
    Py_INCREF(&PyUNFO_ObjList_Type);
    PyModule_AddObject(m, "ObjList", (PyObject*) &PyUNFO_ObjList_Type);
    Py_INCREF(&PyUNFO_ObjListIter_Type);
    PyModule_AddObject(m, "ObjListIter", (PyObject*) &PyUNFO_ObjListIter_Type);

    #if PY_MAJOR_VERSION >= 3
        return m;
    #endif
}
