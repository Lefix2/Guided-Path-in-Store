#ifndef ITEM_H
#define ITEM_H

#define ITECATDEF
#include "Common.h"

item * newItem(int id, category i_category, char * name);
item * Item_init(item * i_source);

int Item_setId(item * i_source, int id);
int Item_setName(item * i_source, char * name);
int Item_setCategory(item * i_source, category i_category);
int Item_setPos(item * i_source, int pos_x, int pos_y);

void Item_print(item * i_source);

#endif // !ITEM_H