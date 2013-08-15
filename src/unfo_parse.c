#include "h/unfo_parse.h"
#include <errno.h>

UNFO_ParseData* unfo_parse_data_create(char *encoding) {
    UNFO_ParseData *ret;

    ret = malloc(sizeof(UNFO_ParseData));
    UNFO_Check_NULL(ret, NULL)

    ret->log = (UNFO_Log*) unfo_object_create(&UNFO_Log_ObjInfo, NULL);
    ret->parser = XML_ParserCreate((const XML_Char*) encoding);
    ret->elem_stack = unfo_hslist_create();
    unfo_hslist_init(ret->elem_stack, NULL, NULL, &unfo_parse_elem_destroy);
    ret->unfo_doc = (UNFO_Doc*)unfo_object_create(&UNFO_Doc_ObjInfo, NULL);
    ret->cdata_stack = unfo_hslist_create();
    unfo_hslist_init(ret->cdata_stack, NULL, NULL, &free);
    ret->cdata_stack_strlen = 0;

    XML_SetElementHandler(ret->parser,
                          &unfo_parse_start_elem_handler,
                          &unfo_parse_end_elem_handler);
    XML_SetCharacterDataHandler(ret->parser,
                          &unfo_parse_cdata_handler);
    XML_SetUserData(ret->parser, ret);
    return ret;
}

void unfo_parse_data_destroy(UNFO_ParseData* parse_data) {

    unfo_hslist_destroy(&parse_data->elem_stack);
    unfo_hslist_destroy(&parse_data->cdata_stack);
    unfo_object_destroy((UNFO_Object*)parse_data->log);
    unfo_object_destroy((UNFO_Object*)parse_data->unfo_doc);
    XML_ParserFree(parse_data->parser);
    free(parse_data);
}

#if ZLIB_SUPPORT == YES
signed char unfo_parse_gzfile(char *filename,
                            char *encoding, UNFO_ParseData* parsed) {
    void *buffer;
    int readed;
    signed char result = 1;
    gzFile f = gzopen(filename, "r");

    for (;;) {
        buffer = XML_GetBuffer(parsed->parser, 1024);
        if (buffer == NULL) {
            unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_FERROR, 1,
                             unfo_num(errno));
            return -1;
        }
        readed = gzread(f, buffer, sizeof(char)*1024);
        if (readed < 0) {
            unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_FREAD, 0);
            return -1;
        }
        if (!XML_ParseBuffer(parsed->parser, readed, readed == 0)) {
            unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_PARSER, 3,
                 unfo_str(XML_ErrorString(XML_GetErrorCode(parsed->parser))),
                 unfo_num(XML_GetCurrentLineNumber(parsed->parser)),
                 unfo_num(XML_GetCurrentColumnNumber(parsed->parser)));
            result = -1;
        }
        if (readed == 0) {
            break;
        }
    }
    gzclose(f);
    return result;
}
#endif

signed char unfo_parse_file(char *filename,
                            char *encoding, UNFO_ParseData* parsed) {
    void *buffer;
    int readed;
    signed char result = 1;
    FILE *f = fopen(filename, "r");

    if (ferror(f)) {
        unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_FERROR, 1, unfo_num(errno));
    }

    for (;;) {
        buffer = XML_GetBuffer(parsed->parser, 1024);
        if (buffer == NULL) {
            unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_FERROR, 0);
            return -1;
        }
        readed = fread(buffer, sizeof(char), 1024, f);
        if (readed < 0) {
            unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_FREAD, 0);
            return -1;
        }
        if (!XML_ParseBuffer(parsed->parser, readed, readed == 0)) {
            unfo_log_error_x(parsed->log, UNFO_LOG_PARSE_PARSER, 3,
                 unfo_str(XML_ErrorString(XML_GetErrorCode(parsed->parser))),
                 unfo_num(XML_GetCurrentLineNumber(parsed->parser)),
                 unfo_num(XML_GetCurrentColumnNumber(parsed->parser)));
            result = -1;
        }
        if (readed == 0) {
            break;
        }
    }
    fclose(f);
    return result;
}

signed char unfo_parse_str(char *str) {
    (void)str;
}

void unfo_parse_check_attributes(UNFO_ParseData *parse_data,
                                 UNFO_ParseElem *elem,
                                 const XML_Char **attrs) {
    int process, attrindex, i;
    const UNFO_ElemAttrInfo *current;
    UNFO_Str *str1, *str2;
    UNFO_Num *num1, *num2;
    const XML_Char *tmp;

    #define parser_line XML_GetCurrentLineNumber(parse_data->parser)
    #define parser_col XML_GetCurrentColumnNumber(parse_data->parser)
    #define attributes UNFO_ElemInfos[elem->type]->attributes

    process = 0;

    for (i=0; attrs[i]; i++);
    char processed2[i/2];
    for (i=0; attrs[i]; i++) {
        processed2[i] = 0;
    }

    for (i=0; attributes[i] != NULL; i++);
    char processed[i];
    for (i=0; attributes[i] != NULL; i++) {
        processed[i] = 0;
    }

    //memset(processed, 0, sizeof(char) * i);
    elem->attrs = malloc(sizeof(char*) * i);
    elem->attrs_len = i;

    if (attributes[0] != NULL) {
        process = 1;
    }
    str1 = unfo_str(UNFO_ElemInfos[elem->type]->name);
    num1 = unfo_num(parser_line);
    num2 = unfo_num(parser_col);

    attrindex = 0;
    while (process) {
        process = 0;
        for (i=0, current = attributes[0]; current != NULL;
             i++, current = attributes[i]) {
            if (!processed[i]) {
                if (strcmp(current->name, attrs[attrindex]) == 0) {
                    elem->attrs[i] = current->name;
                    processed[i] = 1;
                    processed2[attrindex] = 1;
                    if (current->val_check &&
                        !current->val_check(attrs[attrindex+1])) {

                        str2 = unfo_str(current->name);
                        unfo_log_error(parse_data->log,
                                         UNFO_LOG_ATTR_VALERROR, 4,
                                         str1, str2, num1, num2);
                        unfo_object_destroy((UNFO_Object*)str2);
                        elem->attrs[i] = NULL;
                    } else {
                        elem->attrs[i] = attrs[attrindex+1];
                    }
                }
                process = 1;
            }
        }
        attrindex += 2;
        if (attrs[attrindex] == NULL) break;
    }
    for (i=0, current = attributes[0]; current != NULL;
         i++, current = attributes[i]) {
        if (!processed[i]) {
            str2 = unfo_str(current->name);
            unfo_log_warning(parse_data->log, UNFO_LOG_ATTR_MISSING,
                             4, str1, str2, num1, num2);
            unfo_object_destroy((UNFO_Object*)str2);
        }
    }
    for (i=0, tmp = attrs[0]; current != NULL; current++, i++) {
        if (!processed2[i]) {
            str2 = unfo_str(current->name);
            unfo_log_warning(parse_data->log, UNFO_LOG_ATTR_UNKNOWN,
                             4, str1, str2, num1, num2);
            unfo_object_destroy((UNFO_Object*)str2);
        }
    }
    unfo_object_destroy((UNFO_Object*)str1);
    unfo_object_destroy((UNFO_Object*)num1);
    unfo_object_destroy((UNFO_Object*)num2);
    #undef parser_line
    #undef parser_col
    #undef attributes
}

void unfo_parse_start_elem_handler(void *userData, const XML_Char *s,
                                   const XML_Char **attrs) {

    #define PARSEDATA ((UNFO_ParseData*)userData)
    #define LAST PARSEDATA->elem_stack->last
    #define LASTELEM ((UNFO_ParseElem*)LAST->data)
    #define ELEMINFO  UNFO_ElemInfos[elem->type]
    #define parser_line XML_GetCurrentLineNumber(PARSEDATA->parser)
    #define parser_col XML_GetCurrentColumnNumber(PARSEDATA->parser)

    UNFO_ParseElem *elem;
    elem = unfo_parse_elem_create(s, attrs);

    if (LAST)
        printf("start elem %s\n", s);
    //UNFO_ElemInfos[elem->type];
    if (ELEMINFO->ancestor != UNFO_ELEM_NONE) {
        UNFO_Str *str1, *str2 = NULL, *str3;
        UNFO_Num *num1, *num2;
        str1 = unfo_str((const char*)s);
        str3 = unfo_str((const char*)UNFO_ElemInfos[ELEMINFO->ancestor]->name);
        num1 = unfo_num(parser_line);
        num2 = unfo_num(parser_line);
        if (LAST && LASTELEM->type != ELEMINFO->ancestor) {
            str2 = unfo_str(UNFO_ElemInfos[LASTELEM->type]->name);
            unfo_log_warning(PARSEDATA->log, UNFO_LOG_WRONG_PARENT, 5,
                             str1, str2, str3, num1, num2);
        } else if (!LAST) {
            str2 = unfo_str("-No element-");
            unfo_log_warning(PARSEDATA->log, UNFO_LOG_WRONG_PARENT, 5,
                             str1, str2, str3, num1, num2);
        }
        unfo_object_destroy((UNFO_Object*)str1);
        unfo_object_destroy((UNFO_Object*)str2);
        unfo_object_destroy((UNFO_Object*)str3);
        unfo_object_destroy((UNFO_Object*)num1);
        unfo_object_destroy((UNFO_Object*)num2);
    }
    if (ELEMINFO->attributes) {
       unfo_parse_check_attributes(PARSEDATA, elem, attrs);
    }

    unfo_hslist_append(PARSEDATA->elem_stack, elem, 0);
    if (ELEMINFO->preproc) {
        ELEMINFO->preproc(PARSEDATA, elem);
    } else {
 
    }
    #undef PARSEDATA
    #undef LAST
    #undef LASTELEM
    #undef ELEMINFO
    #undef parser_line
    #undef parser_col
}

void unfo_parse_cdata_handler(void *userData, const XML_Char *s, int len) {
    char *str;
    if (__unfo_iswhitespace(s, len)) {
        return;
    }
    str = malloc(sizeof(char) * (len+1));
    str = memcpy(str, s, sizeof(char) * len);
    str[len] = 0;
    unfo_hslist_append(((UNFO_ParseData*)userData)->cdata_stack, str, 0);
    ((UNFO_ParseData*)userData)->cdata_stack_strlen += len;
}

void unfo_parse_end_elem_handler(void *userData, const XML_Char *s) {
    (void)userData;
    UNFO_ParseElem *elem;
    UNFO_HSListItem *it;
    #define LAST (((UNFO_ParseData*)userData)->elem_stack->last)

    UNFO_ParseElemType type = unfo_elem_get_type(s);
    elem = (UNFO_ParseElem*)LAST->data;
    it = LAST;
    unfo_hslist_remove(((UNFO_ParseData*)userData)->elem_stack, it);

    if (UNFO_ElemInfos[type]->postproc) {
        UNFO_ElemInfos[type]->postproc((UNFO_ParseData*)userData, elem);
    }
    unfo_parse_elem_destroy(it->data);
    free(it);
    
    unfo_hslist_clear(((UNFO_ParseData*)userData)->cdata_stack);
    ((UNFO_ParseData*)userData)->cdata_stack_strlen = 0;

    #undef LAST
}



UNFO_ParseElem* unfo_parse_elem_create(const char *name, const char **attrs) {
    UNFO_ParseElem *ret;
    ret = malloc(sizeof(UNFO_ParseElem));
    ret->name = (char*)name;
    ret->attrs = attrs;
    ret->type = unfo_elem_get_type(name);
    return ret;
}

void unfo_parse_elem_destroy(void *elem) {
    free(((UNFO_ParseElem*)elem)->attrs);
    free(elem);
}

