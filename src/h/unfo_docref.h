#include "unfo_obj.h"
#include "unfo_objlist.h"
#include "unfo_dict.h"

typedef struct UNFO_DocRef {
    UNFO_Object_HEAD
    UNFO_RTree *attributes;
} UNFO_DocRef;

UNFO_DocRef* unfo_doc_ref_create();
UNFO_Object* unfo_doc_ref_create_u();
UNFO_DocRef* unfo_doc_ref_copy(UNFO_DocRef *docref);
UNFO_Object* unfo_doc_ref_copy_u(UNFO_Object *obj);
void unfo_doc_ref_destroy(UNFO_DocRef *docref);
void unfo_doc_ref_destroy_u(UNFO_Object *docref);

extern UNFO_ObjectInfo UNFO_DocRef_ObjInfo;

