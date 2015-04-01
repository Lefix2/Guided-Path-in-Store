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
	int size[2];					/*!< size in X and Y of the store */
	itemList * allocated_stock;		/*!< itemList of item allocated in memory */
	sectionList * allocated_sections;	/*!< list of sections of the store */
	int ** cartography;				/*!< array image of the store's cartography */
};

store * newStore(int id, char * name, int x_size, int y_size);
store * Store_init(store * st_source);
int Store_delete(store * st_source);

int Store_setId(store * st_source, int id);
int Store_setName(store * st_source, char * name);
int Store_setSize(store * st_source, int x_size, int y_size);

int Store_getId(store * st_source);
char * Store_getName(store * st_source);
int Store_getXSize(store * st_source);
int Store_getYSize(store * st_source);

void Store_print(store * st_source);

int Store_freeCartography(store * st_source);
int Store_computeCartography(store * st_source);

int Store_addItem(store * st_source, int id, category i_category, char * name);
int Store_deleteItem(store * st_source, item * i_source);
int Store_deleteAllocatedStock(store * st_source);
int Store_addSection(store * st_source, int id, type s_type, int x_pos, int y_pos, int x_size, int y_size);
int Store_deleteSection(store * st_source, section * s_source);
int Store_deleteAllocatedSections(store * st_source);

void testStore(void);

#endif //!STORE_H