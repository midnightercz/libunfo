/* libunfo
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

#ifndef UNFO_HSLIST_H
#define UNFO_HSLIST_H


struct _UNFO_HSListItem {
    struct _UNFO_HSListItem * next;
    void * data;
};

typedef struct _UNFO_HSListItem UNFO_HSListItem;

typedef struct {
    UNFO_HSListItem * first;
    UNFO_HSListItem * last;
    void(*data_destructor)(void*);
    void*(*data_cloner)(void*);
    void*(*data_constructor)(void*);
} UNFO_HSList;

UNFO_HSList * unfo_hslist_create();
void unfo_hslist_destroy(UNFO_HSList ** hlist);
void unfo_hslist_destroy_v(void ** hlist);

void unfo_hslist_init(UNFO_HSList * hlist,
                       void*(*data_constructor)(void* data),
                       void*(*data_cloner)(void* data),
                       void(*data_destructor)(void* data));
void unfo_hslist_append(UNFO_HSList * hlist, void * data,
                                                        unsigned construct);
void unfo_hslist_remove(UNFO_HSList * hlist, UNFO_HSListItem * it);
void* unfo_hslist_data_at(UNFO_HSList * hlist, unsigned int index);

UNFO_HSList* unfo_hslist_clone(UNFO_HSList * hslist);
void unfo_hslist_clear(UNFO_HSList * hslist);
unsigned unfo_hslist_values_equal(UNFO_HSList *hlist1, UNFO_HSList *hlist2,
                                   char (*cmpf)(void*, void*));
void unfo_hslist_unique(UNFO_HSList *hslist1, char (*cmpf)(void*, void*));

#endif
