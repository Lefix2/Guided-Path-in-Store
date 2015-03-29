#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Common.h"

/**
* \struct nodeItemList
* \brief Structure for a node of a itemList of items
*/
struct nodeItemList{
	item * i;						/*!< pointer to an item */
	struct nodeItemList * nextItem;	/*!< pointer to the nextItem nodeItemList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct itemList{
	nodeItemList *firstItem;		/*!< first item of the list */
	nodeItemList *current;			/*!< current item of the list*/
	nodeItemList *lastItem;			/*!< last item of the list*/
};

nodeItemList * newNodeItemList(item *i, nodeItemList *n);

itemList * newItemList(void);
int deleteItemList(itemList * l);

void initItemList(itemList * l);
int emptyItemList(itemList * l);
int firstItem(itemList * l);
int lastItem(itemList * l);
int outOfItemList(itemList * l);
void setOnfirstItem(itemList * l);
void setOnlastItem(itemList * l);
void nextItem(itemList * l);
item * getCurrentItem(itemList * l);
void printItemList(itemList * l);
int insertfirstItem(itemList * l, item * i);
int insertlastItem(itemList * l, item * i);
int insertBeforeCurrentItem(itemList * l, item * i);
int insertAfterCurrentItem(itemList * l, item * i);
void deletfirstItem(itemList * l);
void deletelastItem(itemList * l);
void deleteCurrentItem(itemList * l);
int findItem(itemList * l, item * i);
int insertSortItem(itemList * l, item * i);

#endif // !ITEMLIST_H
