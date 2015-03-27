#include <string.h>

#include "Item.h"

item * newItem(int id, category i_category, char * name)
{
	item * i_new;
	i_new = (item *)malloc(sizeof(item));

	Item_init(i_new);
	i_new->id = id;
	i_new->i_category = i_category;
	strcpy(i_new->name, name);

	return i_new;
}

item * Item_init(item * i_source)
{
	i_source->id = 0;
	i_source->name[0] = 0;
	i_source->i_category = c_none;
	i_source->fresh = false;
	i_source->fragility = 0;
	i_source->promotion = false;
	i_source->pos_s[X] = 0;
	i_source->pos_s[Y] = 0;
	i_source->i_section = NULL;

	return i_source;
}

int Item_setId(item * i_source, int id)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->id = id;
	return EXIT_SUCCESS;
}

int Item_setName(item * i_source, char * name)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	strcpy(i_source->name, name);
	return EXIT_SUCCESS;
}

int Item_setCategory(item * i_source, category i_category)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->i_category = i_category;
	return EXIT_SUCCESS;
}

int Item_setPos(item * i_source, int pos_x, int pos_y)
{
	if (i_source->i_section == NULL)
		return EXIT_FAILURE;
	int x_min = i_source->i_section->pos[X];
	int y_min = i_source->i_section->pos[Y];
	int x_max = i_source->i_section->size[X] + x_min;
	int y_max = i_source->i_section->size[Y] + y_min;
	if (!onBorder(pos_x, pos_y, x_min, x_max, y_min, y_max))
	{
		printf("Trying to put an item out of section borders");
		return EXIT_FAILURE;
	}
	i_source->pos_s[X] = pos_x;
	i_source->pos_s[Y] = pos_y;
	return EXIT_SUCCESS;
}

int Item_getId(item * i_source)
{
	 return i_source->id;
}

char * Item_getName(item * i_source)
{
	return i_source->name;
}

category Item_getCategory(item * i_source)
{
	return i_source->i_category;
}
/*
int Item_setPos(item * i_source, int pos_x, int pos_y)
{
	if (i_source->i_section == NULL)
		return EXIT_FAILURE;
	int x_min = i_source->i_section->pos[X];
	int y_min = i_source->i_section->pos[Y];
	int x_max = i_source->i_section->size[X] + x_min;
	int y_max = i_source->i_section->size[Y] + y_min;
	if (!onBorder(pos_x, pos_y, x_min, x_max, y_min, y_max))
	{
		printf("Trying to put an item out of section borders");
		return EXIT_FAILURE;
	}
	i_source->pos_s[X] = pos_x;
	i_source->pos_s[Y] = pos_y;
	return EXIT_SUCCESS;
}
*/
void Item_print(item * i_source)
{
	printf("| %12d | %12s | %12s | %11.2fE | %12d |\n", i_source->id, i_source->name, item_category[i_source->i_category], i_source->cost, i_source->i_section->id);
}