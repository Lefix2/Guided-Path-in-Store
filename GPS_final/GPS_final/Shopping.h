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

shopping *shopping_new();
int shopping_delete(shopping *shopping);

int shopping_set_store(shopping * shopping, store * store);
int shopping_set_list(shopping *shopping, itemList *list);

store *shopping_get_store(shopping *shopping);
itemList *shopping_get_list(shopping *shopping);

#endif // !SHOPPING_H
