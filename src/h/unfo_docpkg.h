#include "unfo_obj.h"
#include "unfo_objlist.h"
#include "unfo_dict.h"

typedef struct UNFO_DocPkg {
    UNFO_Object_HEAD
    UNFO_RTree *attributes;
} UNFO_DocPkg;

UNFO_DocPkg* unfo_doc_pkg_create();
UNFO_Object* unfo_doc_pkg_create_u();
UNFO_DocPkg* unfo_doc_pkg_copy(UNFO_DocPkg *docref);
UNFO_Object* unfo_doc_pkg_copy_u(UNFO_Object *docref);
void unfo_doc_pkg_destroy(UNFO_DocPkg *docref);
void unfo_doc_pkg_destroy_u(UNFO_Object *docref);

extern UNFO_ObjectInfo UNFO_DocPkg_ObjInfo;


