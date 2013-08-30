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

char* unfo_doc_coll_str(UNFO_DocColl *obj) {
    char *ret, *tmp;
    int len;
    const int wrap = strlen("<UNFO_DocColl >");
    static const char *attrs[] = {"short", "name"};
    tmp = attrs2str(obj->attrs, attrs, 2);
    len = strlen(tmp);
    ret = malloc(sizeof(char) * (len + wrap + 1));
    sprintf(ret, "<UNFO_DocPkg %s>", tmp);
    free(tmp);
    return ret;
}

char* unfo_doc_coll_str_u(UNFO_Object *obj) {
    return unfo_doc_coll_str((UNFO_DocColl*)obj);
}

signed char unfo_doc_coll_cmp(UNFO_DocColl* coll1, UNFO_DocColl *coll2){
    static const char *attrs[] = {"short", "name"};
    static int attrs_len = 2;
    int i;
    char *tmp1, *tmp2;

    for (i = 0; i < attrs_len; i++) {
        tmp1 = unfo_rtree_get(coll1->attrs, attrs[i]);
        tmp2 = unfo_rtree_get(coll2->attrs, attrs[i]);
        if (!__unfo_strcmp(tmp1, tmp2)) {
            printf("coll differ\n");
            return 0;
        }
    }
    return unfo_object_cmp((UNFO_Object*)coll1->pkgs,
                           (UNFO_Object*)coll2->pkgs);
}
UNFO_CMP_u(doc_coll, UNFO_DocColl)

UNFO_GETSET_ATTR(UNFO_DocColl, doc_coll, short)
UNFO_GETSET_ATTR(UNFO_DocColl, doc_coll, name)

UNFO_ObjectInfo UNFO_DocColl_ObjInfo = {
    .obj_size = sizeof(UNFO_DocColl),
    .constructor = &unfo_doc_coll_create_u,
    .destructor = &unfo_doc_coll_destroy_u,
    .deep_copy = &unfo_doc_coll_copy_u,
    .to_str = &unfo_doc_coll_str_u,
    .obj_cmp = &unfo_doc_coll_cmp_u
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
    for (it = ((UNFO_DocColl*)obj)->pkgs->first; it != NULL; it = it->next)
        unfo_doc_pkg_xml(it->unfo_obj, writer);

    xmlTextWriterEndElement(writer);
}
