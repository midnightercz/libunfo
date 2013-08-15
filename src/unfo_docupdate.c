#include "h/unfo_docupdate.h"

void unfo_doc_update_create(UNFO_DocUpdate *docupdate, UNFO_Object **args){
    (void)args;

    docupdate->colls = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo,
                                                         NULL);
    docupdate->refs = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo,
                                                         NULL);
    docupdate->attrs = unfo_rtree_create(&__unfo_str_clone,
                                         &__unfo_str_clone, &free);
    docupdate->date_attrs = unfo_rtree_create(&__unfo_str_clone,
                                              &__unfo_str_clone, &free);
}
UNFO_CREATE_u(doc_update, UNFO_DocUpdate)

UNFO_DocUpdate* unfo_doc_update_copy(UNFO_DocUpdate *docupdate) {
    UNFO_DocUpdate *ret;
    ret = (UNFO_DocUpdate*) unfo_object_copy((UNFO_Object*)docupdate);
    ret->colls = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)
                                                     docupdate->colls);
    ret->refs = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)
                                                       docupdate->refs);
    ret->attrs = unfo_rtree_clone(docupdate->attrs);
    return ret;
}
UNFO_COPY_u(doc_update, UNFO_DocUpdate)

void unfo_doc_update_destroy(UNFO_DocUpdate *docupdate) {
    unfo_object_destroy((UNFO_Object*)docupdate->colls);
    unfo_object_destroy((UNFO_Object*)docupdate->refs);
    unfo_rtree_destroy(docupdate->attrs);
    unfo_rtree_destroy(docupdate->date_attrs);
}
UNFO_DESTROY_u(doc_update, UNFO_DocUpdate)


char* unfo_doc_update_updated_get(UNFO_DocUpdate *docupdate) {
    struct tm *timeinfo;
    char *ret;
    ret = malloc(sizeof(char)*20);
    UNFO_Check_Malloc(ret, NULL)

    timeinfo = (struct tm*)unfo_rtree_get(docupdate->date_attrs, "updated");
    strftime(ret, 20, "%F %T", timeinfo);
    return ret;
}

int unfo_doc_update_updated_set(UNFO_DocUpdate *docupdate, char *date) {
    struct tm *timeinfo;
    timeinfo = getdate(date);
    if (!timeinfo) return 0;
    unfo_rtree_set(docupdate->date_attrs, "updated", timeinfo);
    return 1;
}

char* unfo_doc_update_issued_get(UNFO_DocUpdate *docupdate) {
    struct tm *timeinfo;
    char *ret;
    ret = malloc(sizeof(char)*20);
    UNFO_Check_Malloc(ret, NULL)

    timeinfo = (struct tm*)unfo_rtree_get(docupdate->date_attrs, "updated");
    strftime(ret, 20, "%F %T", timeinfo);
    return ret;
}

int unfo_doc_update_issued_set(UNFO_DocUpdate *docupdate, char *date) {
    struct tm *timeinfo;
    timeinfo = getdate(date);
    if (timeinfo) return 0;
    unfo_rtree_set(docupdate->date_attrs, "updated", timeinfo);
    return 1;
}

UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, from)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, status)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, type)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, version)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, id)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, title)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, rights)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, summary)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, description)
UNFO_GETSET_ATTR(UNFO_DocUpdate, doc_update, solution)

UNFO_OBJLIST_APPEND(UNFO_DocUpdate, doc_update, colls, collection, UNFO_DocColl)
UNFO_OBJLIST_APPEND(UNFO_DocUpdate, doc_update, refs, references, UNFO_DocRef)

UNFO_ObjectInfo UNFO_DocUpdate_ObjInfo = {
    .obj_size = sizeof(UNFO_DocUpdate),
    .constructor = &unfo_doc_update_create_u,
    .destructor = &unfo_doc_update_destroy_u,
    .deep_copy = &unfo_doc_update_copy_u
};
