#ifndef ASTARLIST_H
#define ASTARLIST_H

#include "Common.h"

struct astarList{
	nodeAstarList *first;
	nodeAstarList *current;
	nodeAstarList *last;
};

nodeAstar * nodeAstar_new(coord pos, nodeAstar *parent);
astarList * astarList_new(void);
int astarList_delete(astarList * l);
void astarList_init(astarList * l);
int astarList_is_empty(astarList * l);
int astarList_is_on_first(astarList * l);
int astarList_is_on_last(astarList * l);
int astarList_is_out_of(astarList * l);
void astarList_set_on_first(astarList * l);
void astarList_set_on_last(astarList * l);
void next(astarList * l);
void astarList_print(astarList * l, gboolean minimal);
int astarList_insert_first(astarList * l, coord pos);
int astarList_insert_last(astarList * l, coord pos);
int astarList_insert_before_current(astarList * l, coord pos);
int astarList_insert_after_current(astarList * l, coord pos);
int astarList_insert_sort(astarList * l, coord pos);
nodeAstar * astarList_delete_first(astarList * l);
nodeAstar * astarList_delete_last(astarList * l);
nodeAstar * astarList_delete_current(astarList * l);
nodeAstar * astarList_delete_single(astarList * l, nodeAstar * a);
nodeAstar * astarList_get_current(astarList * l);
nodeAstar * astarList_find(astarList * l, nodeAstar * a);

#endif // !ASTARLIST_H
