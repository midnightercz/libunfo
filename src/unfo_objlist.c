#include "h/unfo_objlist.h"

inline const UNFO_ObjListIt *unfo_objlist_it_next(const UNFO_ObjListIt *it) {
    return (const UNFO_ObjListIt*)it->next;
}

UNFO_ObjListIt* unfo_objlist_it_create(UNFO_Object *obj) {
    UNFO_ObjListIt *objit;
    objit = malloc(sizeof(UNFO_ObjListIt));
    UNFO_Check_NULL(objit, NULL)

    objit->unfo_obj = unfo_object_copy(obj);
    objit->next = NULL;
    return objit;
}

UNFO_ObjListIt* unfo_objlist_it_create_x(UNFO_Object *obj) {
    UNFO_ObjListIt *objit;
    objit = malloc(sizeof(UNFO_ObjListIt));
    UNFO_Check_NULL(objit, NULL)

    objit->unfo_obj = obj;
    objit->next = NULL;
    return objit;
}

void unfo_objlist_it_destroy(UNFO_ObjListIt *objit) {
    UNFO_Check_NULL(objit, )
    unfo_object_destroy(objit->unfo_obj);
    free(objit);
}

void unfo_objlist_create(UNFO_ObjList *objlist, UNFO_Object **args) {
    (void)args;
    objlist->first = NULL;
    objlist->last = NULL;
    objlist->len = 0;
}
UNFO_CREATE_u(objlist, UNFO_ObjList)

UNFO_ObjList* unfo_objlist_copy(UNFO_ObjList *objlist) {
    UNFO_ObjList *ret;
    UNFO_ObjListIt *it;

    ret =(UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    for (it = objlist->first; it != NULL; it = it->next) {
        unfo_objlist_append(ret, unfo_object_copy(it->unfo_obj));
    }
    return ret;
}

UNFO_Object* unfo_objlist_copy_u(UNFO_Object *objlist) {
    return (UNFO_Object*)unfo_objlist_copy((UNFO_ObjList*)objlist);
}

void unfo_objlist_destroy(UNFO_ObjList *objlist) {
    UNFO_ObjListIt *oldit, *it = objlist->first;
    UNFO_Object **obj= NULL;

    oldit = it;
    for (; unfo_objlist_walk(&it, obj); oldit = it) {
        unfo_objlist_it_destroy(oldit);
        oldit = it;
    }
    if (oldit)
        unfo_objlist_it_destroy(oldit);
}

void unfo_objlist_destroy_u(UNFO_Object *objlist) {
    unfo_objlist_destroy((UNFO_ObjList*)objlist);
}

UNFO_Object* unfo_objlist_get(UNFO_ObjList *objlist,
                              unsigned int atpos) {
    unsigned int pos;
    UNFO_ObjListIt *it;
    UNFO_Check_NULL(objlist, NULL)

    for (it = objlist->first, pos=0;
         it != NULL && pos != atpos;
         it = it->next, pos++);

    if (pos != atpos)
        return NULL;

    return (it)?unfo_object_copy(it->unfo_obj):NULL;
}

UNFO_ObjListIt* unfo_objlist_get_it(UNFO_ObjList *objlist,
                              unsigned int atpos) {
    unsigned int pos;
    UNFO_ObjListIt *it;
    UNFO_Check_NULL(objlist, NULL)

    for (it = objlist->first, pos=0;
         it != NULL && pos != atpos;
         it = it->next, pos++);

    if (pos+1 != atpos)
        return NULL;

    return (it)?it:NULL;
}


int unfo_objlist_walk(UNFO_ObjListIt **walker, UNFO_Object **result) {
    UNFO_Check_NULL(*walker, 0)
    result = &(*walker)->unfo_obj;
    *walker = (*walker)->next;
    return 1;
}

int unfo_objlist_walk_r(UNFO_ObjListIt *start,
                            UNFO_ObjListIt *mantinel,
                            UNFO_Object **result) {
    UNFO_Check_NULL(start->next, 1)
    if (start == mantinel)
        return 0;
    start = start->next;
    *result = start->unfo_obj;
    return 1;
}

static int __unfo_objlist_append(UNFO_ObjList *objlist, UNFO_ObjListIt *objit) {
    UNFO_Check_NULL(objlist, -1)
    if (objlist->first == NULL) {
        objlist->first = objit;
        objlist->last = objit;
    } else {
        objlist->last->next = objit;
        objlist->last = objlist->last->next;
    }
    objlist->len++;
    return 1;
}

int unfo_objlist_append_x(UNFO_ObjList *objlist, UNFO_Object *obj) {
    UNFO_ObjListIt *new_it = unfo_objlist_it_create_x(obj);
    return __unfo_objlist_append(objlist, new_it);
}
int unfo_objlist_append(UNFO_ObjList *objlist, UNFO_Object *obj) {
    UNFO_ObjListIt *new_it = unfo_objlist_it_create(obj);
    return __unfo_objlist_append(objlist, new_it);
}

int unfo_objlist_insert_after(UNFO_ObjList *objlist,
                              UNFO_ObjListIt *it,
                              UNFO_Object *obj) {
    UNFO_Check_NULL(objlist, -1)
    UNFO_Check_NULL(it, -1)

    UNFO_ObjListIt *new_it = unfo_objlist_it_create(obj);

    new_it->next = it->next;
    it->next = new_it;
    if (it == objlist->last) {
        objlist->last = new_it;
    }
    objlist->len++;
    return 1;
}

int unfo_objlist_insert_before(UNFO_ObjList *objlist,
                               UNFO_ObjListIt *it,
                               UNFO_Object *obj) {
    UNFO_Check_NULL(objlist, -1)
    UNFO_Check_NULL(it, -1)

    UNFO_ObjListIt *new_it = unfo_objlist_it_create(obj);
    UNFO_ObjListIt *tmpit;
    for (tmpit = objlist->first; tmpit->next != it; tmpit = tmpit->next);

    if (tmpit == objlist->first) {
        new_it->next = objlist->first;
        objlist->first = new_it;
        if (objlist->last == NULL)
            objlist->last = new_it;
    } else {
        new_it->next = tmpit->next;
        tmpit->next = new_it;
    }
    objlist->len++;
    return 1;
}

int unfo_objlist_insert_at(UNFO_ObjList *objlist,
                           unsigned int pos,
                           UNFO_Object *obj) {
    UNFO_ObjListIt *tmpit;
    unsigned int i;

    UNFO_Check_NULL(objlist, -1)

    UNFO_ObjListIt *new_it;

    if (objlist->first) {
        for (i = 0, tmpit = objlist->first; tmpit->next != NULL && i+1 != pos;
            tmpit = tmpit->next, i++) {
        };
    } else tmpit = NULL;
        if (tmpit == objlist->last && pos != objlist->len) {
        return 0;
    }

    new_it = unfo_objlist_it_create(obj);

    if (pos == 0 && tmpit == NULL) {
        objlist->first = new_it;
        objlist->last = new_it;
        objlist->len++;
        return 1;
    }
    if (tmpit == objlist->last && pos == objlist->len) {
        objlist->last->next = new_it;
        objlist->last = new_it;
        objlist->len++;
        return 1;
    }
    new_it->next = tmpit->next;
    tmpit->next = new_it;
    if (tmpit == objlist->last) {
        objlist->last = new_it;
    }
    objlist->len++;
    return 1;
}

int unfo_objlist_remove_at(UNFO_ObjList *objlist, unsigned int atpos) {
    int pos;
    UNFO_ObjListIt *it, *itprev = NULL;
    UNFO_Check_NULL(objlist, 0)

    for (it = objlist->first, pos=-1;
         it != NULL && pos != (int)atpos;
         it = it->next, pos++) {
        itprev = it;
    }
    if (pos != (int)(atpos-1))
        return 0;

    if (itprev == NULL) {
        if (objlist->last == objlist->first)
            objlist->last = NULL;
        objlist->first = objlist->first->next;
        unfo_object_destroy(it->unfo_obj);
        free(it);
    } else {
        itprev->next = it->next;
        unfo_object_destroy(it->unfo_obj);
        free(it);
        if (it == objlist->last) {
            objlist->last = itprev;
        }
    }
    return 1;
}


UNFO_ObjList* unfo_objlist_sublist_it(UNFO_ObjListIt *startit,
                                      UNFO_ObjListIt *end) {
    UNFO_ObjList *ret;
    UNFO_ObjListIt *it;
    ret = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);

    for (it = startit; it != end; it = it->next) {
        unfo_objlist_append(ret, it->unfo_obj);
    }
    return ret;
}

UNFO_ObjList* unfo_objlist_sublist_it_step(UNFO_ObjListIt *startit,
                                           UNFO_ObjListIt *end,
                                           unsigned int step) {
    unsigned int stepc;
    UNFO_ObjList *ret;
    UNFO_ObjListIt *it;

    ret = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    stepc = step;
    for (it = startit; it->next != end; it = it->next, stepc++) {
        if (step == stepc) {
            stepc = 0;
            unfo_objlist_append(ret, it->unfo_obj);
        }
    }
    return ret;
}

UNFO_ObjList* unfo_objlist_sublist_indexed(UNFO_ObjList *objlist,
                                           unsigned int start,
                                           unsigned int end) {
    unsigned int pos;
    UNFO_ObjList *ret;
    UNFO_ObjListIt *it;
    ret = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);

    for (it = objlist->first, pos=0;
         it != NULL && pos != start;
         it = it->next, pos++);
    for (; it->next != NULL && pos != end; it = it->next, pos++) {
        unfo_objlist_append(ret, it->unfo_obj);
    }
    return ret;
}

UNFO_ObjList* unfo_objlist_sublist_indexed_step(UNFO_ObjList *objlist,
                                               unsigned int start,
                                               unsigned int end,
                                               unsigned int step) {
    unsigned int pos;
    unsigned int stepc;
    UNFO_ObjList *ret;
    UNFO_ObjListIt *it;
    ret = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);

    pos = 0;
    stepc = 0;
    for (it = objlist->first;
         it != NULL && pos != start;
         it = it->next, pos++);
    for (; it->next != NULL && pos != end; it = it->next, pos++, stepc++) {
        if (stepc == step) {
            step = 0;
            unfo_objlist_append(ret, it->unfo_obj);
        }
    }
    return ret;
}

UNFO_ObjList* unfo_objlist_filter(UNFO_ObjList *list,
                                  char (*filter_func)(UNFO_Object*)) {
    UNFO_ObjList *ret;
    unsigned int i = 0;
    UNFO_ObjListIt *it;

    ret = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);

    for (i=0, it = list->first; i < list->len; it = it->next, i++) {
        if (filter_func(it->unfo_obj))
            unfo_objlist_append(ret, it->unfo_obj);
    }
    return ret;
}

UNFO_ObjList* unfo_objlist_concat(UNFO_ObjList *list1, UNFO_ObjList *list2) {
    UNFO_ObjList *ret;
    UNFO_ObjListIt *it;

    ret = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    for (it = list1->first; it != NULL; it = it->next) {
        unfo_objlist_append(ret, it->unfo_obj);
    }
    for (it = list2->first; it != NULL; it = it->next) {
        unfo_objlist_append(ret, it->unfo_obj);
    }
    return ret;
}

signed char unfo_objlist_cmp(UNFO_Object *list1, UNFO_Object *list2) {
    UNFO_ObjListIt *it, *it2;
    if (!list1 || !list2) return -1;
    it =  ((UNFO_ObjList*)list1)->first;
    it2 =  ((UNFO_ObjList*)list2)->first;
    
    for (; it != NULL && it2 != NULL; it = it->next, it2 = it2->next) {
        if (!unfo_object_cmp(it->unfo_obj, it2->unfo_obj))
            return 0;
    }
    if (!it && !it2)
        return 1;
    else
        return 0;
}

UNFO_ObjectInfo UNFO_ObjList_ObjInfo = {
    .obj_size = sizeof(UNFO_ObjList),
    .constructor = &unfo_objlist_create_u,
    .destructor = &unfo_objlist_destroy_u,
    .deep_copy = &unfo_objlist_copy_u,
    .obj_cmp = &unfo_objlist_cmp
};
