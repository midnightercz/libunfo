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

#include "h/unfo_dict.h"
#include <stdio.h>

void unfo_rtree_data_destroy(UNFO_RTreeData * rtd) {
    free(rtd->key);
    if ((rtd->data) && (*rtd->data_destructor))
        (*rtd->data_destructor)(rtd->data);
    unfo_hslist_destroy(&rtd->subnodes);
    free(rtd);
}

inline void unfo_rtree_data_destroy_v(void * rtd) {
    unfo_rtree_data_destroy((UNFO_RTreeData*)rtd);
}

inline UNFO_RTreeData * __unfo_rtree_data_create(UNFO_RTree *rt, char *key,
                                                   unsigned int keylen,
                                                   void *data){
    UNFO_RTreeData * rtd;
    if ((rtd = malloc(sizeof(*rtd))) == NULL)
        return NULL;
    if ((rtd->key = malloc(sizeof(char) * (keylen+1))) == NULL) {
        free(rtd);
        return NULL;
    }
    memcpy(rtd->key, key, sizeof(char)*keylen);
    rtd->key[keylen] = 0;
    rtd->data = data;
    if (data != NULL) {
        rtd->is_leaf = 1;
    }
    rtd->data_destructor = &rt->data_destructor;
    rtd->subnodes = unfo_hslist_create();
    unfo_hslist_init(rtd->subnodes, NULL, NULL, &unfo_rtree_data_destroy_v);
    return rtd;
}

UNFO_RTreeData * unfo_rtree_data_create(UNFO_RTree *rt,char * key,
                                          void * data) {
    UNFO_RTreeData * rtd;
    rtd = __unfo_rtree_data_create(rt, key, strlen(key), data);
    return rtd;
}

UNFO_RTreeData * unfo_rtree_data_create_n(UNFO_RTree *rt, char * key,
                                            unsigned keylen, void * data) {
    UNFO_RTreeData * rtd;
    rtd = __unfo_rtree_data_create(rt, key, keylen, data);
    return rtd;
}

UNFO_RTree * unfo_rtree_create(void* (*data_constructor)(void*),
                                 void* (*data_cloner)(void*),
                                 void (*data_destructor)(void*)) {
    UNFO_RTree *ret;
    if ((ret = malloc(sizeof(UNFO_RTree))) == NULL)
        return NULL;
    ret->subnodes = unfo_hslist_create();
    unfo_hslist_init(ret->subnodes, NULL, NULL, &unfo_rtree_data_destroy_v);
    if (ret->subnodes == NULL) {
        free(ret);
        return NULL;
    }
    ret->data_constructor = data_constructor;
    ret->data_cloner = data_cloner;
    ret->data_destructor = data_destructor;
    return ret;
}

void unfo_rtree_destroy(UNFO_RTree * rt) {
    if (!rt) return;
    unfo_hslist_destroy(&(rt->subnodes));
    free(rt);
}

void unfo_rtree_print(UNFO_HSList * hl, unsigned  deep) {
    UNFO_HSListItem * it;
    for (it = hl->first; it != NULL; it=it->next) {
        printf("%d %s\n",deep, (((UNFO_RTreeData*)it->data)->key));
        unfo_rtree_print(((UNFO_RTreeData*)it->data)->subnodes, deep+1);
    }
}

UNFO_HSList * unfo_rtree_values(UNFO_RTree * rt) {
    UNFO_HSList *ret, *tmplist, *tmp_subnodes;
    UNFO_HSListItem *it, *firstit;
    ret = unfo_hslist_create();
    unfo_hslist_init(ret, NULL, NULL, NULL);
    tmplist = unfo_hslist_create();
    unfo_hslist_init(tmplist, NULL, NULL, NULL);
    unfo_hslist_append(tmplist, rt->subnodes, 0);
    while (tmplist->first != NULL) {
        it = tmplist->first;
        firstit = it;
        unfo_hslist_remove(tmplist, firstit);
        tmp_subnodes = (UNFO_HSList*)it->data;
        for (it = tmp_subnodes->first; it != NULL; it=it->next) {
            if (((UNFO_RTreeData*)it->data)->subnodes->first) {
                unfo_hslist_append(tmplist,
                                    ((UNFO_RTreeData*)it->data)->subnodes, 0);
            }
            if (((UNFO_RTreeData*)it->data)->data != NULL) {
                unfo_hslist_append(ret,
                                    ((UNFO_RTreeData*)it->data)->data, 0);
            }
        }
        free(firstit);
    }
    unfo_hslist_destroy(&tmplist);
    return ret;
}

UNFO_RTree * unfo_rtree_clone(UNFO_RTree *rt) {

    UNFO_HSList *to_clone, *tmplist, *new_subnodes;
    UNFO_RTree *ret;
    UNFO_HSListItem *it, *it2;
    UNFO_RTreeData *rtdata;
    void *new_data;

    if (!rt) return NULL;

    to_clone = unfo_hslist_create();
    unfo_hslist_init(to_clone, NULL, NULL, NULL);
    ret = unfo_rtree_create(rt->data_constructor, rt->data_cloner,
                             rt->data_destructor);


    for (it = rt->subnodes->first; it != NULL; it = it->next) {
        rtdata = unfo_rtree_data_create(ret,
                                      ((UNFO_RTreeData*)it->data)->key, NULL);
        if (((UNFO_RTreeData*)it->data)->data != NULL)
            new_data = rt->data_cloner(((UNFO_RTreeData*)it->data)->data);
        else
            new_data = NULL;
        unfo_hslist_destroy(&rtdata->subnodes);
        rtdata->subnodes = ((UNFO_RTreeData*)it->data)->subnodes;
        rtdata->data = new_data;
        unfo_hslist_append(ret->subnodes, rtdata, 0);

        unfo_hslist_append(to_clone, rtdata, 0);
    }


    while (to_clone->first) {
        it2 = to_clone->first;
        tmplist = ((UNFO_RTreeData*)it2->data)->subnodes;
        unfo_hslist_remove(to_clone, to_clone->first);

        new_subnodes = unfo_hslist_create();
        unfo_hslist_init(new_subnodes, NULL, NULL, &unfo_rtree_data_destroy_v);
        for (it = tmplist->first; it != NULL; it = it->next) {
            rtdata = unfo_rtree_data_create(ret,
                                      ((UNFO_RTreeData*)it->data)->key, NULL);
            if (((UNFO_RTreeData*)it->data)->data != NULL)
                new_data = rt->data_cloner(((UNFO_RTreeData*)it->data)->data);
            else
                new_data = NULL;
            unfo_hslist_destroy(&rtdata->subnodes);
            rtdata->subnodes = ((UNFO_RTreeData*)it->data)->subnodes;
            rtdata->data = new_data;
            unfo_hslist_append(new_subnodes, rtdata, 0);

            unfo_hslist_append(to_clone, rtdata, 0);
        }
        ((UNFO_RTreeData*)it2->data)->subnodes = new_subnodes;
        free(it2);
    }
    unfo_hslist_destroy(&to_clone);
    return ret;
}

void unfo_rtree_values_walk(UNFO_RTree * rt, void* udata,
                              void (*walk_f)(void*, void*)) {
    UNFO_HSList *tmplist, *tmp_subnodes;
    UNFO_HSListItem *it;
    tmplist = unfo_hslist_create();
    unfo_hslist_init(tmplist, NULL, NULL, NULL);
    unfo_hslist_append(tmplist, rt->subnodes, 0);
    while (tmplist->first != NULL) {
        it = tmplist->first;
        unfo_hslist_remove(tmplist, tmplist->first);
        tmp_subnodes = (UNFO_HSList*)it->data;
        for (it = tmp_subnodes->first; it != NULL; it=it->next) {
            if (((UNFO_RTreeData*)it->data)->subnodes->first) {
                unfo_hslist_append(tmplist,
                                    ((UNFO_RTreeData*)it->data)->subnodes, 0);
            }
            if (((UNFO_RTreeData*)it->data)->data != NULL) {
               walk_f(udata, ((UNFO_RTreeData*)it->data)->data);
            }
        }
    }
    unfo_hslist_destroy(&tmplist);
}

void unfo_rtree_set(UNFO_RTree * rt, char * key, void * data)
{
    static UNFO_HSListItem *it;
    UNFO_HSList *subnodes;
    UNFO_RTreeData *rtd;
    static UNFO_RTreeData *rtdata;

    unsigned int len, offset=0;
    unsigned x, found = 0;
    void *ndata;
    char ended, tmpch;

    len = strlen(key);

    if (rt->subnodes == NULL)
        return;
    if (rt->data_constructor) {
        ndata = rt->data_constructor(data);
    } else {
        ndata = data;
    }

    subnodes = rt->subnodes;
    while (offset != len)
    {
        found = 0;
        for (it = subnodes->first; it != NULL; it=it->next) {
            if (((UNFO_RTreeData*)it->data)->key[0] == key[offset]) {
                found = 1;
                break;
            }
        }
        if (!found) { // not found in subnodes; create new subnode
            rtd = unfo_rtree_data_create(rt, key+offset, ndata);
            unfo_hslist_append(subnodes, rtd, 0);
            return;
        } else {
            rtdata = (UNFO_RTreeData*)it->data;
            ended = 0;
            for (x=1; ;x++) {
                if (rtdata->key[x] == 0) ended += 1;
                if (x == len - offset) ended += 2;
                if (ended != 0) break;
                if (key[offset+x] != rtdata->key[x]) break;
            }
            if (ended == 3) { //keys equals; data replacement
                rt->data_destructor(rtdata->data);
                rtdata->data = ndata;
                return;
            } else if (ended == 2) { //global key ends first; make global leaf
                unfo_hslist_remove(subnodes, it);
                it->next = NULL;
                rtd = unfo_rtree_data_create(rt, key, ndata);
                unfo_hslist_append(subnodes, rtd, 0);
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->last = it;
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->first = it;
                len = strlen(key + offset);

                memmove(rtdata->key,rtdata->key+strlen(key+offset),
                                    strlen(rtdata->key) - len);
                rtdata->key[strlen(rtdata->key) - len] = 0;
                rtdata->key = realloc(rtdata->key, sizeof(char)* (strlen(rtdata->key)+1));
                return;
            } else if (ended == 1) { //local key ends first; go deeper
                subnodes = rtdata->subnodes;
                offset += x;
            } else {
                unfo_hslist_remove(subnodes, it);  //remove old node
                tmpch = rtdata->key[x];             // split mutual key
                rtdata->key[x] = 0;
                /* insert new parent node with mutual key part */
                rtd = unfo_rtree_data_create(rt, rtdata->key, NULL);

                unfo_hslist_append(subnodes, rtd, 0);


                rtd = unfo_rtree_data_create(rt, key+offset+x, ndata);
                unfo_hslist_append(
                            ((UNFO_RTreeData*)subnodes->last->data)->subnodes,
                            rtd, 0);

                it->next = NULL;
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->last->next = it;
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->last = it;
                rtdata->key[x] = tmpch;
                len = strlen(rtdata->key+x);
                memmove(rtdata->key,rtdata->key+x, sizeof(char)*len);
                rtdata->key = realloc(rtdata->key, sizeof(char)*(len+1));
                rtdata->key[len] = 0;
                return;
            }
        }
    }
}

void unfo_rtree_set_n(UNFO_RTree * rt, char * key,
                       unsigned int len, void * data)
{
    static UNFO_HSListItem *it;
    UNFO_HSList *subnodes;
    UNFO_RTreeData *rtd;
    static UNFO_RTreeData *rtdata;

    unsigned int klen, offset=0;
    unsigned x, found = 0;
    void *ndata;
    char ended, tmpch;

    if (rt->subnodes == NULL)
        return;
    if (rt->data_constructor)
        ndata = rt->data_constructor(data);
    else
        ndata = data;

    subnodes = rt->subnodes;
    while (offset != len)
    {
        found = 0;
        for (it = subnodes->first; it != NULL; it=it->next) {
            if (((UNFO_RTreeData*)it->data)->key[0] == key[offset]) {
                found = 1;
                break;
            }
        }
        if (!found) { // not found in subnodes; create new subnode
            rtd = unfo_rtree_data_create_n(rt, key+offset, len, ndata);
            unfo_hslist_append(subnodes, rtd, 0);
            return;
        } else {
            rtdata = (UNFO_RTreeData*)it->data;
            ended = 0;
            for (x=1; ;x++) {
                if (rtdata->key[x] == 0) ended += 1;
                if (x == len-offset) ended += 2;
                if (ended != 0) break;
                if (key[offset+x] != rtdata->key[x]) break;
            }
            if (ended == 3) { //keys equals; data replacement
                if (rt->data_destructor)
                    rt->data_destructor(rtdata->data);
                return;
            } else if (ended == 2) { //global key ends first; make global leaf
                unfo_hslist_remove(subnodes, it);
                it->next = NULL;
                rtd = unfo_rtree_data_create_n(rt, key, len, ndata);
                unfo_hslist_append(subnodes, rtd, 0);
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->last = it;
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->first = it;
                klen = len-offset;
                memmove(rtdata->key,rtdata->key+(klen-offset), sizeof(char)*klen);
                rtdata->key[len] = 0;
                return;
            } else if (ended == 1) { //local key ends first; go deeper
                subnodes = rtdata->subnodes;
                offset += x;
            } else {
                unfo_hslist_remove(subnodes, it);
                tmpch = rtdata->key[x];
                rtdata->key[x] = 0;
                rtd = unfo_rtree_data_create(rt, rtdata->key, NULL);
                unfo_hslist_append(subnodes, rtd, 0);
                rtd = unfo_rtree_data_create_n(rt, key+offset+x,
                                                 len-offset-x, ndata);
                unfo_hslist_append(
                            ((UNFO_RTreeData*)subnodes->last->data)->subnodes,
                            rtd, 0);
                rtdata->key[x] = tmpch;
                it->next = NULL;
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->last->next = it;
                ((UNFO_RTreeData*)subnodes->last->data)->subnodes->last = it;
                klen = strlen(rtdata->key+x);
                memmove(rtdata->key,rtdata->key+x, sizeof(char)*len);
                rtdata->key = realloc(rtdata->key, sizeof(char)*(len+1));
                rtdata->key[len] = 0;
                return;
            }
        }
    }
}

void* unfo_rtree_get(UNFO_RTree * rt, const char * key) {
    UNFO_HSList * subnodes;
    UNFO_HSListItem * it = NULL;
    UNFO_RTreeData * rtdata;
    unsigned int offset, len, x;
    char found, ended;

    len = strlen(key);
    offset = 0;
    subnodes = rt->subnodes;
    while (offset != len) {
        found = 0;
        for (it = subnodes->first; it != NULL; it=it->next) {
            if (((UNFO_RTreeData*)it->data)->key[0] == key[offset]) {
                found = 1;
                break;
            }
        }
        if (!found)
            return NULL;
        rtdata = (UNFO_RTreeData*)it->data;

        for (x=1; ;x++) {
            ended=0;
            if (x == strlen(rtdata->key)) ended += 1;
            if (x == len-offset) ended += 2;
            if (ended != 0) break;
            if (key[offset+x] != rtdata->key[x]) break;
        }
        if (ended == 3) return rtdata->data;
        else if (ended == 1) offset+=x;
        else return NULL;
        subnodes = ((UNFO_RTreeData*)it->data)->subnodes;
    }
    if (it != NULL)
        return ((UNFO_RTreeData*)it->data)->data;
    else return NULL;
}

void unfo_rtree_unset(UNFO_RTree * rt, const char * key) {
    UNFO_HSList * subnodes;
    UNFO_HSListItem * it;
    UNFO_RTreeData * rtdata;
    unsigned int offset, len, x;
    char found, ended;
    UNFO_HSList * path;

    struct Relation {
        UNFO_HSList * parent_nodes;
        UNFO_HSListItem * child_it;
    } *relation;

    path = unfo_hslist_create();
    unfo_hslist_init(path, NULL, NULL, &free);

    len = strlen(key);
    offset = 0;
    subnodes = rt->subnodes;
    while (offset != len) {
        found = 0;
        for (it = subnodes->first; it != NULL; it=it->next) {
            if (((UNFO_RTreeData*)it->data)->key[0] == key[offset]) {
                found = 1;
                break;
            }
        }
        if (!found)
            return;
        rtdata = (UNFO_RTreeData*)it->data;

        for (x=1; ;x++) {
            ended=0;
            if (rtdata->key[x] == 0) ended += 1;
            if (x == len - offset) ended += 2;
            if (ended != 0) break;
            if (key[offset+x] != rtdata->key[x]) break;
        }
        if (ended == 3) {
            /* remove node from tree only if there's no descendant*/
            if (rtdata->subnodes->last == NULL) {
                //printf("removing all\n");
                unfo_hslist_remove(subnodes, it);
                unfo_rtree_data_destroy(rtdata);
                free(it);
            }
            else if (rtdata->data_destructor != NULL) {
                //printf("removing data only\n");
                (*rtdata->data_destructor)(rtdata->data);
                rtdata->is_leaf = 0;
                rtdata->data = NULL;
            }

            if (path->last == NULL) {
                unfo_hslist_destroy(&path);
                return;
            }
            rtdata = (UNFO_RTreeData*)
                     ((struct Relation*)path->last->data)->child_it->data;

            /*remove all predecessor of deleted node (recursive) with no childs*/
            while (rtdata->subnodes->last == NULL) {
                //printf("removing '%s'\n", rtdata->key);
                unfo_rtree_data_destroy(rtdata);
                unfo_hslist_remove(
                            ((struct Relation*)path->last->data)->parent_nodes,
                            ((struct Relation*)path->last->data)->child_it);
                free(((struct Relation*)path->last->data)->child_it);
                it = path->last;
                unfo_hslist_remove(path, path->last);
                free(it);
                rtdata = (UNFO_RTreeData*)
                         ((struct Relation*)path->last->data)->child_it->data;
            }
            unfo_hslist_destroy(&path);
            return;
        }
        else if (ended == 1) offset+=x;
        else return;
        if ((relation = malloc(sizeof(struct Relation))) == NULL) {
            unfo_hslist_destroy(&path);
            return;
        }
        subnodes = ((UNFO_RTreeData*)it->data)->subnodes;
        relation->parent_nodes = subnodes;
        relation->child_it = it;
        unfo_hslist_append(path, (void*)relation, 0);
    }
    unfo_hslist_destroy(&path);
    return;
}

void unfo_rtree_clear(UNFO_RTree * rt) {
    UNFO_HSListItem *it, *oldit;
    if (rt==NULL) return;
    if (rt->subnodes == NULL) return;
    oldit = rt->subnodes->first;
    it = (oldit)?oldit->next:NULL;
    for (;it != NULL; it=it->next) {
        if (rt->subnodes->data_destructor != NULL)
            rt->subnodes->data_destructor(oldit->data);
        free(oldit);
        oldit = it;
    }
    if (oldit) {
        if (rt->subnodes->data_destructor != NULL)
            rt->subnodes->data_destructor(oldit->data);
        free(oldit);
    }
}

inline UNFO_HSList* __unfo_rtree_all(UNFO_RTree * rt, char pairorkey) {
    UNFO_HSList *tmplist, *tmp_subnodes, *ret;
    UNFO_HSListItem *it;
    struct Pair {
        UNFO_HSList * subnodes;
        char * key;
        char added;
    } *pair, *parent_pair;
    UNFO_RTreePair *rtpair;

    pair = malloc(sizeof(struct Pair));
    pair->subnodes = rt->subnodes;
    pair->key = NULL;
    pair->added = 0;

    tmplist = unfo_hslist_create();
    unfo_hslist_init(tmplist, NULL, NULL, &free);
    ret = unfo_hslist_create();
    if (pairorkey == 1)
        unfo_hslist_init(ret, NULL, NULL, &free);
    else
        unfo_hslist_init(ret, NULL, NULL, &unfo_rtree_pair_destroy_v);

    unfo_hslist_append(tmplist, pair, 0);

    while (tmplist->first != NULL) {
        it = tmplist->first;
        unfo_hslist_remove(tmplist, tmplist->first);
        tmp_subnodes = ((struct Pair*)it->data)->subnodes;
        parent_pair = (struct Pair*) it->data;
        free(it);

        for (it = tmp_subnodes->first; it != NULL; it=it->next) {
            pair = malloc(sizeof(struct Pair));
            pair->subnodes = ((UNFO_RTreeData*)it->data)->subnodes;
            pair->added = 0;

            if (parent_pair->key != NULL) {
                pair->key =
                    malloc(sizeof(char)
                           * (strlen(((UNFO_RTreeData*)it->data)->key)
                           + strlen(parent_pair->key) + 1));
                memcpy(pair->key, parent_pair->key,
                       sizeof(char) * strlen(parent_pair->key));
                memcpy(pair->key+strlen(parent_pair->key),
                       ((UNFO_RTreeData*)it->data)->key,
                       sizeof(char)*(strlen(((UNFO_RTreeData*)it->data)->key)+1));
            } else {
                pair->key = malloc(sizeof(char)*
                                (strlen(((UNFO_RTreeData*)it->data)->key) +
                                1));
                memcpy(pair->key, ((UNFO_RTreeData*)it->data)->key,
                       sizeof(char)*(strlen(((UNFO_RTreeData*)it->data)->key)+1));
            }
            /* current node has data */
            if (((UNFO_RTreeData*)it->data)->data != NULL) {
                if (pairorkey == 1) {
                    unfo_hslist_append(ret, pair->key, 0);
                } else {
                    rtpair = malloc(sizeof(UNFO_RTreePair));
                    rtpair->key = pair->key;
                    rtpair->data = ((UNFO_RTreeData*)it->data)->data;
                    unfo_hslist_append(ret, rtpair, 0);
                }
                pair->added = 1;
                if (((UNFO_RTreeData*)it->data)->subnodes->first != NULL) {
                    unfo_hslist_append(tmplist, pair, 0);
                } else {
                    free(pair);
                }
            /* current node hasn't data */
            } else {
                if (((UNFO_RTreeData*)it->data)->subnodes->first) {
                    unfo_hslist_append(tmplist, pair, 0);
                } else {
                    free(pair->key);
                    free(pair);
                }
            }
        }
        if (parent_pair->added == 0)
            free(parent_pair->key);
        free(parent_pair);
    }
    unfo_hslist_destroy(&tmplist);
    return ret;
}

void unfo_rtree_unite(UNFO_RTree *rt1, UNFO_RTree *rt2) {
    UNFO_HSList *tmplist, *tmp_subnodes;
    UNFO_HSListItem *it;
    struct Pair {
        UNFO_HSList * subnodes;
        char * key;
        char added;
    } *pair, *parent_pair;

    pair = malloc(sizeof(struct Pair));
    pair->subnodes = rt2->subnodes;
    pair->key = NULL;

    tmplist = unfo_hslist_create();
    unfo_hslist_init(tmplist, NULL, NULL, &free);
    unfo_hslist_append(tmplist, pair, 0);

    while (tmplist->first != NULL) {
        it = tmplist->first;
        unfo_hslist_remove(tmplist, tmplist->first);
        tmp_subnodes = ((struct Pair*)it->data)->subnodes;
        parent_pair = (struct Pair*) it->data;
        //printf("key-part:%s\n", parent_pair->key);
        free(it);

        //pair->added = 0;
        for (it = tmp_subnodes->first; it != NULL; it=it->next) {
            pair = malloc(sizeof(struct Pair));
            pair->subnodes = ((UNFO_RTreeData*)it->data)->subnodes;

            if (parent_pair->key != NULL) {
                pair->key = malloc(sizeof(char)
                               * (strlen(((UNFO_RTreeData*)it->data)->key)
                               + strlen(parent_pair->key) + 1));
                memcpy(pair->key, parent_pair->key,
                       sizeof(char) * strlen(parent_pair->key));
                memcpy(pair->key + strlen(parent_pair->key),
                       ((UNFO_RTreeData*)it->data)->key,
                       sizeof(char)*(strlen(((UNFO_RTreeData*)it->data)->key)+1));
            } else {
                pair->key = malloc(sizeof(char)*
                                (strlen(((UNFO_RTreeData*)it->data)->key) +1));
                memcpy(pair->key, ((UNFO_RTreeData*)it->data)->key,
                       sizeof(char)*(strlen(((UNFO_RTreeData*)it->data)->key)+1));
            }
            /* current node has data */
            if (((UNFO_RTreeData*)it->data)->data != NULL) {
                    unfo_rtree_set(rt1,
                                    pair->key,
                        rt2->data_cloner(((UNFO_RTreeData*)it->data)->data));
            }
            if (((UNFO_RTreeData*)it->data)->subnodes->first) {
                unfo_hslist_append(tmplist, pair, 0);
            } else {
                free(pair->key);
                free(pair);
            }
        }
        free(parent_pair->key);
        free(parent_pair);
    }
    unfo_hslist_destroy(&tmplist);
}

UNFO_RTree* unfo_rtree_union(UNFO_RTree *rt1, UNFO_RTree *rt2){
    UNFO_RTree *ret;
    ret = unfo_rtree_clone(rt2);
    unfo_rtree_unite(ret, rt1);
    return ret;
}


UNFO_HSList* unfo_rtree_keys(UNFO_RTree * rt) {
    return __unfo_rtree_all(rt, 1);
}

UNFO_HSList* unfo_rtree_pairs(UNFO_RTree * rt) {
    return __unfo_rtree_all(rt, 0);
}

inline void unfo_rtree_pair_destroy(UNFO_RTreePair * pair) {
    free(pair->key);
    free(pair);
}

inline void unfo_rtree_pair_destroy_v(void * pair) {
    free(((UNFO_RTreePair *)pair)->key);
    free(pair);
}
