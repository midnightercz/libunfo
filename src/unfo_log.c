#include "h/unfo_log.h"

const char * UNFO_LogCodeFormat[] = {
                [LOG_TEST_CODE1] = "log message at line:%s col:%s",
                [LOG_TEST_CODE2] = "log message '%s' at line:%s col:%s",
                [LOG_TEST_CODE3] = "noarg log message",
                [LOG_TEST_CODE4] = "log message '%s'",
                [LOG_TEST_CODE5] = "log message %s at line:%s col:%s with code:%s",
                [LOG_TEST_CODE6] = "noarg log message",
                [UNFO_LOG_WRONG_PARENT] = "Element %s has wrong parent %s "
                                          "(should has %s) at line:%s column:%s",
                [UNFO_LOG_ATTR_UNKNOWN] = "Unkown attribute %s within element %s"
                                          " at line:%s column:%s",
                [UNFO_LOG_ATTR_MISSING] = "Element %s attribute %s missing "
                                          "at line:%s column:%s",
                [UNFO_LOG_PARSE_FERROR] = "Couldn't parse file. File error: %s",
                [UNFO_LOG_PARSE_FREAD] = "Couldn't parse file. Couldn't read file",
                [UNFO_LOG_PARSE_ALLOC] = "Couldn't allocate buffer for parsing",
                [UNFO_LOG_PARSE_PARSER] = "Couldn't parse. Parser problem:%s"
                                          "at line:%s column:%s",
                [UNFO_LOG_XMLGEN] = "Cannot generate xml",
                [UNFO_LOG_WRITEF] = "Can't write to file %s"
                    };

void unfo_log_create(UNFO_Log *log, UNFO_Object **args){
    (void)args;

    log->entries = unfo_hslist_create();
    unfo_hslist_init(log->entries, NULL, NULL, unfo_log_entry_destroy);
}
UNFO_CREATE_u(log, UNFO_Log)

void unfo_log_destroy(UNFO_Log *log) {
    unfo_hslist_destroy(&log->entries);
}
UNFO_DESTROY_u(log, UNFO_Log)


UNFO_LogEntry* unfo_log_entry_create() {
    UNFO_LogEntry *ret;
    ret = malloc(sizeof(UNFO_LogEntry));
    UNFO_Check_NULL(ret, NULL)
    ret->args = NULL;
    return ret;
}

void unfo_log_entry_destroy(UNFO_LogEntry *log_entry) {
    for (int i=0; i<log_entry->arg_count; i++) {
        unfo_object_destroy(log_entry->args[i]);
    }
    free(log_entry->args);
    free(log_entry);
}

inline static UNFO_LogEntry * __unfo_log_entry_prep(int code, int type, int n){
    UNFO_LogEntry *entry;

    entry = unfo_log_entry_create();

    entry->args = malloc(sizeof(UNFO_Object*) * n);
    entry->arg_count = n;
    entry->code = code;
    entry->type = type;
    return entry;
}

static void __unfo_log_entry(UNFO_Log *log, int code, int type, int n,
                             va_list va){
    UNFO_LogEntry *entry;
    UNFO_Object *val;

    entry = __unfo_log_entry_prep(code, type, n);

    for (int i=0; i<n; i++) {
        val = va_arg(va, UNFO_Object*);
        entry->args[i] = unfo_object_copy(val);
    }
    unfo_hslist_append(log->entries, entry, 0);
}

static void __unfo_log_entry_x(UNFO_Log *log, int code, int type, int n,
                             va_list va){
    UNFO_LogEntry *entry;
    UNFO_Object *val;

    entry = __unfo_log_entry_prep(code, type, n);

    for (int i=0; i<n; i++) {
        val = va_arg(va, UNFO_Object*);
        entry->args[i] = val;
    }
    unfo_hslist_append(log->entries, entry, 0);
}

void unfo_log_error(UNFO_Log *log, int code, int n, ...) {
    va_list list;
    va_start(list, n);
    __unfo_log_entry(log, code, UNFO_LOG_ENTRY_ERR, n, list);
    va_end(list);
}
void unfo_log_error_x(UNFO_Log *log, int code, int n, ...) {
    va_list list;
    va_start(list, n);
    __unfo_log_entry_x(log, code, UNFO_LOG_ENTRY_ERR, n, list);
    va_end(list);
}

void unfo_log_warning(UNFO_Log *log, int code, int n, ...) {
    va_list list;
    va_start(list, n);
    __unfo_log_entry(log, code, UNFO_LOG_ENTRY_WAR, n, list);
    va_end(list);
}
void unfo_log_warning_x(UNFO_Log *log, int code, int n, ...) {
    va_list list;
    va_start(list, n);
    __unfo_log_entry_x(log, code, UNFO_LOG_ENTRY_WAR, n, list);
    va_end(list);
}


static char ** __unfo_log_entry_out(UNFO_LogEntry *log_entry, int *total_len) {
    char **args;
    args = malloc(sizeof(char*) * log_entry->arg_count);
    *total_len = 0;

    for (int i = 0; i < log_entry->arg_count; i++) {
        args[i] = unfo_object_tostr((UNFO_Object*)log_entry->args[i]);
        *total_len += strlen(args[i]);
    }
    return args;
}

char* unfo_log_entry_str(UNFO_LogEntry *log_entry) {
    char **args;
    char *ret;
    int total_len;

    args = __unfo_log_entry_out(log_entry, &total_len);
    ret = malloc(sizeof(char) * (strlen(UNFO_LogCodeFormat[log_entry->code]) +
                                 total_len + 1 - (2*log_entry->arg_count)));
    expand_s(ret, UNFO_LogCodeFormat[log_entry->code],
           args,
           log_entry->arg_count);
    for (int i = 0; i < log_entry->arg_count; i++) {
        free(args[i]);
    }
    free(args);
    return ret;
}

void unfo_log_entry_print(UNFO_LogEntry *log_entry) {
    int total_len;
    char **args;

    args = __unfo_log_entry_out(log_entry, &total_len);
    expand_out(UNFO_LogCodeFormat[log_entry->code],
           args,
           log_entry->arg_count);
    printf("\n");
    for (int i = 0; i < log_entry->arg_count; i++) {
        free(args[i]);
    }
    free(args);
}

void unfo_log_print(UNFO_Log *log) {
    UNFO_HSListItem *hsit;
    for (hsit = log->entries->first; hsit != NULL; hsit = hsit->next) {
        unfo_log_entry_print(hsit->data);
    }
}

UNFO_ObjectInfo UNFO_Log_ObjInfo = {
    .obj_size = sizeof(UNFO_Log),
    .constructor = &unfo_log_create_u,
    .destructor = &unfo_log_destroy_u,
    //.deep_copy = &unfo_log_copy_u
};
