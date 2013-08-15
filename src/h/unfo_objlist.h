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

/*! \file unfo_list.h
 * \brief A Documented file.
 * Details.
 * */
#ifndef UNFO_LIST_H
#define UNFO_LIST_H

#include "unfo_obj.h"

#include <string.h>
#include <stdlib.h>

typedef struct UNFO_ObjListIt UNFO_ObjListIt;

struct UNFO_ObjListIt {
    UNFO_Object *unfo_obj;
    UNFO_ObjListIt *next;
} UnfoObjListIt;

typedef struct UNFO_ObjList {
    UNFO_Object_HEAD
    UNFO_ObjListIt *first;
    UNFO_ObjListIt *last;
    size_t len;
} UNFO_ObjList;


void unfo_objlist_create(UNFO_ObjList *objlist, UNFO_Object **args);
void unfo_objlist_create_u(UNFO_Object *uobj, UNFO_Object **args);
void unfo_objlist_destroy(UNFO_ObjList *objlist);
void unfo_objlist_destroy_u(UNFO_Object *objlist);


const UNFO_ObjListIt *unfo_objlist_it_next(const UNFO_ObjListIt *it);

int unfo_objlist_walk(UNFO_ObjListIt **walker, UNFO_Object **result);
int unfo_objlist_walk_r(UNFO_ObjListIt *walker_start,
                            UNFO_ObjListIt *mantinel,
                            UNFO_Object **result);


int unfo_objlist_append_x(UNFO_ObjList *objlist, UNFO_Object *obj);
int unfo_objlist_append(UNFO_ObjList *objlist, UNFO_Object *obj);
UNFO_Object* unfo_objlist_get(UNFO_ObjList *objlist, unsigned int atpos);
int unfo_objlist_insert_at(UNFO_ObjList *objlist,
                           unsigned int pos,
                           UNFO_Object *obj);
UNFO_ObjList* unfo_objlist_sublist_it(UNFO_ObjListIt *startit,
                                      UNFO_ObjListIt *end);
UNFO_ObjList* unfo_objlist_filter(UNFO_ObjList *list,
                                  char (*filter_func)(UNFO_Object*));

extern UNFO_ObjectInfo UNFO_ObjList_ObjInfo;

#endif
