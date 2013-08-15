#ifndef UNFO_PARSE_H
#define UNFO_PARSE_H

#include <expat.h>

#if ZLIB_SUPPORT == YES
    #include <zlib.h>
#endif

#include "unfo_types.h"
#include "unfo_log.h"
#include "unfo_doc.h"
#include "unfo_elems.h"

UNFO_ParseData* unfo_parse_data_create(char *encoding);
void unfo_parse_data_destroy(UNFO_ParseData* parse_data);


UNFO_ParseElem* unfo_parse_elem_create(const char *name, const char **attrs);
void unfo_parse_elem_destroy(void *elem);

signed char unfo_parse_file(char *filename,
                            char *encoding, UNFO_ParseData *parsed);
#if ZLIB_SUPPORT == YES
signed char unfo_parse_gzfile(char *filename,
                            char *encoding, UNFO_ParseData *parsed);
#endif

void unfo_parse_start_elem_handler(void *userData, const XML_Char *s,
                                   const XML_Char **attrs);
void unfo_parse_cdata_handler(void *userData, const XML_Char *s, int len);
void unfo_parse_end_elem_handler(void *userData, const XML_Char *s);



#endif
