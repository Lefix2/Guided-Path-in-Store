#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Common.h"

nodeList * newNodeList(item *i, nodeList *n);

list * newList(void);
int deleteList(list * l);

void initList(list * l);
int empty(list * l);
int first(list * l);
int last(list * l);
int outOfList(list * l);
void setOnFirst(list * l);
void setOnLast(list * l);
void next(list * l);
item * getCurrentItem(list * l);
void printList(list * l);
int insertFirst(list * l, item * i);
int insertLast(list * l, item * i);
int insertBeforeCurrent(list * l, item * i);
int insertAfterCurrent(list * l, item * i);
void deletFirst(list * l);
void deleteLast(list * l);
void deleteCurrent(list * l);
int find(list * l, item * i);
int insertSort(list * l, item * i);

#endif // !ITEMLIST_H
