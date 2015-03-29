#include <string.h>

#include "Store1.h"
#include "Section.h"
#include "Item.h"
#include "ItemList.h"

store * newStore(int id, char * name, int x_size, int y_size)
{
	store * st_new = (store *)malloc(sizeof(store));

	Store_init(st_new);
	Store_setId(st_new, id);
	Store_setName(st_new, name);
	Store_setSize(st_new, x_size, y_size);
	st_new = newList();

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
	deleteList(st_source->allocated_stock);
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
/*
int Store_freeCartography(store * st_source)
{
	for (int i = 0; i < st_source->size[X]; i++)
	{
		*(st_source->cartography + i) = free(st_source->size[Y], sizeof(int));
	}
}

int Store_computeCartography(store * st_source)
{
	for (int i = 0; i < st_source->size[X]; i++)
	{
		*(st_source->cartography + i) = (int*)calloc(st_source->size[Y], sizeof(int));
	}
}*/