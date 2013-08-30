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
    if (PyType_Ready(&PyUNFO_DocRef_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocRefs_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocColl_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocColls_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocPkg_Type) < 0)
        return;
    if (PyType_Ready(&PyUNFO_DocPkgs_Type) < 0)
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
    Py_INCREF(&PyUNFO_DocRef_Type);
    PyModule_AddObject(m, "DocRef", (PyObject*) &PyUNFO_DocRef_Type);
    Py_INCREF(&PyUNFO_DocRefs_Type);
    PyModule_AddObject(m, "DocRefs", (PyObject*) &PyUNFO_DocRefs_Type);
    Py_INCREF(&PyUNFO_DocColl_Type);
    PyModule_AddObject(m, "DocColl", (PyObject*) &PyUNFO_DocColl_Type);
    Py_INCREF(&PyUNFO_DocColls_Type);
    PyModule_AddObject(m, "DocColls", (PyObject*) &PyUNFO_DocColls_Type);
    Py_INCREF(&PyUNFO_DocPkg_Type);
    PyModule_AddObject(m, "DocPkg", (PyObject*) &PyUNFO_DocPkg_Type);
    Py_INCREF(&PyUNFO_DocPkgs_Type);
    PyModule_AddObject(m, "DocPkgs", (PyObject*) &PyUNFO_DocPkgs_Type);
    Py_INCREF(&PyUNFO_ObjList_Type);
     PyModule_AddObject(m, "ObjList", (PyObject*) &PyUNFO_ObjList_Type);
    Py_INCREF(&PyUNFO_ObjListIter_Type);
    PyModule_AddObject(m, "ObjListIter", (PyObject*) &PyUNFO_ObjListIter_Type);

    #if PY_MAJOR_VERSION >= 3
        return m;
    #endif
}
