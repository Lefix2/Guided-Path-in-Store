#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Common.h"

/**
* \struct nodeItemList
* \brief Structure for a node of a itemList of items
*/
struct nodeItemList{
	item * i;						/*!< pointer to an item */
	struct nodeItemList * itemPointerList_next;	/*!< pointer to the itemPointerList_next nodeItemList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct itemList{
	nodeItemList *first;		/*!< first item of the list */
	nodeItemList *current;			/*!< current item of the list*/
	nodeItemList *last;			/*!< last item of the list*/
};

nodeItemList * nodeItemPointerList_new(item *i, nodeItemList *n);

itemList * itemPointerList_new(void);
int itemPointerList_delete(itemList * l);

void itemPointerList_init(itemList * l);
int itemPointerList_is_empty(itemList * l);

int itemPointerList_is_on_first(itemList * l);
int itemPointerList_is_on_last(itemList * l);
int itemPointerList_is_out_of(itemList * l);

void itemPointerList_set_on_first(itemList * l);
void itemPointerList_set_on_last(itemList * l);
void itemPointerList_next(itemList * l);

void itemPointerList_print(itemList * l, gboolean minimal);

int itemPointerList_insert_first(itemList * l, item * i);
int itemPointerList_insert_last(itemList * l, item * i);
int itemPointerList_insert_before_current(itemList * l, item * i);
int itemPointerList_insert_after_current(itemList * l, item * i);
int itemPointerList_insert_sort(itemList * l, item * i);

item * itemPointerList_delete_first(itemList * l);
item * itemPointerList_delete_last(itemList * l);
item * itemPointerList_delete_current(itemList * l);
item * itemPointerList_delete_single(itemList * l, item * i);

item * itemPointerList_get_current(itemList * l);
item * itemPointerList_find(itemList * l, item * i);
item * itemPointerList_find_id(itemList * l, int id);

#endif // !ITEMLIST_H
