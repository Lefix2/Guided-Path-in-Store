#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Common.h"

/**
* \struct nodeItemList
* \brief Structure for a node of a itemList of items
*/
struct nodeItemList{
	item * i;						/*!< pointer to an item */
	struct nodeItemList * nextItemPointer;	/*!< pointer to the nextItemPointer nodeItemList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct itemList{
	nodeItemList *firstItemPointer;		/*!< first item of the list */
	nodeItemList *currentItem;			/*!< current item of the list*/
	nodeItemList *lastItemPointer;			/*!< last item of the list*/
};

nodeItemList * newNodeItemPointer(item *i, nodeItemList *n);

itemList * newItemPointerList(void);
int deleteItemPointerList(itemList * l);

void initItemPointerList(itemList * l);
int emptyItemPointerList(itemList * l);

int firstItemPointer(itemList * l);
int lastItemPointer(itemList * l);
int outOfItemPointerList(itemList * l);

void setOnFirstItemPointer(itemList * l);
void setOnLastItemPointer(itemList * l);
void nextItemPointer(itemList * l);

void printItemList(itemList * l, gboolean minimal);

int insertFirstItemPointer(itemList * l, item * i);
int insertlastItemPointer(itemList * l, item * i);
int insertBeforeCurrentItemPointer(itemList * l, item * i);
int insertAfterCurrentItemPointer(itemList * l, item * i);
int insertSortItemPointer(itemList * l, item * i);

item * deleteFirstItemPointer(itemList * l);
item * deleteLastItemPointer(itemList * l);
item * deleteCurrentItemPointer(itemList * l);
item * deleteSingleItemPointer(itemList * l, item * i);

item * getCurrentItemPointer(itemList * l);
item * findItemPointer(itemList * l, item * i);
item * findItemPointerId(itemList * l, int id);

#endif // !ITEMLIST_H
