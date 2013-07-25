#include "unfo_obj.h"
#include "unfo_objlist.h"
#include "unfo_dict.h"

typedef struct UNFO_DocColl {
    UNFO_Object_HEAD
    UNFO_RTree *attributes;
    UNFO_ObjList *packages;
} UNFO_DocColl;

UNFO_DocColl* unfo_doc_coll_create();
UNFO_Object* unfo_doc_coll_create_u();
UNFO_DocColl* unfo_doc_coll_copy(UNFO_DocColl *docref);
UNFO_Object* unfo_doc_coll_copy_u(UNFO_Object *docref);
void unfo_doc_coll_destroy(UNFO_DocColl *docref);
void unfo_doc_coll_destroy_u(UNFO_Object *docref);

extern UNFO_ObjectInfo UNFO_DocColl_ObjInfo;


