#include "h/pyunfo_utils.h"

char * Py2Str(PyObject *obj) {
    char *ret;
    if PyUnicode_Check(obj) {
        PyObject *tmpobj;
        tmpobj = PyUnicode_AsUTF8String(obj);
        ret = PyBytes_AsString(tmpobj);

    } else if (PyBytes_Check(obj)) {
        ret = PyBytes_AsString(obj);
    } else return NULL;
    return ret;
}

PyObject* pyunfo_strattr_getter(PyObject *self, void *closure) {
    PyObject* ret;
    PyUNFO_StrGetSet_Closure *cl = (PyUNFO_StrGetSet_Closure*)closure;
    char* val = cl->getter(*(UNFO_Object**)(((char*)self) + cl->c_offset));
    if (val)
        ret = PyUnicode_FromString(val);
    else
        Py_RETURN_NONE;
    return ret;
}

int pyunfo_strattr_setter(PyObject *self, PyObject *other, void *closure) {
    const char *ret;
    PyUNFO_StrGetSet_Closure *cl = (PyUNFO_StrGetSet_Closure*)closure;

    if (!other) {
        PyErr_Format(PyExc_TypeError, "Cannot delete '%s' attribute", cl->name);
        return -1;
    }

    ret = Py2Str(other);
    if (!ret) {
        PyErr_Format(PyExc_TypeError, "%s is not bytes or unicode",
                                      Py_TYPE(other)->tp_name);
        return -1;
    }
    return (cl->setter(*(UNFO_Object**)(((char*)self)+cl->c_offset), ret) != 1);
}

PyObject* pyunfo_objlist_getter(PyObject *self, void *closure) {
    PyUNFO_ObjListGetSet_Closure *cl =(PyUNFO_ObjListGetSet_Closure*)closure;
    PyObject *ret;
    ret = PyUNFO_ObjList_new(cl->list_type, NULL, NULL);
    Py_TYPE(ret)->tp_init(ret, NULL, NULL);
    unfo_object_destroy((UNFO_Object*)((PyUNFO_ObjList*)ret)->list);
    ((PyUNFO_ObjList*)ret)->list = *(UNFO_ObjList**)(*(char**)
                                                     ((char*)self+cl->c_offset)+
                                    cl->l_offset);
    //increment reference
    ((PyUNFO_ObjList*)ret)->list = (UNFO_ObjList*)unfo_object_copy(
                                (UNFO_Object*)((PyUNFO_ObjList*)ret)->list);
    return ret;
}

int pyunfo_objlist_setter(PyObject *self, PyObject *other, void *closure) {
    PyUNFO_ObjListGetSet_Closure *cl =(PyUNFO_ObjListGetSet_Closure*)closure;
    if (!other) {
        PyErr_Format(PyExc_TypeError, "Cannot delete %s attribute\n", cl->name);
        return -1;
    }

    if (cl->list_type != Py_TYPE(other)) {
        PyErr_Format(PyExc_TypeError, "%s is not %s", cl->list_type->tp_name,
                                                      Py_TYPE(other)->tp_name);
        return -1;
    }

    unfo_object_destroy(*(UNFO_Object**)(*(char**)((char*)self+cl->c_offset) +
                                    cl->l_offset));
    *(UNFO_ObjList**)(*(char**)((char*)self+cl->c_offset) + cl->l_offset) =
        (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)((PyUNFO_ObjList*)other)->list);
    return 0;
}
