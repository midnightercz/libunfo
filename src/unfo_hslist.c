/* libunfo - C alternative to yum.unfo library
 * Copyright (C) 2013 Jindrich Luza
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to  Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA
 */

#include "h/unfo_hslist.h"

#include <stdlib.h>
UNFO_HSList * unfo_hslist_create() {
    UNFO_HSList *ret;
    ret =  malloc(sizeof(UNFO_HSList));
    if (!ret) {
        return NULL;
    }
    return ret;
}

void unfo_hslist_init(UNFO_HSList * hslist,
                            void*(*data_constructor)(void* data),
                            void*(*data_cloner)(void* data),
                            void(*data_destructor)(void* data)) {
    if (hslist == NULL) {
        return;
    }
    hslist->data_constructor = data_constructor;
    hslist->data_destructor = data_destructor;
    hslist->data_cloner = data_cloner;
    hslist->first = NULL;
    hslist->last = NULL;
}

void unfo_hslist_append(UNFO_HSList * hslist, void * data, unsigned construct) {
    UNFO_HSListItem * it;
    void * ndata;

    if (hslist == NULL)
        return;
    if ((it = malloc(sizeof(*it))) == NULL)
        return;
    if (construct && hslist->data_constructor) {
        ndata = hslist->data_constructor(data);
    } else {
        ndata = data;
    }
    it->data = ndata;
    it->next = NULL;
    if (hslist->last == NULL) {
        hslist->last = it;
        hslist->first = it;
    } else {
        hslist->last->next = it;
        hslist->last = hslist->last->next;
    }
}

inline void unfo_hslist_destroy_v(void ** hslist) {
    unfo_hslist_destroy((UNFO_HSList**) hslist);
}

void unfo_hslist_destroy(UNFO_HSList ** hslist) {
    UNFO_HSListItem *it,*oldit;
    unsigned int x;
    if (*hslist == NULL) return;
    oldit = (*hslist)->first;
    it = (oldit)?oldit->next:NULL;
    for (x=0 ;it != NULL; it=it->next, x++) {
        if ((*hslist)->data_destructor != NULL)
            (*hslist)->data_destructor(oldit->data);
        free(oldit);
        oldit = it;
    }
    if (oldit) {
        if ((*hslist)->data_destructor != NULL)
            (*hslist)->data_destructor(oldit->data);
        free(oldit);
    }
    free(*hslist);
    *hslist = NULL;
}

void unfo_hslist_remove(UNFO_HSList * hslist,
                              UNFO_HSListItem * it) {
    UNFO_HSListItem *itx, *itprev=NULL;
    for (itx = hslist->first; itx != NULL && itx != it; itx = itx->next) {
        itprev = itx;
    }
    if (itx != it)
        return;
    if (itprev == NULL) {
        if (hslist->first == hslist->last)
            hslist->last = hslist->first->next;
        hslist->first = hslist->first->next;
    } else {
        itprev->next = it->next;
        if (it == hslist->last) {
            if (hslist->first == hslist->last)
                hslist->first = itprev;
            hslist->last = itprev;
        }
    }
}

void* unfo_hslist_data_at(UNFO_HSList * hlist, unsigned int index)
{
    unsigned int i=0;
    UNFO_HSListItem * itx;
    for (itx = hlist->first; itx != NULL && index != i; itx = itx->next, i++);
    if (itx == NULL)
        return itx;
    else
        return itx->data;
}

UNFO_HSList* unfo_hslist_clone(UNFO_HSList * hslist) {
    UNFO_HSList *ret;
    UNFO_HSListItem *it;

    ret = unfo_hslist_create();
    unfo_hslist_init(ret, hslist->data_constructor,
                           hslist->data_cloner,
                           hslist->data_destructor);
    for (it = hslist->first; it != NULL; it = it->next) {
        unfo_hslist_append(ret, hslist->data_cloner(it->data), 0);
    }
    return ret;
}

void unfo_hslist_clear(UNFO_HSList * hslist) {
    UNFO_HSListItem *it,*oldit;
    if (hslist == NULL) return;
    oldit = hslist->first;
    it = (oldit)?oldit->next:NULL;
    for (;it != NULL; it=it->next) {
        if (hslist->data_destructor != NULL)
            hslist->data_destructor(oldit->data);
        free(oldit);
        oldit = it;
    }
    if (oldit) {
        if (hslist->data_destructor != NULL)
            hslist->data_destructor(oldit->data);
        free(oldit);
    }
    hslist->first = NULL;
    hslist->last = NULL;
}

unsigned unfo_hslist_values_equal(UNFO_HSList *hlist1, UNFO_HSList *hlist2,
                                   char (*cmpf)(void*, void*)) {
    UNFO_HSListItem *it, *it2;
    for (it = hlist1->first, it2 = hlist2->first; it != NULL && it2 != NULL;
        it = it->next, it2 = it2->next) {
        if (!cmpf(it->data, it2->data))
            return 0;
    }
    if (it != NULL || it2 != NULL)
        return 0;
    return 1;
}
