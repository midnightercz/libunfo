#include "h/unfo_doccoll.h"

void unfo_doc_coll_create(UNFO_DocColl* doccoll, UNFO_Object **args){
    (void)args;
    doccoll->attrs = unfo_rtree_create(&__unfo_str_clone,
                                      &__unfo_str_clone, &free);
    doccoll->pkgs = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo,
                                                         NULL);
}
UNFO_CREATE_u(doc_coll, UNFO_DocColl)

UNFO_DocColl* unfo_doc_coll_copy(UNFO_DocColl *doccoll) {
    UNFO_DocColl *ret;
    ret = (UNFO_DocColl*) unfo_object_copy((UNFO_Object*)doccoll);
    ret->pkgs = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)doccoll->pkgs);
    return ret;
}
UNFO_COPY_u(doc_coll, UNFO_DocColl)

void unfo_doc_coll_destroy(UNFO_DocColl *doccoll){
    unfo_object_destroy((UNFO_Object*)doccoll->pkgs);
    unfo_rtree_destroy(doccoll->attrs);
}
UNFO_DESTROY_u(doc_coll, UNFO_DocColl)

UNFO_GETSET_ATTR(UNFO_DocColl, doc_coll, short)
UNFO_GETSET_ATTR(UNFO_DocColl, doc_coll, name)

UNFO_ObjectInfo UNFO_DocColl_ObjInfo = {
    .obj_size = sizeof(UNFO_DocColl),
    .constructor = &unfo_doc_coll_create_u,
    .destructor = &unfo_doc_coll_destroy_u,
    .deep_copy = &unfo_doc_coll_copy_u
};

void unfo_doc_coll_xml(UNFO_Object *obj, xmlTextWriterPtr writer) {
    const char *val;
    UNFO_ObjListIt *it;

    xmlTextWriterStartElement(writer, BAD_CAST "collection");
    val = unfo_doc_coll_short_get((UNFO_DocColl*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "short", BAD_CAST val);
    xmlTextWriterStartElement(writer, BAD_CAST "name");
    val = unfo_doc_coll_name_get((UNFO_DocColl*)obj);
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);

    xmlTextWriterEndElement(writer);
}
