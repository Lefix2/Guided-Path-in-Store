#include <string.h>

#include "Store.h"
#include "Section.h"
#include "SectionList.h"
#include "Item.h"
#include "ItemList.h"

store * newStore(int id, char * name, int x_size, int y_size)
{
	store * st_new = (store *)malloc(sizeof(store));

	Store_init(st_new);
	Store_setId(st_new, id);
	Store_setName(st_new, name);
	Store_setSize(st_new, x_size, y_size);
	st_new->allocated_stock = newItemList();

	return st_new;
}

store * Store_init(store * st_source)
{
	st_source->id = 0;
	st_source->name[0] = 0;
	st_source->size[X] = 0;
	st_source->size[Y] = 0;
	st_source->allocated_stock = NULL;
	st_source->cartography = NULL;
	
	return st_source;
}

store Store_delete(store * st_source)
{
	store tmp = *st_source;
	deleteItemList(st_source->allocated_stock);
	free(st_source);
	return tmp;
}

int Store_setId(store * st_source, int id)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	st_source->id = id;
	return EXIT_SUCCESS;
}

int Store_setName(store * st_source, char * name)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	strcpy(st_source->name, name);
	return EXIT_SUCCESS;
}

int Store_setSize(store * st_source, int x_size, int y_size)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	Store_freeCartography(st_source);
	st_source->size[X] = x_size;
	st_source->size[Y] = y_size;
	return EXIT_SUCCESS;
}

int Store_getId(store * st_source)
{
	return st_source->id;
}

char * Store_getName(store * st_source)
{
	return st_source->name;
}

int Store_getXSize(store * st_source)
{
	return st_source->size[X];
}

int Store_getYSize(store * st_source)
{
	return st_source->size[Y];
}

int Store_freeCartography(store * st_source)
{
	for (int i = 0; i < st_source->size[X]; i++)
	{
		free(*(st_source->cartography+i));
	}
	free(st_source->cartography);
	return EXIT_SUCCESS;
}

int Store_computeCartography(store * st_source)
{
	st_source->cartography = (int**)calloc(st_source->size[X], sizeof(int*));
	for (int i = 0; i < st_source->size[X]; i++)
	{
		*(st_source->cartography + i) = (int*)calloc(st_source->size[Y], sizeof(int));
	}
	return EXIT_SUCCESS;
}

int Store_addItem(store * st_source, int id, category i_category, char * name)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	item * new_i = newItem(id, i_category, name);
	insertSortItem(st_source->allocated_stock, new_i);
	return EXIT_SUCCESS;
}

int Store_addSection(store * st_source, int id, type s_type)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	section * new_s = newSection(id, s_type);
	insertSortSection(st_source->allocated_stock, new_s);
	return EXIT_SUCCESS;
}

int Store_deleteItem(store * st_source, item * i_source)
{

}


void testStore(void)
{
	store * sttest = newStore(0, "Carrefour - rennes", 100, 100);
	Store_computeCartography(sttest);
	Store_freeCartography(sttest);
	Store_delete(sttest);
}

int Store_deleteSection(store * st_source, section * s_source);