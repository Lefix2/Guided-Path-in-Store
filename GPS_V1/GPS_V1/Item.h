#ifndef ITEM_H
#define ITEM_H

#define ITECATDEF
#include "Common.h"

item * newItem(int id, category i_category, char * name);
item * Item_init(item * i_source);

void Item_print(item * i_source);

#endif // !ITEM_H