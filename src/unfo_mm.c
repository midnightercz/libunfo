#include "h/unfo_mm.h"

UNFO_RefC* unfo_refc_create(void *obj, void (*destructor)(void*)) {
    UNFO_RefC *refc;
    refc = malloc(sizeof(*refc));
    if (!refc) {
        // TOTO: MALLOC_FAIL
        return NULL;
    }
    refc->ref_count = 0;
    refc->obj = obj;
    refc->destructor = destructor;
    return refc;
}

void unfo_refc_destroy(UNFO_RefC *refc) {
    UNFO_Check_NULL(refc, )
    if (!refc->ref_count) {
        refc->destructor(refc->obj);
        free(refc);
    } else {
        refc->ref_count--;
    }
}

inline void unfo_refc_destroy_v(void *refc) {
    unfo_refc_destroy((UNFO_RefC*)refc);
}

inline void unfo_refc_decref(UNFO_RefC *refc) {
    unfo_refc_destroy(refc);
}

inline void unfo_refc_incref(UNFO_RefC *refc) {
    UNFO_Check_NULL(refc, )
    refc->ref_count++;
}
