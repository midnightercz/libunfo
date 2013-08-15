#ifndef UNFO_LOG_H
#define UNFO_LOG_H

#include <stdarg.h>

#include "unfo_log_codes.h"
#include "unfo_types.h"

void unfo_log_create(UNFO_Log *log, UNFO_Object **args);
void unfo_log_create_u(UNFO_Object *log, UNFO_Object **args);

void unfo_log_destroy(UNFO_Log *log);
void unfo_log_destroy_u(UNFO_Object *log);

UNFO_LogEntry *unfo_log_entry_create();
void unfo_log_entry_destroy();


void unfo_log_error(UNFO_Log *log, int code, int n, ...);
void unfo_log_error_x(UNFO_Log *log, int code, int n, ...);
void unfo_log_warning(UNFO_Log *log, int code, int n, ...);
void unfo_log_warning_x(UNFO_Log *log, int code, int n, ...);
void unfo_log_print(UNFO_Log *log);

extern const char * UNFO_LogCodeFormat[];
extern UNFO_ObjectInfo UNFO_Log_ObjInfo;

#endif

