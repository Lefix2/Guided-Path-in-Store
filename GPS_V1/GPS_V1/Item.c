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
	i_source->i_section = NULL;

	return i_source;
}

int Item_setPos(item * i_source, int pos_x, int pos_y)
{
	if (i_source->i_section == NULL)
		return EXIT_FAILURE;
	int x_min = i_source->i_section->pos[X];
	int y_min = i_source->i_section->pos[Y];
	int x_max = i_source->i_section->size[X] + x_min;
	int y_max = i_source->i_section->size[Y] + y_min;

	return EXIT_FAILURE;
}

void Item_print(item * i_source)
{
	printf("| %12d | %12s | %12s | %11.2fE | %12d |\n", i_source->id, i_source->name, item_category[i_source->i_category], i_source->cost, i_source->i_section->id);
}