#include "h/pyunfo_objlist.h"

PyUNFO_NEW(ObjList, UNFO_ObjList_ObjInfo, UNFO_ObjList, PyUNFO_ObjList, list)
PyUNFO_INIT(ObjList, PyUNFO_ObjList)
PyUNFO_DEALLOC(ObjList, PyUNFO_ObjList, list)


inline PyObject *pyobjlist_getitem(PyObject *self, Py_ssize_t index) {
    #define list ((PyUNFO_ObjList*)self)->list
    UNFO_Object *uobj;
    if (index < 0)
        index = list->len + index;

    uobj = unfo_objlist_get(list, index);
    if (uobj == NULL) {
        PyErr_SetString(PyExc_IndexError,"Index out of range");
        return NULL;
    }
    return ((PyUNFO_ObjList*)self)->item_info->out_func(uobj);
    #undef list
}

inline int pyobjlist_setitem(PyObject *self, Py_ssize_t index, PyObject *item){
    #define list ((PyUNFO_ObjList*)self)->list
    #define item_info ((PyUNFO_ObjList*)self)->item_info
    UNFO_Object *uobj, *uobj2;
    int type_index;

    if ((int)index > (int)(list->len-1)) {
        PyErr_SetString(PyExc_IndexError,"Index out of range");
        return -1;
    }
    if (item != NULL) {
        for (type_index = 0; item_info->accept_types[type_index]; type_index++){

            if (Py_TYPE(item) != item_info->accept_types[type_index])
                continue;

            uobj = item_info->accept_func(item);
            uobj2 = unfo_objlist_get(list, index);
            if (uobj2) unfo_object_destroy(uobj2);
            unfo_objlist_insert_at(list, index, uobj);
            break;
        }
        if (!item_info->accept_types[type_index]) {
            PyErr_Format(PyExc_TypeError, "Cannot set %s to %s",
                            Py_TYPE(self)->tp_name, Py_TYPE(self)->tp_name);
            return -1;
        }
    } else {
        unfo_objlist_remove_at(list, index);
    }
    return 0;
    #undef list
    #undef item_info
}

/*PyObject* ctopy_list_concat(PyObject *self, PyObject *other) {
    Py_RETURN_NONE;
}*/

PyObject *PyUNFO_ObjList_get(PyObject *self, PyObject *key) {
    #define _list ((PyUNFO_ObjList*)self)->list

    PyUNFO_ObjList *result;
    UNFO_ObjListIt *it;
    int i;
    unsigned int n, uret;
    Py_ssize_t clen;
    Py_ssize_t istart, istop, istep, ilen;

    if (PySlice_Check(key)) {
        n = _list->len;
        result = (PyUNFO_ObjList*)Py_TYPE(self)->tp_new(Py_TYPE(self),
                                                          NULL, NULL);
        Py_TYPE(self)->tp_init((PyObject*)result, NULL, NULL);
        uret = PySlice_GetIndicesEx((SLICE_CAST)key, n,
                                   &istart, &istop, &istep, &ilen);
        if (uret) {
            PyErr_SetString(PyExc_TypeError, "Fail to convert slice");
            return NULL;
        }
        clen = 0;
        it = _list->first;
        for (i=0 ; i<istart; it=it->next, i++);
        while (clen != ilen) {
            unfo_objlist_append(result->list, it->unfo_obj);
            clen+=1;
            for (i=0 ; i<istep && it != NULL; it=it->next,  i++);
            if (!it) it = _list->first;
            for (; i<istep; it=it->next, i++);
        }
        return (PyObject*)result;
    } else if (PyINT_CHECK(key)) {
        return pyobjlist_getitem(self, PyINT_ASLONG(key));
    } else {
        PyErr_SetString(PyExc_TypeError, "Key must be index interger or slice");
        return NULL;
    }
    #undef _list
}

int PyUNFO_ObjList_set(PyObject *self, PyObject *key, PyObject *val) {
    #define _list ((PyUNFO_ObjList*)self)->list
    #define _list2 ((PyUNFO_ObjList*)self)->list

    UNFO_ObjListIt *it, *it2;
    unsigned int n, uret;
    Py_ssize_t istart, istop, istep, ilen, i, c, clen;

    if (PySlice_Check(key)) {
        n = _list->len;
        uret = PySlice_GetIndicesEx((SLICE_CAST)key, n,
                                   &istart, &istop, &istep, &ilen);
        if (ilen==0) {
            uret = PySlice_GetIndicesEx((SLICE_CAST)key, n + istart,
                                       &istart, &istop, &istep, &ilen);
        }
        if (uret)
            return -1;
        if (val) {
            if (Py_TYPE(self) != Py_TYPE(val)) {
                PyErr_SetString(PyExc_TypeError, "different object class");
                return -1;
            }
            if (istep != 1 && n != (unsigned int)ilen) {
                PyErr_Format(PyExc_ValueError,
                             "attempt to assign sequence of size %d to extended"
                             "slice of size %d",
                             n, (unsigned int)ilen);
                return -1;
            }
            clen = 0;
            it = _list->first;
            it2 = _list2->first;
            for (i=0 ; i < istart && it != NULL; it=it->next, i++);
            if (istep != 1) {
                while (clen != ilen) {
                    unfo_object_destroy(it->unfo_obj);
                    it->unfo_obj = unfo_object_copy(it2->unfo_obj);
                    clen+=1;
                    it2 = it2->next;
                    for (i=0 ; i<istep && it != NULL; it=it->next,  i++);
                    if (!it) it = _list->first;
                    for (; i<istep; it=it->next, i++);
                }
            } else {
                if (istart < 0) istart += n;
                if (istop < 0) istop += n;

                for (; it2 != NULL && it != NULL;
                       it2 = it2->next, it = it->next, i++) {
                    unfo_object_destroy(it->unfo_obj);
                    it->unfo_obj = unfo_object_copy(it2->unfo_obj);
                }
                if (it == NULL) {
                    for (;it2 != NULL; it2 = it2->next) {
                        unfo_objlist_append(_list, it2->unfo_obj);
                    }
                }
                if (it != NULL) {
                    for (c = i; c < istop; c++) {
                        unfo_objlist_remove_at(_list, i);
                    }
                }
            }
            return 0;
        } else {
            clen = 0;
            it = _list->first;
            for (i=0 ; i<istart && it != NULL; it=it->next, i++);
            while (clen != ilen) {
                if (it->unfo_obj) {
                    unfo_object_destroy(it->unfo_obj);
                    it->unfo_obj = NULL;
                }
                clen+=1;
                for (i=0 ; i<istep && it != NULL; it=it->next,  i++);
                if (!it) it = _list->first;
                for (; i<istep; it=it->next, i++);
            }
            it2 = NULL;
            for (i=0, it = _list->first;
                 it != NULL;
                 it2 = it, it = it->next, i++) {
                if (it2 && !it2->unfo_obj) {
                    unfo_objlist_remove_at(_list, i);
                }
            }
            if (it2 && !it2->unfo_obj) {
                unfo_objlist_remove_at(_list, i);
            }
            return 0;
        }
    } else if (PyINT_CHECK(key)) {
        return pyobjlist_setitem(self, PyINT_ASLONG(key), val);
    } else {
        PyErr_SetString(PyExc_TypeError, "Key must be index interger or slice");
        return -1;
    }
    #undef list
    #undef list2
}

PyObject* PyUNFO_ObjList_append(PyObject * self, PyObject *item) {
    #define list ((PyUNFO_ObjList*)self)->list
    #define item_info ((PyUNFO_ObjList*)self)->item_info
    int type_index;
    UNFO_Object *uobj;

    for (type_index = 0; item_info->accept_types[type_index]; type_index++) {
        if (Py_TYPE(item) != item_info->accept_types[type_index])
            continue;
        uobj = item_info->accept_func(item);
        unfo_objlist_append_x(list, uobj);
        break;
    }
    if (!item_info->accept_types[type_index]) {
        PyErr_Format(PyExc_TypeError, "Cannot set %s to %s",
                        Py_TYPE(self)->tp_name, Py_TYPE(self)->tp_name);
        return NULL;
    }
    Py_RETURN_NONE;
    #undef list
    #undef item_info
}

PyObject* PyUNFO_ObjList_str(PyObject *self) {
    PyObject *ret, *tmp, *tmp2;
    UNFO_ObjListIt *it;
    ret = PyUnicode_FromString("[");
    for (it = ((PyUNFO_ObjList*)self)->list->first; it != NULL; it = it->next) {
        tmp2 = PyUnicode_FromString(unfo_object_tostr(it->unfo_obj));
        tmp = PyUnicode_Concat(ret, tmp2);
        Py_DECREF(ret);
        Py_DECREF(tmp2);
        ret = tmp;
    }
    tmp = ret;
    tmp2 = PyUnicode_FromString("]");
    ret = PyUnicode_Concat(ret, tmp2);
    Py_XDECREF(tmp);
    Py_XDECREF(tmp2);
    return ret;
}
int PyUNFO_ObjList_print(PyObject *self, FILE *f, int flags) {
    UNFO_ObjListIt *it;

    (void)flags;
    fprintf(f, "[");
    it = ((PyUNFO_ObjList*)self)->list?((PyUNFO_ObjList*)self)->list->first:NULL;
    for (;it != NULL && it != ((PyUNFO_ObjList*)self)->list->last; it = it->next){
        fprintf(f, "%s", unfo_object_tostr(it->unfo_obj));
        fprintf(f, ", ");
    }
    if (it) {
        fprintf(f, "%s", unfo_object_tostr(it->unfo_obj));
    }
    fprintf(f, "]");
    return 0;
}

PyObject* PyUNFO_ObjList_cmp(PyObject *self, PyObject *other, int op) {
    char cmpret;
    cmpret = unfo_object_cmp((UNFO_Object*)((PyUNFO_ObjList*)self)->list,
                             (UNFO_Object*)((PyUNFO_ObjList*)other)->list);
    if (cmpret) {
        if (op == Py_EQ)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    } else {
        if (op == Py_EQ)
            Py_RETURN_FALSE;
        else
            Py_RETURN_TRUE;
    }
}
PyObject* PyUNFO_ObjList_getiter(PyObject *self) {
    PyObject *res;
    res = PyUNFO_ObjListIter_new(&PyUNFO_ObjListIter_Type, NULL, NULL);
    ((PyUNFO_ObjListIter*)res)->it = ((PyUNFO_ObjList*)self)->list->first;
    ((PyUNFO_ObjListIter*)res)->seq = self;
    return res;
}

Py_ssize_t PyUNFO_ObjList_len(PyObject *self) {
    return (Py_ssize_t)((PyUNFO_ObjList*)self)->list->len;
}

PyObject* PyUNFO_ObjList_clear(PyObject *self) {
    //unfo_objlist_clear(((PyUNFO_ObjList*)self)->list);
    Py_RETURN_NONE;
}

int PyUNFO_setobjlist(PyObject *self, PyObject *objlist, void *closure) {

}

PyObject* PyUNFO_getobjlist(PyObject *self, void *closure) {
    size_t offset = 0;
    void *tmpobj;
    PyObject *pobj;
    pobj = (PyObject*) *((char**)((char*)tmpobj)+offset);
    if (pobj) {
        Py_INCREF(pobj);
        return pobj;
    } else {
        pobj = PyUNFO_ObjList_new(&PyUNFO_ObjList_Type, NULL, NULL);
        unfo_object_destroy((UNFO_Object*)((PyUNFO_ObjList*)pobj)->list);
        tmpobj = (void*)self;
        offset = ((PyUNFO_GetSetObjClosure*)closure)->path[0];
        while (offset != (size_t)-1) {
            tmpobj =(void*) *((char**)((char*)tmpobj)+offset);
            offset++;
        }
        ((PyUNFO_ObjList*)pobj)->list = (UNFO_ObjList*)
                                        unfo_object_copy((UNFO_Object*)tmpobj);
        tmpobj = (void*)self;
        offset = ((PyUNFO_GetSetObjClosure*)closure)->pobj_offset;
        *((PyObject**)((char*)tmpobj)+offset) = pobj;
        return pobj;
    }
}

static PyMappingMethods PyUNFO_ObjList_mapping = {
    &PyUNFO_ObjList_len,
    &PyUNFO_ObjList_get,
    &PyUNFO_ObjList_set
};

PyMemberDef PyUNFO_ObjList_members[] = {
    {NULL}};

PyMethodDef PyUNFO_ObjList_methods[] = {
     {"append", (PyCFunction)PyUNFO_ObjList_append, METH_O,
     "Append item to new of the list"},
     {"clear", (PyCFunction)PyUNFO_ObjList_clear, METH_NOARGS,
     "Clear the list"},
    {NULL}  /* Sentinel */
};

PyTypeObject PyUNFO_ObjList_Type = {
    PY_OBJ_HEAD_INIT
    "_libpyunfo.ObjList",             /*tp_name*/
    sizeof(PyUNFO_ObjList), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PyUNFO_ObjList_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    &PyUNFO_ObjList_mapping,   /*tp_as_mapping*/
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
    &PyUNFO_ObjList_cmp,       /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    PyUNFO_ObjList_methods,    /* tp_methods */
    PyUNFO_ObjList_members,    /* tp_members */
    0,     /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyUNFO_ObjList_init,      /* tp_init */
    0,                         /* tp_alloc */
    &PyUNFO_ObjList_new                /* tp_new */};
