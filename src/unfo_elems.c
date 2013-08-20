#include "h/unfo_elems.h"


UNFO_ParseElemType unfo_elem_get_type(const char *elem) {
    if (!strcmp(elem, "updates"))       return UNFO_ELEM_UPDATES;
    if (!strcmp(elem, "update"))        return UNFO_ELEM_UPDATE;
    if (!strcmp(elem, "id"))            return UNFO_ELEM_ID;
    if (!strcmp(elem, "title"))         return UNFO_ELEM_TITLE;
    if (!strcmp(elem, "issued"))        return UNFO_ELEM_ISSUED;
    if (!strcmp(elem, "updated"))       return UNFO_ELEM_UPDATED;
    if (!strcmp(elem, "rights"))        return UNFO_ELEM_RIGHTS;
    if (!strcmp(elem, "summary"))       return UNFO_ELEM_SUMMARY;
    if (!strcmp(elem, "description"))   return UNFO_ELEM_DESCRIPTION;
    if (!strcmp(elem, "solution"))      return UNFO_ELEM_SOLUTION;
    if (!strcmp(elem, "references"))    return UNFO_ELEM_REFERENCES;
    if (!strcmp(elem, "reference"))     return UNFO_ELEM_REFERENCE;
    if (!strcmp(elem, "pkglist"))       return UNFO_ELEM_PKGLIST;
    if (!strcmp(elem, "collection"))    return UNFO_ELEM_COLLECTION;
    if (!strcmp(elem, "name"))          return UNFO_ELEM_NAME;
    if (!strcmp(elem, "package"))       return UNFO_ELEM_PACKAGE;
    if (!strcmp(elem, "filename"))      return UNFO_ELEM_FILENAME;
    if (!strcmp(elem, "sum"))           return UNFO_ELEM_SUM;
    return UNFO_ELEM_UNKNOWN;
}

const UNFO_ElemInfo UNFO_UNKNOWN_ElemInfo = {
    .name = "???",
    .ancestor = UNFO_ELEM_NONE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = NULL
};

const UNFO_ElemInfo UNFO_UPDATES_ElemInfo = {
    .name = "updates",
    .ancestor = UNFO_ELEM_NONE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = NULL
};

const UNFO_ElemInfo UNFO_UPDATE_ElemInfo = {
    .name = "update",
    .ancestor = UNFO_ELEM_UPDATES,
    .attributes = (const UNFO_ElemAttrInfo*[]){
                        &UNFO_FROM_ElemAttrInfo,
                        &UNFO_STATUS_ElemAttrInfo,
                        &UNFO_TYPE_ElemAttrInfo,
                        &UNFO_VERSION_ElemAttrInfo,
                        NULL
                        },
    .preproc = &unfo_elem_update_preproc,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_ID_ElemInfo = {
    .name = "id",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_TITLE_ElemInfo = {
    .name = "title",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_ISSUED_ElemInfo = {
    .name = "issued",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){&UNFO_DATE_ElemAttrInfo, NULL},
    .preproc = unfo_elem_issued_preproc,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_UPDATED_ElemInfo = {
    .name = "updated",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){&UNFO_DATE_ElemAttrInfo, NULL},
    .preproc = unfo_elem_updated_preproc,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_RIGHTS_ElemInfo = {
    .name = "rights",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_SUMMARY_ElemInfo = {
    .name = "summary",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_DESCRIPTION_ElemInfo = {
    .name = "description",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_SOLUTION_ElemInfo = {
    .name = "solution",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_REFERENCES_ElemInfo = {
    .name = "references",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_REFERENCE_ElemInfo = {
    .name = "reference",
    .ancestor = UNFO_ELEM_REFERENCES,
    .attributes = (const UNFO_ElemAttrInfo*[]){
                                &UNFO_HREF_ElemAttrInfo,
                                &UNFO_ID_ElemAttrInfo,
                                &UNFO_REFTYPE_ElemAttrInfo,
                                &UNFO_TITLE_ElemAttrInfo, NULL},
    .preproc =  &unfo_elem_reference_preproc,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_PKGLIST_ElemInfo = {
    .name = "pkglist",
    .ancestor = UNFO_ELEM_UPDATE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_COLLECTION_ElemInfo = {
    .name = "collection",
    .ancestor = UNFO_ELEM_PKGLIST,
    .attributes = (const UNFO_ElemAttrInfo*[]){&UNFO_SHORT_ElemAttrInfo, NULL},
    .preproc = &unfo_elem_coll_preproc,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_NAME_ElemInfo = {
    .name = "name",
    .ancestor = UNFO_ELEM_COLLECTION,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_PACKAGE_ElemInfo = {
    .name = "package",
    .ancestor = UNFO_ELEM_COLLECTION,
    .attributes = (const UNFO_ElemAttrInfo*[]){
                            &UNFO_NAME_ElemAttrInfo,
                            &UNFO_VERSION_ElemAttrInfo,
                            &UNFO_RELEASE_ElemAttrInfo,
                            &UNFO_EPOCH_ElemAttrInfo,
                            &UNFO_SRC_ElemAttrInfo,
                            &UNFO_ARCH_ElemAttrInfo, NULL},
    .preproc = unfo_elem_pkg_preproc,
    .postproc = NULL
};
const UNFO_ElemInfo UNFO_FILENAME_ElemInfo = {
    .name = "filename",
    .ancestor = UNFO_ELEM_PACKAGE,
    .attributes = (const UNFO_ElemAttrInfo*[]){NULL},
    .preproc = NULL,
    .postproc = unfo_elem_textval_postproc
};
const UNFO_ElemInfo UNFO_SUM_ElemInfo = {
    .name = "sum",
    .ancestor = UNFO_ELEM_PACKAGE,
    .attributes = (const UNFO_ElemAttrInfo*[]){&UNFO_SUMTYPE_ElemAttrInfo,
                                               NULL},
    .preproc = unfo_elem_sum_preproc,
    .postproc = unfo_elem_textval_postproc
};


const UNFO_ElemAttrInfo UNFO_FROM_ElemAttrInfo = {
    .name="from"
};
const UNFO_ElemAttrInfo UNFO_STATUS_ElemAttrInfo = {
    .name="status"
};
const UNFO_ElemAttrInfo UNFO_TYPE_ElemAttrInfo = {
    .name="type"
};
const UNFO_ElemAttrInfo UNFO_VERSION_ElemAttrInfo = {
    .name="version"
};
const UNFO_ElemAttrInfo UNFO_DATE_ElemAttrInfo = {
    .name="date"
};
const UNFO_ElemAttrInfo UNFO_HREF_ElemAttrInfo = {
    .name="href"
};
const UNFO_ElemAttrInfo UNFO_REFTYPE_ElemAttrInfo = {
    .name="type"
};
const UNFO_ElemAttrInfo UNFO_TITLE_ElemAttrInfo = {
    .name="title"
};
const UNFO_ElemAttrInfo UNFO_SHORT_ElemAttrInfo = {
    .name="short"
};
const UNFO_ElemAttrInfo UNFO_NAME_ElemAttrInfo = {
    .name="name"
};
const UNFO_ElemAttrInfo UNFO_RELEASE_ElemAttrInfo = {
    .name="release"
};
const UNFO_ElemAttrInfo UNFO_EPOCH_ElemAttrInfo = {
    .name="epoch"
};
const UNFO_ElemAttrInfo UNFO_ARCH_ElemAttrInfo = {
    .name="arch"
};
const UNFO_ElemAttrInfo UNFO_SUMTYPE_ElemAttrInfo = {
    .name="type"
};
const UNFO_ElemAttrInfo UNFO_ID_ElemAttrInfo = {
    .name="id"
};
const UNFO_ElemAttrInfo UNFO_SRC_ElemAttrInfo = {
    .name="src"
};

const UNFO_ElemInfo* UNFO_ElemInfos[] = {
    [UNFO_ELEM_UPDATES]     = &UNFO_UPDATES_ElemInfo,
    [UNFO_ELEM_UPDATE]      = &UNFO_UPDATE_ElemInfo,
    [UNFO_ELEM_ID]          = &UNFO_ID_ElemInfo,
    [UNFO_ELEM_TITLE]       = &UNFO_TITLE_ElemInfo,
    [UNFO_ELEM_ISSUED]      = &UNFO_ISSUED_ElemInfo,
    [UNFO_ELEM_UPDATED]     = &UNFO_UPDATED_ElemInfo,
    [UNFO_ELEM_RIGHTS]      = &UNFO_RIGHTS_ElemInfo,
    [UNFO_ELEM_SUMMARY]     = &UNFO_SUMMARY_ElemInfo,
    [UNFO_ELEM_DESCRIPTION] = &UNFO_DESCRIPTION_ElemInfo,
    [UNFO_ELEM_SOLUTION]    = &UNFO_SOLUTION_ElemInfo,
    [UNFO_ELEM_REFERENCES]  = &UNFO_REFERENCES_ElemInfo,
    [UNFO_ELEM_REFERENCE]   = &UNFO_REFERENCE_ElemInfo,
    [UNFO_ELEM_PKGLIST]     = &UNFO_PKGLIST_ElemInfo,
    [UNFO_ELEM_COLLECTION]  = &UNFO_COLLECTION_ElemInfo,
    [UNFO_ELEM_NAME]        = &UNFO_NAME_ElemInfo,
    [UNFO_ELEM_PACKAGE]     = &UNFO_PACKAGE_ElemInfo,
    [UNFO_ELEM_FILENAME]    = &UNFO_FILENAME_ElemInfo,
    [UNFO_ELEM_SUM]         = &UNFO_SUM_ElemInfo,
    [UNFO_ELEM_UNKNOWN]     = &UNFO_UNKNOWN_ElemInfo
};

void unfo_elem_update_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    UNFO_DocUpdate *update;
    update = (UNFO_DocUpdate*)unfo_object_create(&UNFO_DocUpdate_ObjInfo, NULL);
    unfo_objlist_append_x(data->unfo_doc->updates, (UNFO_Object*)update);
    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (__unfo_strcmp(elem->attrs[i], "from") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_update_from_set(update, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "status") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_update_status_set(update, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "type") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_update_type_set(update, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "version") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_update_version_set(update, elem->attrs[i+1]);
        }
    }
}

void unfo_elem_reference_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    UNFO_DocRef *ref;
    ref = (UNFO_DocRef*)unfo_object_create(&UNFO_DocRef_ObjInfo, NULL);

    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (strcmp(elem->attrs[i], "href") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_ref_url_set(ref, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "type") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_ref_type_set(ref, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "title") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_ref_title_set(ref, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "id") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_ref_id_set(ref, elem->attrs[i+1]);
        }
    }
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    unfo_objlist_append_x(LASTUPDATE->refs, (UNFO_Object*)ref);
    #undef LASTUPDATE
}

void unfo_elem_coll_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    UNFO_DocColl *coll;
    coll = (UNFO_DocColl*)unfo_object_create(&UNFO_DocColl_ObjInfo, NULL);

    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (strcmp(elem->attrs[i], "short") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_coll_short_set(coll, elem->attrs[i+1]);
        }
    }
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    unfo_objlist_append_x(LASTUPDATE->colls, (UNFO_Object*)coll);
    #undef LASTUPDATE
}

void unfo_elem_sum_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    #define LASTCOLL ((UNFO_DocColl*)LASTUPDATE->colls->last->unfo_obj)
    #define LASTPKG ((UNFO_DocPkg*)LASTCOLL->pkgs->last->unfo_obj)
    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (strcmp(elem->attrs[i], "short") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_sumtype_set(LASTPKG, elem->attrs[i+1]);
        }
    }
    #undef LASTUPDATE
    #undef LASTCOLL
    #undef LASTPKG
}

void unfo_elem_pkg_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    UNFO_DocPkg *pkg;
    pkg = (UNFO_DocPkg*)unfo_object_create(&UNFO_DocPkg_ObjInfo, NULL);

    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (strcmp(elem->attrs[i], "name") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_name_set(pkg, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "version") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_version_set(pkg, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "release") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_release_set(pkg, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "epoch") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_epoch_set(pkg, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "arch") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_arch_set(pkg, elem->attrs[i+1]);
        } else if (strcmp(elem->attrs[i], "source") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_pkg_src_set(pkg, elem->attrs[i+1]);
        }
    }
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    #define LASTCOLL ((UNFO_DocColl*)LASTUPDATE->colls->last->unfo_obj)
    unfo_objlist_append_x(LASTCOLL->pkgs, (UNFO_Object*)pkg);
    #undef LASTCOLL
    #undef LASTUPDATE
}
void unfo_elem_updated_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (strcmp(elem->attrs[i], "date") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_update_updated_set(LASTUPDATE, elem->attrs[i+1]);
        }
    }
    #undef LASTUPDATE
}
void unfo_elem_issued_preproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    for (unsigned int i = 0; i < elem->attrs_len; i += 2) {
        if (strcmp(elem->attrs[i], "date") == 0) {
            if (elem->attrs[i+1])
                unfo_doc_update_issued_set(LASTUPDATE, elem->attrs[i+1]);
        }
    }
    #undef LASTUPDATE
}

void unfo_elem_textval_postproc(UNFO_ParseData *data, UNFO_ParseElem *elem) {
    #define LASTUPDATE ((UNFO_DocUpdate*)data->unfo_doc->updates->last->unfo_obj)
    #define LASTCOLL ((UNFO_DocColl*)LASTUPDATE->colls->last->unfo_obj)
    #define LASTPKG ((UNFO_DocPkg*)LASTCOLL->pkgs->last->unfo_obj)

    char *textval;
    textval = malloc(sizeof(char) * (data->cdata_stack_strlen + 1));
    textval[0] = 0;
    for (UNFO_HSListItem *it = data->cdata_stack->first;
         it != NULL; it = it->next) {
        strcat(textval, (char*)it->data);
    }

    switch (elem->type) {
        case UNFO_ELEM_ID:
            unfo_doc_update_id_set(LASTUPDATE, textval);
        break;
        case UNFO_ELEM_TITLE:
            unfo_doc_update_title_set(LASTUPDATE, textval);
        break;
        /*case UNFO_ELEM_ISSUED:
            unfo_doc_update_issued_set(LASTUPDATE, textval);
        break;
        case UNFO_ELEM_UPDATED:
            unfo_doc_update_updated_set(LASTUPDATE, textval);
        break;*/
        case UNFO_ELEM_RIGHTS:
            unfo_doc_update_rights_set(LASTUPDATE, textval);
        break;
        case UNFO_ELEM_SUMMARY:
            unfo_doc_update_summary_set(LASTUPDATE, textval);
        break;
        case UNFO_ELEM_DESCRIPTION:
            unfo_doc_update_description_set(LASTUPDATE, textval);
        break;
        case UNFO_ELEM_SOLUTION:
            unfo_doc_update_solution_set(LASTUPDATE, textval);
        break;
        case UNFO_ELEM_NAME:
            unfo_doc_coll_name_set(LASTCOLL, textval);
        break;
        case UNFO_ELEM_FILENAME:
            unfo_doc_pkg_filename_set(LASTPKG, textval);
        break;
        case UNFO_ELEM_SUM:
            unfo_doc_pkg_sum_set(LASTPKG, textval);
        break;
        default:
        break;
    }
    #undef LASTUPDATE
    #undef LASTCOLL
    free(textval);
}
