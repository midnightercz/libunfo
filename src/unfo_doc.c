#include "h/unfo_doc.h"
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>

void unfo_doc_create(UNFO_Doc* doc, UNFO_Object **args) {
    (void)args;
    (void)doc;
    if (args && args[0]->obj_info == &UNFO_DocUpdate_ObjInfo) {
            doc->updates = (UNFO_ObjList*)unfo_object_copy(args[0]);
    } else {
        doc->updates = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    }
}
UNFO_CREATE_u(doc, UNFO_Doc)

UNFO_Doc* unfo_doc_copy(UNFO_Doc *doc) {
    UNFO_Doc *ret;
    ret = (UNFO_Doc*) unfo_object_copy((UNFO_Object*)doc);
    ret->updates = (UNFO_ObjList*) unfo_object_copy((UNFO_Object*)doc->updates);
    return ret;
}
UNFO_COPY_u(doc, UNFO_Doc)

void unfo_doc_destroy(UNFO_Doc *doc) {
    unfo_object_destroy((UNFO_Object*)doc->updates);
}
UNFO_DESTROY_u(doc, UNFO_Doc)

UNFO_ObjectInfo UNFO_Doc_ObjInfo = {
    .obj_size = sizeof(UNFO_Doc),
    .constructor = &unfo_doc_create_u,
    .destructor = &unfo_doc_destroy_u,
    .deep_copy = &unfo_doc_copy_u
};

void unfo_doc_xml_f(UNFO_Doc* doc,  char *filename, char *enc, UNFO_Log *log) {
    xmlDocPtr xmldoc;
    xmlTextWriterPtr writer;
    int rc;
    writer = xmlNewTextWriterDoc(&xmldoc, 0);

    rc = xmlTextWriterStartDocument(writer, NULL, enc, NULL);
    if (rc < 0)
        unfo_log_error_x(log, UNFO_LOG_XMLGEN, 0);
    unfo_doc_xml((UNFO_Object*)doc, writer);
    rc = xmlTextWriterEndDocument(writer);
    if (rc < 0)
        unfo_log_error_x(log, UNFO_LOG_WRITEF, 1, unfo_str(filename));
    rc = xmlSaveFormatFileEnc(filename, xmldoc, NULL, 1);
    if (rc < 0)
        unfo_log_error_x(log, UNFO_LOG_WRITEF, 1, unfo_str(filename));
    xmlFreeTextWriter(writer);
    xmlFreeDoc(xmldoc);
    xmlCleanupParser();
    xmlMemoryDump();
}

char* unfo_doc_xml_str(UNFO_Doc* doc, char *enc, UNFO_Log *log) {
    xmlDocPtr xmldoc;
    xmlBuffer * xmlbuff;
    xmlOutputBuffer * xmlobuff;
    xmlTextWriterPtr writer;
    int rc;
    char *xmlstr, *ret;

    writer = xmlNewTextWriterDoc(&xmldoc, 0);
    xmlbuff = xmlBufferCreate();
    xmlobuff = xmlOutputBufferCreateBuffer(xmlbuff, 0);
    rc = xmlTextWriterStartDocument(writer, NULL, enc, NULL);
    if (rc < 0)
        unfo_log_error_x(log, UNFO_LOG_XMLGEN, 0);
    unfo_doc_xml((UNFO_Object*)doc, writer);
    rc = xmlTextWriterEndDocument(writer);
    xmlSaveFormatFileTo(xmlobuff, xmldoc, NULL, 1);

    xmlFreeTextWriter(writer);
    xmlFreeDoc(xmldoc);

    xmlstr = (char*) xmlBufferContent(xmlbuff);
    ret = malloc(sizeof(char) * (strlen(xmlstr)+1));
    if (!ret) {
    } else {
        strcpy(ret, xmlstr);
    }
    xmlBufferFree(xmlbuff);
    xmlCleanupParser();
    xmlMemoryDump();
    return ret;
}

void unfo_doc_xml(UNFO_Object *obj, xmlTextWriterPtr writer) {
    UNFO_ObjListIt *it;
    xmlTextWriterStartElement(writer, BAD_CAST "updates");
    for (it = ((UNFO_Doc*)obj)->updates->first; it != NULL; it = it->next)
        unfo_doc_update_xml(it->unfo_obj, writer);
    xmlTextWriterEndElement(writer);
}
