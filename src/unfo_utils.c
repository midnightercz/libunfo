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
