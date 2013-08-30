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

char *attrs2str(UNFO_RTree *attrs, const char *kwds[], int kwds_len) {
    int total_len = 0;
    int len, i;
    char *tmp, *ret;
    char *vals[kwds_len];

    const int streqlen = strlen("='', ");
    if (!attrs)
        return "";
    for (i=0; i < kwds_len-1; i++) {
        len = streqlen;
        len += strlen(kwds[i]);
        len += (tmp=unfo_rtree_get(attrs, kwds[i]))?strlen(tmp):0;
        total_len += len;

        vals[i] = malloc(sizeof(char) * (len+1));
        if (tmp)
            sprintf(vals[i], "%s='%s', ", kwds[i], tmp);
        else
            sprintf(vals[i], "%s='', ", kwds[i]);
    }
    len = streqlen;
    len += strlen(kwds[i]);
    len += (tmp=unfo_rtree_get(attrs, kwds[i]))?strlen(tmp):0;
    total_len += len;

    vals[i] = malloc(sizeof(char) * (len+1));
    if (tmp)
        sprintf(vals[i], "%s='%s'", kwds[i], tmp);
    else
        sprintf(vals[i], "%s=''", kwds[i]);

    ret = malloc((total_len + 1) * sizeof(char));
    ret[0]=0;
    for (int i=0; i < kwds_len; i++) {
        ret = strcat(ret, vals[i]);
        free(vals[i]);
    }
    return ret;
}
