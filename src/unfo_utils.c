#include "h/unfo_utils.h"

void* __unfo_str_clone(void *str) {
    void *ret;
    ret = malloc(sizeof(char) * (strlen((char*)str)+1));
    memcpy(ret, str, sizeof(char) * (strlen((char*)str)+1));
    return ret;
}

inline char __unfo_iswhitespace(const char *str, int len) {
    for (int x = 0; x < len; x++) {
        if (!isspace(str[x])) return 0;
    }
    return 1;
}

int __unfo_strcmp(const char *str1, const char *str2) {
    if (!str1 && !str2)
        return 1;
    else if (!str1 || !str2)
        return 0;
    else
        return strcmp(str1, str2) == 0;
}
