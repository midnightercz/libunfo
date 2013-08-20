#ifndef UNFO_ELEMS_H
#define UNFO_ELEMS_H

#include <string.h>

#include "unfo_types.h"
#include "unfo_docupdate.h"
#include "unfo_doccoll.h"

void unfo_elem_update_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);
void unfo_elem_reference_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);
void unfo_elem_coll_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);
void unfo_elem_pkg_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);
void unfo_elem_sum_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);
void unfo_elem_updated_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);
void unfo_elem_issued_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem);

void unfo_elem_textval_postproc(UNFO_ParseData *data, UNFO_ParseElem *elem);

UNFO_ParseElemType unfo_elem_get_type(const char *elem);

extern const UNFO_ElemAttrInfo UNFO_FROM_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_STATUS_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_TYPE_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_TITLE_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_VERSION_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_DATE_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_HREF_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_REFTYPE_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_SHORT_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_NAME_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_RELEASE_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_EPOCH_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_ARCH_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_SUMTYPE_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_ID_ElemAttrInfo;
extern const UNFO_ElemAttrInfo UNFO_SRC_ElemAttrInfo;

extern const UNFO_ElemInfo* UNFO_ElemInfos[];

#endif
