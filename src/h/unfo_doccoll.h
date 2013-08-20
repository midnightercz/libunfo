#ifndef UNFO_DOCCOLL_H
#define UNFO_DOCCOLL_H

#include "unfo_objlist.h"
#include "unfo_types.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>

void unfo_doc_coll_create(UNFO_DocColl* doccoll, UNFO_Object **args);
void unfo_doc_coll_create_u(UNFO_Object* uobj, UNFO_Object **args);
UNFO_DocColl* unfo_doc_coll_copy(UNFO_DocColl *doccoll);
UNFO_Object* unfo_doc_coll_copy_u(UNFO_Object *doccoll);
void unfo_doc_coll_destroy(UNFO_DocColl *doccoll);
void unfo_doc_coll_destroy_u(UNFO_Object *doccoll);

int unfo_doc_coll_short_set(UNFO_DocColl *obj, const char *val);
int unfo_doc_coll_name_set(UNFO_DocColl *obj, const char *val);

char* unfo_doc_coll_short_get(UNFO_DocColl *obj);
char* unfo_doc_coll_name_get(UNFO_DocColl *obj);

void unfo_doc_coll_xml(UNFO_Object *obj, xmlTextWriterPtr writer);

extern UNFO_ObjectInfo UNFO_DocColl_ObjInfo;

#endif //UNFO_DOCCOLL
