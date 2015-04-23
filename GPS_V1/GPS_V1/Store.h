#ifndef STORE_H
#define STORE_H

#include "Common.h"

/**
* \struct store
* \brief Structure image of a store
*/
struct store{
	int id;							/*!< Store's identifiant */
	char name[MAX_ARRAY_OF_CHAR];	/*!< Store's name */
	coord size;					/*!< size in X and Y of the store */
	itemList * allocatedStock;		/*!< itemList of item allocated in memory */
	sectionList * allocatedSections;	/*!< list of sections of the store */
	int ** cartography;				/*!< array image of the store's cartography */
};

store * store_new(int id, char * name, int x_size, int y_size);
store * store_init(store * st_source);
int store_delete(store * st_source);

int store_set_id(store * st_source, int id);
int store_set_name(store * st_source, char * name);
int store_set_size(store * st_source, int x_size, int y_size);

int store_get_id(store * st_source);
char * store_get_name(store * st_source);
int store_get_x_size(store * st_source);
itemList *store_get_allocatedStock(store * st_source);
sectionList *store_get_allocatedSections(store * st_source);
int store_get_y_size(store * st_source);

void store_print(store * st_source);
void store_print_carto(store * st_source);

int store_free_carto(store * st_source);
int store_alloc_carto(store * st_source);

int store_add_item(store * st_source, int id, category category, char * name);
int store_delete_item(store * st_source, item * item);
int store_delete_stock(store * st_source);

int store_add_section(store * st_source, int id, type s_type, int x_pos, int y_pos, int x_size, int y_size);
int store_delete_section(store * st_source, section * s_source);
int store_delete_sections(store * st_source);

int store_detect_collision(store * st_source, int x_pos, int y_pos, int x_size, int y_size);

void testStore(void);

#endif //!STORE_H