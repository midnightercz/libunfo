#ifndef UNFO_MM_H
#define UNFO_MM_H

#include "unfo_utils.h"

#include <stdlib.h>
#include <string.h>


typedef struct {
    size_t ref_count;
    void (*destructor)(void*);
    void *obj;
} UNFO_RefC;

UNFO_RefC* unfo_refc_create(void *obj, void (*destructor)(void*));
void unfo_refc_destroy(UNFO_RefC *refc);
void unfo_refc_destroy_v(void *refc);
void unfo_refc_decref(UNFO_RefC *refc);
void unfo_refc_incref(UNFO_RefC *refc);

#endif //UNFO_MM_H
