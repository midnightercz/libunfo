#include "h/unfo_docupdate.h"

UNFO_DocUpdate* unfo_doc_update_create(){
    UNFO_DocUpdate *docupdate;
    docupdate = (UNFO_DocUpdate*)unfo_object_create(&UNFO_DocUpdate_ObjInfo);
    docupdate->packages = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo);
    docupdate->references = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo);
    docupdate->attributes = unfo_rtree_create(NULL, &__unfo_str_clone, &free);
    return docupdate;
}

UNFO_CREATE_u(doc_update, UNFO_DocUpdate)

UNFO_DocUpdate* unfo_doc_update_copy(UNFO_DocUpdate *docupdate) {
    UNFO_DocUpdate *ret;
    ret = (UNFO_DocUpdate*) unfo_object_copy((UNFO_Object*)docupdate);
    ret->packages = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)
                                                     docupdate->packages);
    ret->references = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)
                                                       docupdate->references);
    ret->attributes = unfo_rtree_clone(docupdate->attributes);
    return ret;
}

UNFO_COPY_u(doc_update, UNFO_DocUpdate)

/*inline UNFO_Object* unfo_doc_update_copy_u(UNFO_Object *docupdate) {
    return (UNFO_Object*)unfo_doc_update_copy((UNFO_DocUpdate*)docupdate);
}*/

void unfo_doc_update_destroy(UNFO_DocUpdate *docupdate) {
    unfo_object_destroy((UNFO_Object*)docupdate->packages);
    unfo_object_destroy((UNFO_Object*)docupdate->references);
    unfo_rtree_destroy(docupdate->attributes);
}

UNFO_DESTROY_u(doc_update, UNFO_DocUpdate)

/*inline void unfo_doc_update_destroy_u(UNFO_Object *doc){
    unfo_doc_update_destroy((UNFO_DocUpdate*)doc);
}*/

UNFO_ObjectInfo UNFO_DocUpdate_ObjInfo = {
    .obj_size = sizeof(UNFO_DocUpdate),
    .constructor = &unfo_doc_update_create_u,
    .destructor = &unfo_doc_update_destroy_u,
    .deep_copy = &unfo_doc_update_copy_u
};

