#ifndef UNFO_DOCPKG_H
#define UNFO_DOCPKG_H

#include "unfo_types.h"
#include "unfo_utils.h"
#include "unfo_obj.h"
#include "unfo_objlist.h"
#include "unfo_dict.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>

void unfo_doc_pkg_create(UNFO_DocPkg* docpkg, UNFO_Object **args);
void unfo_doc_pkg_create_u(UNFO_Object* uobj, UNFO_Object **args);
UNFO_DocPkg* unfo_doc_pkg_copy(UNFO_DocPkg *docpkg);
UNFO_Object* unfo_doc_pkg_copy_u(UNFO_Object *docpkg);
signed char unfo_doc_pkg_cmp_u(UNFO_Object* pkg1, UNFO_Object *pkg2);
void unfo_doc_pkg_destroy(UNFO_DocPkg *docpkg);
void unfo_doc_pkg_destroy_u(UNFO_Object *docpkg);

int unfo_doc_pkg_name_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_name_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_version_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_version_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_release_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_release_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_epoch_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_epoch_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_arch_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_arch_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_src_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_src_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_filename_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_filename_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_sum_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_sum_set_u(UNFO_Object *obj, const char *val);
int unfo_doc_pkg_sumtype_set(UNFO_DocPkg *obj, const char *val);
int unfo_doc_pkg_sumtype_set_u(UNFO_Object *obj, const char *val);

char* unfo_doc_pkg_name_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_name_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_version_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_version_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_release_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_release_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_epoch_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_epoch_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_arch_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_arch_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_src_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_src_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_filename_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_filename_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_sum_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_sum_get_u(UNFO_Object *obj);
char* unfo_doc_pkg_sumtype_get(UNFO_DocPkg *obj);
char* unfo_doc_pkg_sumtype_get_u(UNFO_Object *obj);

void unfo_doc_pkg_xml(UNFO_Object *obj, xmlTextWriterPtr writer);

extern UNFO_ObjectInfo UNFO_DocPkg_ObjInfo;

#endif
