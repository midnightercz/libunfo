#ifndef UNFO_DOCREF_H
#define UNFO_DOCREF_H

#include "unfo_obj.h"
#include "unfo_objlist.h"
#include "unfo_dict.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>

typedef struct UNFO_DocRef {
    UNFO_Object_HEAD
    UNFO_RTree *attrs;
} UNFO_DocRef;

void unfo_doc_ref_create(UNFO_DocRef *docref, UNFO_Object **args);
void unfo_doc_ref_create_u(UNFO_Object *uobj, UNFO_Object **args);
UNFO_DocRef* unfo_doc_ref_copy(UNFO_DocRef *docref);
UNFO_Object* unfo_doc_ref_copy_u(UNFO_Object *obj);
void unfo_doc_ref_destroy(UNFO_DocRef *docref);
void unfo_doc_ref_destroy_u(UNFO_Object *docref);

int unfo_doc_ref_url_set(UNFO_DocRef *obj, const char *val);
int unfo_doc_ref_url_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_ref_type_set(UNFO_DocRef *obj, const char *val);
int unfo_doc_ref_type_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_ref_title_set(UNFO_DocRef *obj, const char *val);
int unfo_doc_ref_title_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_ref_id_set(UNFO_DocRef *obj, const char *val);
int unfo_doc_ref_id_set_u(UNFO_Object *obj, const char *val);

char* unfo_doc_ref_url_get(UNFO_DocRef *obj);
char* unfo_doc_ref_url_get_u(UNFO_Object *obj);
char* unfo_doc_ref_type_get(UNFO_DocRef *obj);
char* unfo_doc_ref_type_get_u(UNFO_Object *obj);
char* unfo_doc_ref_title_get(UNFO_DocRef *obj);
char* unfo_doc_ref_title_get_u(UNFO_Object *obj);
char* unfo_doc_ref_id_get(UNFO_DocRef *obj);
char* unfo_doc_ref_id_get_u(UNFO_Object *obj);

void unfo_doc_ref_xml(UNFO_Object *obj, xmlTextWriterPtr writer);

extern UNFO_ObjectInfo UNFO_DocRef_ObjInfo;

#endif //UNFO_DOCREF_H
