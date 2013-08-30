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

char* unfo_doc_ref_str(UNFO_DocRef *obj) {
    char *ret, *tmp;
    int len;
    const int wrap = strlen("<UNFO_DocRef >");
    static const char *attrs[] = {"url", "type", "title", "id"};
    tmp = attrs2str(obj->attrs, attrs, 4);
    len = strlen(tmp);
    ret = malloc(sizeof(char) * (len + wrap + 1));
    sprintf(ret, "<UNFO_DocRef %s>", tmp);
    free(tmp);
    return ret;
}

char* unfo_doc_ref_str_u(UNFO_Object *obj) {
    return unfo_doc_ref_str((UNFO_DocRef*)obj);
}

signed char unfo_doc_ref_cmp(UNFO_DocRef* ref1, UNFO_DocRef *ref2){
    static const char *attrs[] = {"url", "type", "title", "id"};
    static int attrs_len = 4;
    int i;
    char *tmp1, *tmp2;

    for (i = 0; i < attrs_len; i++) {
        tmp1 = unfo_rtree_get(ref1->attrs, attrs[i]);
        tmp2 = unfo_rtree_get(ref2->attrs, attrs[i]);
        if (!__unfo_strcmp(tmp1, tmp2))
            return 0;
    }
    return 1;
}
UNFO_CMP_u(doc_ref, UNFO_DocRef)

UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, url)
UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, type)
UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, title)
UNFO_GETSET_ATTR(UNFO_DocRef, doc_ref, id)

UNFO_ObjectInfo UNFO_DocRef_ObjInfo = {
    .obj_size = sizeof(UNFO_DocRef),
    .constructor = &unfo_doc_ref_create_u,
    .destructor = &unfo_doc_ref_destroy_u,
    .deep_copy = &unfo_doc_ref_copy_u,
    .to_str = &unfo_doc_ref_str_u,
    .obj_cmp = &unfo_doc_ref_cmp_u
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
