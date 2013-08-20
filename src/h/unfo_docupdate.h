#ifndef UNFO_DOCUPDATE_H
#define UNFO_DOCUPDATE_H

//#define __USE_XOPEN_EXTENDED 1
#define _XOPEN_SOURCE 500
#include <time.h>

#include "unfo_types.h"
#include "unfo_utils.h"
#include "unfo_docpkg.h"
#include "unfo_docref.h"
#include "unfo_doccoll.h"


#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>


void unfo_doc_update_create(UNFO_DocUpdate *docupdate, UNFO_Object **args);
void unfo_doc_update_create_u(UNFO_Object *uobj, UNFO_Object **args);
UNFO_DocUpdate* unfo_doc_update_copy(UNFO_DocUpdate *docupdate);
UNFO_Object* unfo_doc_update_copy_u(UNFO_Object *docupdate);
void unfo_doc_update_destroy(UNFO_DocUpdate *doc);
void unfo_doc_update_destroy_u(UNFO_Object *doc);

int unfo_doc_update_from_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_status_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_type_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_id_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_title_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_version_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_rights_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_summary_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_description_set(UNFO_DocUpdate *obj, const char *val);
int unfo_doc_update_solution_set(UNFO_DocUpdate *obj, const char *val);

char* unfo_doc_update_from_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_status_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_type_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_id_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_title_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_version_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_rights_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_summary_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_description_get(UNFO_DocUpdate *obj);
char* unfo_doc_update_solution_get(UNFO_DocUpdate *obj);

char* unfo_doc_update_updated_get(UNFO_DocUpdate *docupdate);
char* unfo_doc_update_issued_get(UNFO_DocUpdate *docupdate);
int unfo_doc_update_updated_set(UNFO_DocUpdate *docupdate, const char *date);
int unfo_doc_update_issued_set(UNFO_DocUpdate *docupdate, const char *date);

void unfo_doc_update_xml(UNFO_Object *obj, xmlTextWriterPtr writer);

extern UNFO_ObjectInfo UNFO_DocUpdate_ObjInfo;

#endif
