#include <string.h>

#include "Item.h"
#include "Section.h"

item * item_new(int id, category category, char * name)
{
	item * i_new;
	i_new = (item *)malloc(sizeof(item));

	item_init(i_new);
	i_new->id = id;
	i_new->category = category;
	strcpy(i_new->name, name);

	return i_new;
}

item * item_init(item * item)
{
	item->id = 0;
	item->name[0] = 0;
	item->category = c_none;
	item->fresh = FALSE;
	item->fragility = 0;
	item->cost = 0;
	item->promotion = FALSE;
	item->posInSec.x = 0;
	item->posInSec.y = 0;
	item->section = NULL;
	item->pathTo = NULL;

	return item;
}

int item_delete(item * item)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (item->pathTo != NULL)
		free(item->pathTo);
	free(item);
	return EXIT_SUCCESS;
}

gboolean item_has_section(item * item)
{
	return (item->section != NULL);
}

int item_set_Id(item * item, int id)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (id < 0)
		return EXIT_FAILURE;
	item->id = id;
	return EXIT_SUCCESS;
}

int item_set_name(item * item, char * name)
{
	if (item == NULL)
		return EXIT_FAILURE;
	strcpy(item->name, name);
	return EXIT_SUCCESS;
}

int item_set_category(item * item, category category)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (category < 0)
		return EXIT_FAILURE;
	item->category = category;
	return EXIT_SUCCESS;
}

int item_set_stock(item *item, int stock)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (stock < 0)
		return EXIT_FAILURE;
	item->stock = stock;
	return EXIT_SUCCESS;
}

int item_set_fresh(item * item, gboolean fresh)
{
	if (item == NULL)
		return EXIT_FAILURE;
	item->fresh = fresh;
	return EXIT_SUCCESS;
}

int item_set_fragility(item * item, int fragility)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (fragility < ITEM_FRAGILITY_MIN || fragility > ITEM_FRAGILITY_MAX)
		return EXIT_FAILURE;
	item->fragility = fragility;
	return EXIT_SUCCESS;
}

int item_set_cost(item * item, double cost)
{
	if (item == NULL)
		return EXIT_FAILURE;
	item->cost = cost;
	return EXIT_SUCCESS;
}

int item_set_promotion(item * item, gboolean promotion)
{
	if (item == NULL)
		return EXIT_FAILURE;
	item->promotion = promotion;
	return EXIT_SUCCESS;
}

int item_set_pos(item * item, int x_pos, int y_pos)
{
	if (item == NULL)
		return EXIT_FAILURE;
	item->posInSec.x = x_pos;
	item->posInSec.y = y_pos;
	return EXIT_SUCCESS;
}

int item_set_section(item * item, section * section)
{
	if (item == NULL)
		return EXIT_FAILURE;
	item->section = section;
	return EXIT_SUCCESS;
}

int item_get_id(item * item)
{
	 return item->id;
}

char * item_get_name(item * item)
{
	return item->name;
}

category item_get_category(item * item)
{
	return item->category;
}

char * item_get_category_string(item * item)
{
	return item_category[item->category];
}

int item_get_stock(item *item)
{
	return item->stock;
}

gboolean item_is_fresh(item * item)
{
	return item->fresh;
}

int item_get_fragility(item * item)
{
	return item->fragility;
}

double item_get_cost(item * item)
{
	return item->cost;
}

gboolean item_is_in_promotion(item * item)
{
	return item->promotion;
}

coord item_get_pos(item * item)
{
	return item->posInSec;
}

section * item_get_section(item * item)
{
	return item->section;
}

path * item_get_pathTo(item * item)
{
	return item->pathTo;
}
int item_compare_id(void *element1, void *element2)
{
	return (((item*)element2)->id - ((item*)element1)->id);
}

void item_print(item * item, gboolean minimal)
{
	if (minimal)
	{
		printf("* Item %d : %s\n", item->id, item->name);
	}
	else
	{
		char i_fresh_string[] = "Yes";
		char i_promo_string[] = "Yes";

		if (item->fresh == FALSE)
			strcpy(i_fresh_string, "No");
		if (item->promotion == FALSE)
			strcpy(i_promo_string, "No");

		printf("****** Item ******\n");
		printf("ID               : %d\n", item_get_id(item));
		printf("Name             : %s\n", item_get_name(item));
		printf("Category         : %s\n", item_category[item_get_category(item)]);
		printf("Fresh product    : %s\n", i_fresh_string);
		printf("Promotion        : %s\n", i_promo_string);
		printf("Cost             : %.2f\n", item_get_cost(item));
		printf("Fragility coeff  : %d\n", item_get_fragility(item));
		if (item_has_section(item))
		{
			printf("Section ID       : %d\n", item_get_section(item)->id);
			printf("pos X in Section : %d\n", item_get_pos(item).x);
			printf("    Y in Section : %d\n", item_get_pos(item).y);
		}
		else
			printf("No Section defined for this Item.");
	}
}

void testItem(void)
{
	section testSec;
	testSec.id = 1;
	testSec.size.x = 20;
	testSec.size.y = 3;

	item * item1 = item_new(10, legumes_vert, "endives");
	item_set_cost(item1, 12.20);
	item_set_fragility(item1, 3);
	item_set_fresh(item1, FALSE);
	item_set_promotion(item1, FALSE);
	item_set_section(item1, &testSec);
	item_set_pos(item1, 19, 1);

	item_print(item1, FALSE);

	item_delete(item1);
}