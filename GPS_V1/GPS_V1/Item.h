#ifndef ITEM_H
#define ITEM_H

#define ITECATDEF
#include "Common.h"

item * newItem(int id, category i_category, char * name);
item * Item_delete(item * i_source);
item * Item_init(item * i_source);

gboolean Item_HasSection(item * i_source);

int Item_setId(item * i_source, int id);
int Item_setName(item * i_source, char * name);
int Item_setCategory(item * i_source, category i_category);
char * Item_getCategoryString(item * i_source);
int Item_setFresh(item * i_source, gboolean fresh);
int Item_setFragility(item * i_source, int fragility);
int Item_setCost(item * i_source, double cost);
int Item_setPromotion(item * i_source, gboolean promotion);
int Item_setPos(item * i_source, int pos_x, int pos_y);
int Item_setSection(item * i_source, section * i_section);

int Item_getId(item * i_source);
char * Item_getName(item * i_source);
category Item_getCategory(item * i_source);
gboolean Item_isFresh(item * i_source);
int Item_getFragility(item * i_source);
double Item_getCost(item * i_source);
gboolean Item_isInPromotion(item * i_source);
int Item_getXPos(item * i_source);
int Item_getYPos(item * i_source);
section * Item_getSection(item * i_source);

void Item_print(item * i_source);

void testItem(void);

#endif // !ITEM_H