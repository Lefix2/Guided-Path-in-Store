#ifndef SHOPPING_H
#define SHOPPING_H

#include "Common.h"
#include "Item.h"

struct shopping{
	store *Store;
	itemList *List;
	item *start;
	item *end;
};

shopping *shopping_new(store *Store);
int shopping_delete(shopping *shopping);

#endif // !SHOPPING_H
