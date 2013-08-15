#ifndef UNFO_PARSE_TYPES_H
#define UNFO_PARSE_TYPES_H
#include <expat.h>
#include "unfo_hslist.h"
#include "unfo_objlist.h"
#include "unfo_obj.h"
#include "unfo_dict.h"

typedef struct UNFO_ParseElem UNFO_ParseElem;
typedef struct UNFO_ParseData UNFO_ParseData;

typedef struct UNFO_ElemAttrInfo UNFO_ElemAttrInfo;
typedef struct UNFO_ElemInfo UNFO_ElemInfo;

typedef struct UNFO_LogEntry UNFO_LogEntry;
typedef struct UNFO_Log UNFO_Log;


typedef struct UNFO_Doc UNFO_Doc;
typedef struct UNFO_DocUpdate UNFO_DocUpdate;

/************ ELEMS_H **********/
typedef enum UNFO_ParseElemType {
                UNFO_ELEM_UPDATES,
                UNFO_ELEM_UPDATE,
                UNFO_ELEM_ID,
                UNFO_ELEM_TITLE,
                UNFO_ELEM_UPDATED,
                UNFO_ELEM_ISSUED,
                UNFO_ELEM_RIGHTS,
                UNFO_ELEM_SUMMARY,
                UNFO_ELEM_DESCRIPTION,
                UNFO_ELEM_SOLUTION,
                UNFO_ELEM_REFERENCES,
                UNFO_ELEM_REFERENCE,
                UNFO_ELEM_PKGLIST,
                UNFO_ELEM_COLLECTION,
                UNFO_ELEM_NAME,
                UNFO_ELEM_PACKAGE,
                UNFO_ELEM_FILENAME,
                UNFO_ELEM_SUM,
                UNFO_ELEM_UNKNOWN,
                UNFO_ELEM_NONE
                } UNFO_ParseElemType;

struct UNFO_ElemAttrInfo {
    char *name;
    signed char (*val_check)(const char*);
};

struct UNFO_ElemInfo{
    char *name;
    UNFO_ParseElemType ancestor;
    const UNFO_ElemAttrInfo **attributes;
    void (*preproc)(UNFO_ParseData*, UNFO_ParseElem *elem);
    void (*postproc)(UNFO_ParseData*, UNFO_ParseElem *elem);
};

/************ PARSE_H **********/
struct UNFO_ParseElem {
    char *name;
    const char **attrs;
    unsigned int attrs_len;
    UNFO_ParseElemType type;
};

struct UNFO_ParseData {
    UNFO_Log *log;
    XML_Parser parser;
    UNFO_HSList *elem_stack;
    UNFO_HSList *cdata_stack;
    size_t cdata_stack_strlen;
    UNFO_Doc *unfo_doc;
};

/************ LOG_H **********/
struct UNFO_LogEntry {
    UNFO_Object **args;
    int arg_count;
    int code;
    int type;
};

struct UNFO_Log {
    UNFO_Object_HEAD
    UNFO_HSList *entries;
};


/************ DOC_H **********/
struct UNFO_Doc {
    UNFO_Object_HEAD
    char *enc;
    UNFO_ObjList *updates;
};

/************ DOCUPDATE_H **********/

struct UNFO_DocUpdate {
    UNFO_Object_HEAD
    UNFO_ObjList *refs;
    UNFO_ObjList *colls;
    UNFO_RTree *attrs;
    UNFO_RTree *date_attrs;
};

/************ DOCCOLL **************/
typedef struct UNFO_DocColl {
    UNFO_Object_HEAD
    UNFO_RTree *attrs;
    UNFO_ObjList *pkgs;
} UNFO_DocColl;

/************ DOCPKG_H **********/
typedef struct UNFO_DocPkg {
    UNFO_Object_HEAD
    UNFO_RTree *attrs;
} UNFO_DocPkg;

#endif


