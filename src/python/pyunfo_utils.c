#include "h/pyunfo_utils.h"

const char * Py2Str(PyObject *obj) {
    const char *ret;
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
    PyUNFO_GetSet_Closure *cl = (PyUNFO_GetSet_Closure*)closure;
    char* val = cl->getter(*(UNFO_Object**)(((char*)self) + cl->c_offset));
    if (val)
        ret = PyUnicode_FromString(val);
    else
        Py_RETURN_NONE;
    return ret;
}

int pyunfo_strattr_setter(PyObject *self, PyObject *other, void *closure) {
    const char *ret;
    PyUNFO_GetSet_Closure *cl = (PyUNFO_GetSet_Closure*)closure;

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
    ret = PyUNFO_ObjList_new(&PyUNFO_ObjList_Type, NULL, NULL);
    PyUNFO_ObjList_init(ret, NULL, NULL);
    ((PyUNFO_ObjList*)ret)->list = *(UNFO_ObjList**)(*(char**)
                                                     ((char*)self+cl->c_offset)+
                                    cl->l_offset);
    //increment reference
    ((PyUNFO_ObjList*)ret)->list = (UNFO_ObjList*)unfo_object_copy(
                                (UNFO_ObjList*)((PyUNFO_ObjList*)ret)->list);
    return ret;
}

PyObject* pyunfo_objlist_setter(PyObject *self, void *closure) {

}
