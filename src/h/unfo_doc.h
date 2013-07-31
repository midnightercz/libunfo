#ifndef UNFO_DOC_H
#define UNFO_DOC_H
#include "unfo_docupdate.h"

#include "unfo_objlist.h"
#include "unfo_obj.h"


typedef struct UNFO_Doc {
    UNFO_Object_HEAD
    char *enc;
    UNFO_ObjList *updates;
} UNFO_Doc;

void unfo_doc_create(UNFO_Doc*);
void unfo_doc_create_u(UNFO_Object* uobj);
UNFO_Doc* unfo_doc_copy(UNFO_Doc *doc);
UNFO_Object* unfo_doc_copy_u(UNFO_Object *doc);
void unfo_doc_destroy(UNFO_Doc *doc);
void unfo_doc_destroy_u(UNFO_Object *doc);

extern UNFO_ObjectInfo UNFO_Doc_ObjInfo;

#endif //UNFO_DOC_H
