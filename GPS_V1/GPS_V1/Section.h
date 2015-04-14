#ifndef SECTION_H
#define SECTION_H

#define SECTYPDEF
#include "Common.h"

/**
* \struct section
* \brief Structure image of a section
*
*Can be a wall, a section, an entrance etc.
*
*/
struct section{
	int id;							/*!< section's identifiant */
	type s_type;					/*!< section's type (wall, section etc...*/
	coord pos;						/*!< section's position in store in X and Y */
	coord size;					/*!< section's size in X and Y */
	int nb_items;					/*!< number of items stored in the section of type section */
	itemList * stock;				/*!< itemList of item pointers pointing to a Store allocatedStock */
};

section * newSection(int id, type s_type);
section * Section_init(section * s_source);
int Section_delete(section * s_source);

int Section_isemptyItemPointerList(section * s_source);
int Section_hasStock(section * s_source);

int Section_setId(section * s_source, int id);
int Section_setType(section * s_source, type s_type);
int Section_setPos(section * s_source, int x_pos, int y_pos);
int Section_setSize(section * s_source, int x_size, int y_size);

int Section_getId(section * s_source);
type Section_getType(section * s_source);
char * Section_getTypeString(section * s_source);
int Section_getXPos(section * s_source);
int Section_getYPos(section * s_source);
int Section_getXSize(section * s_source);
int Section_getYSize(section * s_source);
int Section_getNbItems(section * s_source);

int Section_addItem(section * s_source, item * item, int x_pos, int y_pos);
int Section_removeItem(item * item);

void Section_print(section * s_source, gboolean minimal);

void testSect(void);

#endif