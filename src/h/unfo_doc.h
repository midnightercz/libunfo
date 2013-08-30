#ifndef UNFO_DOC_H
#define UNFO_DOC_H
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>

#include "unfo_docupdate.h"
#include "unfo_types.h"
#include "unfo_log.h"


void unfo_doc_create(UNFO_Doc* doc, UNFO_Object **args);
void unfo_doc_create_u(UNFO_Object* uobj, UNFO_Object **args);
UNFO_Doc* unfo_doc_copy(UNFO_Doc *doc);
UNFO_Object* unfo_doc_copy_u(UNFO_Object *doc);
void unfo_doc_destroy(UNFO_Doc *doc);
void unfo_doc_destroy_u(UNFO_Object *doc);
signed char unfo_doc_cmp_u(UNFO_Object *obj1, UNFO_Object *obj2);

void unfo_doc_xml_f(UNFO_Doc* doc,  char *filename, char *enc, UNFO_Log *log);
char* unfo_doc_xml_str(UNFO_Doc* doc, char *enc, UNFO_Log *log);
void unfo_doc_xml(UNFO_Object *obj, xmlTextWriterPtr writer);

extern UNFO_ObjectInfo UNFO_Doc_ObjInfo;

#endif //UNFO_DOC_H
