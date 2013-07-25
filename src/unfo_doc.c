#include "h/unfo_doc.h"

UNFO_Doc* unfo_doc_create() {
    UNFO_Doc *doc;
    doc = (UNFO_Doc*)unfo_object_create(&UNFO_Doc_ObjInfo);
    return doc;
}

UNFO_CREATE_u(doc, UNFO_Doc)

UNFO_Doc* unfo_doc_copy(UNFO_Doc *doc) {
    UNFO_Doc *ret;
    ret = (UNFO_Doc*) unfo_object_copy((UNFO_Object*)doc);
    ret->updates = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)doc->updates);
    return ret;
}

UNFO_COPY_u(doc, UNFO_Doc)

/*inline UNFO_Object* unfo_doc_copy_u(UNFO_Object *doc) {
    return (UNFO_Object*)unfo_doc_copy((UNFO_Doc*)doc);
}*/

void unfo_doc_destroy(UNFO_Doc *doc) {
    unfo_object_destroy((UNFO_Object*)doc);
}

UNFO_DESTROY_u(doc, UNFO_Doc)

/*inline void unfo_doc_destroy_u(UNFO_Object *doc) {
    unfo_doc_destroy((UNFO_Doc*)doc);
}*/

UNFO_ObjectInfo UNFO_Doc_ObjInfo = {
    .obj_size = sizeof(UNFO_Doc),
    .constructor = &unfo_doc_create_u,
    .destructor = &unfo_doc_destroy_u,
    .deep_copy = &unfo_doc_copy_u
};
