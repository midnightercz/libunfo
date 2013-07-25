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

#ifndef UNFO_RADIX_H
#define UNFO_RADIX_H

#include <stdlib.h>
#include <string.h>
#include "unfo_hslist.h"

typedef struct {
    char * key;
    unsigned is_leaf;
    UNFO_HSList * subnodes;
    void * data;
    void (**data_destructor)(void*);
} UNFO_RTreeData;

typedef struct {
    UNFO_HSList *  subnodes;
    void* (*data_constructor)(void*);
    void* (*data_cloner)(void*);
    void (*data_destructor)(void*);
} UNFO_RTree;

typedef struct {
    char * key;
    void * data;
} UNFO_RTreePair;

UNFO_RTreeData * __unfo_rtree_data_create(UNFO_RTree *rt, char *key,
                                                   unsigned int keylen,
                                                   void *data);
UNFO_HSList* __unfo_rtree_all(UNFO_RTree * rt, char pairorkey);

void unfo_rtree_data_destroy(UNFO_RTreeData * rtd);
void unfo_rtree_data_destroy_v(void * rtd);

UNFO_RTreeData * unfo_rtree_data_create(UNFO_RTree *rt, char * key,
                                          void * data);
UNFO_RTreeData * unfo_rtree_data_create_n(UNFO_RTree *rt, char * key,
                                            unsigned int len,
                                            void * data);

UNFO_RTree * unfo_rtree_create(void* (*data_constructor)(void*),
                                 void* (*data_cloner)(void*),
                                 void (*data_destructor)(void*));
void unfo_rtree_destroy(UNFO_RTree * rt);

void unfo_rtree_set(UNFO_RTree *rt, char *key, void *data);
void unfo_rtree_set_n(UNFO_RTree *rt, char *key, unsigned int len,
                       void *data);

void* unfo_rtree_get(UNFO_RTree * rt, const char * key);
void unfo_rtree_unset(UNFO_RTree * rt, const char * key);
void unfo_rtree_clear(UNFO_RTree * rt);

void unfo_rtree_values_walk(UNFO_RTree *rt, void* udata,
                                               void (*walk_f)(void*, void*));
UNFO_HSList * unfo_rtree_values(UNFO_RTree *rt);
UNFO_HSList* unfo_rtree_keys(UNFO_RTree * rt);
UNFO_HSList* unfo_rtree_pairs(UNFO_RTree * rt);
UNFO_RTree * unfo_rtree_clone(UNFO_RTree * rt);
UNFO_RTree* unfo_rtree_union(UNFO_RTree *rt1, UNFO_RTree *rt2);
void unfo_rtree_unite(UNFO_RTree *rt1, UNFO_RTree *rt2);
UNFO_RTree* unfo_rtree_union(UNFO_RTree *rt1, UNFO_RTree *rt2);

UNFO_RTreePair * unfo_rtree_pair_create(char * key, void * data,
                                          void (*data_destructor(void*)));
void unfo_rtree_pair_destroy(UNFO_RTreePair * pair);
void unfo_rtree_pair_destroy_v(void * pair);

#endif
