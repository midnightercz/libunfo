#include "h/unfo_docref.h"

void unfo_doc_ref_create(UNFO_DocRef* docref){
    docref->attrs = unfo_rtree_create(&__unfo_str_clone,
                                      &__unfo_str_clone, &free);
}
UNFO_CREATE_u(doc_ref, UNFO_DocRef)

UNFO_DocRef* unfo_doc_ref_copy(UNFO_DocRef *docref) {
    UNFO_DocRef *ret;
    ret = (UNFO_DocRef*) unfo_object_copy((UNFO_Object*)docref);
    return ret;
}
UNFO_COPY_u(doc_ref, UNFO_DocRef)

void unfo_doc_ref_destroy(UNFO_DocRef *docref){
    unfo_rtree_destroy(docref->attrs);
}
UNFO_DESTROY_u(doc_ref, UNFO_DocRef)


UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, url)
UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, type)
UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, title)

UNFO_ObjectInfo UNFO_DocRef_ObjInfo = {
    .obj_size = sizeof(UNFO_DocRef),
    .constructor = &unfo_doc_ref_create_u,
    .destructor = &unfo_doc_ref_destroy_u,
    .deep_copy = &unfo_doc_ref_copy_u
};


