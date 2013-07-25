#include "h/unfo_docupdate.h"

UNFO_DocUpdate* unfo_doc_update_create(){
    UNFO_DocUpdate *docupdate;
    docupdate = (UNFO_DocUpdate*)unfo_object_create(&UNFO_DocUpdate_ObjInfo);
    return docupdate;
}

inline UNFO_Object* unfo_doc_update_create_u(){
    return (UNFO_Object*)unfo_doc_update_create();
}

UNFO_DocUpdate* unfo_doc_update_copy(UNFO_DocUpdate *docupdate) {
    UNFO_DocUpdate *ret;
    ret = (UNFO_DocUpdate*) unfo_object_copy((UNFO_Object*)docupdate);
    return ret;
}

inline UNFO_Object* unfo_doc_update_copy_u(UNFO_Object *docupdate) {
    return (UNFO_Object*)unfo_doc_update_copy((UNFO_DocUpdate*)docupdate);
}

void unfo_doc_update_destroy(UNFO_DocUpdate *doc){
    unfo_object_destroy((UNFO_Object*)doc);
}

inline void unfo_doc_update_destroy_u(UNFO_Object *doc){
    unfo_doc_update_destroy((UNFO_DocUpdate*)doc);
}

UNFO_ObjectInfo UNFO_DocUpdate_ObjInfo = {
    .obj_size = sizeof(UNFO_DocUpdate),
    .constructor = &unfo_doc_update_create_u,
    .destructor = &unfo_doc_update_destroy_u,
    .deep_copy = &unfo_doc_update_copy_u
};

