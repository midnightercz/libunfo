#include "unfo_obj.h"
#include "unfo_objlist.h"

typedef struct UNFO_DocUpdate {
    UNFO_Object_HEAD
    UNFO_ObjList *references;
    UNFO_ObjList *packages;
} UNFO_DocUpdate;

UNFO_DocUpdate* unfo_doc_update_create();
UNFO_Object* unfo_doc_update_create_u();
UNFO_DocUpdate* unfo_doc_update_copy(UNFO_DocUpdate *docupdate);
UNFO_Object* unfo_doc_update_copy_u(UNFO_Object *docupdate);
void unfo_doc_update_destroy(UNFO_DocUpdate *doc);
void unfo_doc_update_destroy_u(UNFO_Object *doc);

extern UNFO_ObjectInfo UNFO_DocUpdate_ObjInfo;

