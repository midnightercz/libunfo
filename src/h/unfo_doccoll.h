#ifndef UNFO_DOCCOLL_H
#define UNFO_DOCCOLL_H

#include "unfo_obj.h"
#include "unfo_objlist.h"
#include "unfo_dict.h"

typedef struct UNFO_DocColl {
    UNFO_Object_HEAD
    UNFO_RTree *attrs;
    UNFO_ObjList *packages;
} UNFO_DocColl;

void unfo_doc_coll_create(UNFO_DocColl* doccoll);
void unfo_doc_coll_create_u(UNFO_Object* uobj);
UNFO_DocColl* unfo_doc_coll_copy(UNFO_DocColl *doccoll);
UNFO_Object* unfo_doc_coll_copy_u(UNFO_Object *doccoll);
void unfo_doc_coll_destroy(UNFO_DocColl *doccoll);
void unfo_doc_coll_destroy_u(UNFO_Object *doccoll);

int unfo_doc_coll_short_set(UNFO_DocColl *obj, char *val);
int unfo_doc_coll_name_set(UNFO_DocColl *obj, char *val);

char* unfo_doc_coll_short_get(UNFO_DocColl *obj);
char* unfo_doc_coll_name_get(UNFO_DocColl *obj);

extern UNFO_ObjectInfo UNFO_DocColl_ObjInfo;

#endif //UNFO_DOCCOLL
