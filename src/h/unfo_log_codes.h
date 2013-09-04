#ifndef UNFO_LOG_CODES_H
#define UNFO_LOG_CODES_H

#include <stdio.h>
#include <stdarg.h>

#include "unfo_obj.h"
#include "unfo_utils.h"

#define UNFO_LOG_ENTRY_ERR          0
#define UNFO_LOG_ENTRY_WAR          1
#define UNFO_LOG_WRONG_PARENT       2
#define UNFO_LOG_ATTR_UNKNOWN       3
#define UNFO_LOG_ATTR_MISSING       4
#define UNFO_LOG_ATTR_VALERROR      5
#define UNFO_LOG_PARSE_FERROR       6
#define UNFO_LOG_PARSE_ALLOC        7
#define UNFO_LOG_PARSE_PARSER       8
#define UNFO_LOG_PARSE_FREAD        9
#define UNFO_LOG_XMLGEN             10
#define UNFO_LOG_WRITEF             11
#define UNFO_LOG_PARSE_FOPEN        12
#define UNFO_LOG_ELEM_UNKNOWN        13

#define LOG_TEST_CODE1              1001
#define LOG_TEST_CODE2              1002
#define LOG_TEST_CODE3              1003
#define LOG_TEST_CODE4              1004
#define LOG_TEST_CODE5              1005
#define LOG_TEST_CODE6              1006



void __expand(char *str, const char *fmt, char out, ...);

inline void expand1(char *str, const char *fmt, char **args, char out) {
    __expand(str, fmt, out, args[0]);
}
inline void expand2(char *str, const char *fmt, char **args, char out) {
    __expand(str, fmt, out, args[0],
                          args[1]);
}
inline void expand3(char *str, const char *fmt, char **args, char out) {
    __expand(str, fmt, out, args[0],
                           args[1],
                           args[2]);
}
inline void expand4(char *str, const char *fmt, char **args, char out) {
    __expand(str, fmt, out, args[0],
                           args[1],
                           args[2],
                           args[3]);
}
inline void expand5(char *str, const char *fmt, char **args, char out) {
    __expand(str, fmt, out, args[0],
                           args[1],
                           args[2],
                           args[3],
                           args[4]);
}

void expand(char *str, const char *fmt, char **args, int len, int out);

inline void expand_out(const char *fmt, char **args, int len) {
    expand(NULL, fmt, args, len, 1);
}
inline void expand_s(char *str, const char *fmt, char **args, int len) {
    expand(str, fmt, args, len, 0);
}

#endif
