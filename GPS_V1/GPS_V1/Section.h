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
	GdkPixbuf *pixbuf;				/*!< the pixbuf of the section*/
};

section * section_new(int id, type s_type);
section * section_init(section * s_source);
int section_delete(section * s_source);

int section_is_empty(section * s_source);
int section_has_stock(section * s_source);

int section_set_id(section * s_source, int id);
int section_set_type(section * s_source, type s_type);
int section_set_pos(section * s_source, int x_pos, int y_pos);
int section_set_size(section * s_source, int x_size, int y_size);
int section_set_pixbuf(section * s_source, GdkPixbuf *pixbuf);

int section_get_id(section * s_source);
type section_get_type(section * s_source);
char * section_get_type_string(section * s_source);
int section_get_x_pos(section * s_source);
int section_get_y_pos(section * s_source);
int section_get_x_size(section * s_source);
int section_get_y_size(section * s_source);
int section_get_nb_items(section * s_source);
GdkPixbuf* section_get_pixbuf(section * s_source);

int section_add_item(section * s_source, item * item, int x_pos, int y_pos);
int section_remove_item(item * item);

void section_print(section * s_source, gboolean minimal);

void testSect(void);

#endif