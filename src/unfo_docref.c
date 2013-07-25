#include "h/unfo_docref.h"

UNFO_DocRef* unfo_doc_ref_create(){
    UNFO_DocRef *docref;
    docref = (UNFO_DocRef*)unfo_object_create(&UNFO_DocRef_ObjInfo);
    return docref;
}

UNFO_CREATE_u(doc_ref, UNFO_DocRef)

UNFO_DocRef* unfo_doc_ref_copy(UNFO_DocRef *docref) {
    UNFO_DocRef *ret;
    ret = (UNFO_DocRef*) unfo_object_copy((UNFO_Object*)docref);
    return ret;
}

UNFO_COPY_u(doc_ref, UNFO_DocRef)

/*inline UNFO_Object* unfo_doc_ref_copy_u(UNFO_Object *docref) {
    return (UNFO_Object*)unfo_doc_ref_copy((UNFO_DocRef*)docref);
}*/

void unfo_doc_ref_destroy(UNFO_DocRef *docref){
    unfo_rtree_destroy(docref->attributes);
    unfo_object_destroy((UNFO_Object*)docref);
}

UNFO_DESTROY_u(doc_ref, UNFO_DocRef)

/*inline void unfo_doc_ref_destroy_u(UNFO_Object *doc){
    unfo_doc_ref_destroy((UNFO_DocRef*)doc);
}*/

UNFO_ObjectInfo UNFO_DocRef_ObjInfo = {
    .obj_size = sizeof(UNFO_DocRef),
    .constructor = &unfo_doc_ref_create_u,
    .destructor = &unfo_doc_ref_destroy_u,
    .deep_copy = &unfo_doc_ref_copy_u
};


