#include "h/unfo_docupdate.h"

void* __unfo_date_clone(void *date){
    struct tm *ret;
    ret = malloc(sizeof(struct tm));
    memcpy(ret, date, sizeof(struct tm));
    /*ret->tm_sec = ((struct tm*)date)->tm_sec;
    ret->tm_min = ((struct tm*)date)->tm_min;
    ret->tm_hour = ((struct tm*)date)->tm_hour;*/

    return (void*)ret;
}

void unfo_doc_update_create(UNFO_DocUpdate *docupdate, UNFO_Object **args){
    (void)args;

    docupdate->colls = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo,
                                                         NULL);
    docupdate->refs = (UNFO_ObjList*) unfo_object_create(&UNFO_ObjList_ObjInfo,
                                                         NULL);
    docupdate->attrs = unfo_rtree_create(&__unfo_str_clone,
                                         &__unfo_str_clone, &free);
    docupdate->date_attrs = unfo_rtree_create(&__unfo_date_clone,
                                              &__unfo_date_clone, &free);
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
    ret->date_attrs = unfo_rtree_clone(docupdate->date_attrs);
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
    if (!timeinfo) return "";
    strftime(ret, 20, "%F %T", timeinfo);
    return ret;
}

int unfo_doc_update_updated_set(UNFO_DocUpdate *docupdate, const char *date) {
    struct tm timeinfo, *timeinfo2;
    printf("DATE %s\n", date);
    if (strptime(date, "%Y-%d-%m %H:%M:%S", &timeinfo) == NULL) {
        printf("failed to parse\n");
        return 0;
    }
    timeinfo2 = __unfo_date_clone(&timeinfo);
    unfo_rtree_set(docupdate->date_attrs, "updated", timeinfo2);
    return 1;
}

char* unfo_doc_update_issued_get(UNFO_DocUpdate *docupdate) {
    struct tm *timeinfo;
    char *ret;
    ret = malloc(sizeof(char)*20);
    UNFO_Check_Malloc(ret, NULL)

    timeinfo = (struct tm*)unfo_rtree_get(docupdate->date_attrs, "updated");
    if (!timeinfo) return "";
    printf("%d %d %d\n", timeinfo->tm_sec, timeinfo->tm_min, timeinfo->tm_hour);
    strftime(ret, 20, "%F %T", timeinfo);
    return ret;
}

int unfo_doc_update_issued_set(UNFO_DocUpdate *docupdate, const char *date) {
    struct tm timeinfo, *timeinfo2;
    printf("DATE %s\n", date);
    if (strptime(date, "%Y-%d-%m %H:%M:%S", &timeinfo) == NULL) {
        printf("failed to parse\n");
        return 0;
    }
    timeinfo2 = __unfo_date_clone(&timeinfo);
    unfo_rtree_set(docupdate->date_attrs, "updated", timeinfo2);
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

void unfo_doc_update_xml(UNFO_Object *obj, xmlTextWriterPtr writer) {
    char *val;
    UNFO_ObjListIt *it;
    xmlTextWriterStartElement(writer, BAD_CAST "update");
    val = unfo_doc_update_from_get((UNFO_DocUpdate*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "from", BAD_CAST val);
    val = unfo_doc_update_status_get((UNFO_DocUpdate*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "status", BAD_CAST val);
    val = unfo_doc_update_type_get((UNFO_DocUpdate*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST val);
    val = unfo_doc_update_version_get((UNFO_DocUpdate*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "version", BAD_CAST val);
    val = unfo_doc_update_id_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "id");
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    val = unfo_doc_update_title_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "title");
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    val = unfo_doc_update_issued_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "issued");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "date", BAD_CAST val);
    xmlTextWriterEndElement(writer);
    free(val);
    val = unfo_doc_update_updated_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "updated");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "date", BAD_CAST val);
    xmlTextWriterEndElement(writer);
    free(val);
    val = unfo_doc_update_rights_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "rights");
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    val = unfo_doc_update_summary_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "summary");
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    val = unfo_doc_update_description_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "description");
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    val = unfo_doc_update_solution_get((UNFO_DocUpdate*)obj);
    xmlTextWriterStartElement(writer, BAD_CAST "solution");
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    xmlTextWriterStartElement(writer, BAD_CAST "references");
    for (it = ((UNFO_DocUpdate*)obj)->refs->first; it != NULL; it = it->next)
        unfo_doc_ref_xml(it->unfo_obj, writer);
    xmlTextWriterEndElement(writer);
    xmlTextWriterStartElement(writer, BAD_CAST "pkglist");
    for (it = ((UNFO_DocUpdate*)obj)->colls->first; it != NULL; it = it->next)
        unfo_doc_coll_xml(it->unfo_obj, writer);
    xmlTextWriterEndElement(writer);
    xmlTextWriterEndElement(writer);
}
