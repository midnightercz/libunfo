#include "h/unfo_docref.h"

void unfo_doc_ref_create(UNFO_DocRef* docref, UNFO_Object **args){
    (void)args;
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
UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, id)

UNFO_ObjectInfo UNFO_DocRef_ObjInfo = {
    .obj_size = sizeof(UNFO_DocRef),
    .constructor = &unfo_doc_ref_create_u,
    .destructor = &unfo_doc_ref_destroy_u,
    .deep_copy = &unfo_doc_ref_copy_u
};

void unfo_doc_ref_xml(UNFO_Object *obj, xmlTextWriterPtr writer) {
    const char *val;
    //UNFO_ObjListIt *it;

    xmlTextWriterStartElement(writer, BAD_CAST "reference");
    val = unfo_doc_ref_url_get((UNFO_DocRef*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "href", BAD_CAST val);
    val = unfo_doc_ref_type_get((UNFO_DocRef*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST val);
    val = unfo_doc_ref_title_get((UNFO_DocRef*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "title", BAD_CAST val);
    val = unfo_doc_ref_id_get((UNFO_DocRef*)obj);
    if (val)
        xmlTextWriterWriteAttribute(writer, BAD_CAST "id", BAD_CAST val);
    xmlTextWriterEndElement(writer);
}
