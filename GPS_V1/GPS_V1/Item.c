#include <string.h>

#include "Item.h"
#include "Section.h"

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
	i_source->fresh = FALSE;
	i_source->fragility = 0;
	i_source->cost = 0;
	i_source->promotion = FALSE;
	i_source->pos_s[X] = 0;
	i_source->pos_s[Y] = 0;
	i_source->i_section = NULL;

	return i_source;
}

item Item_delete(item * i_source)
{
	item tmp = * i_source;
	free(i_source);
	return tmp;
}

gboolean Item_HasSection(item * i_source)
{
	return (i_source->i_section != NULL);
}

int Item_setId(item * i_source, int id)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	if (id < 0)
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
	if (i_category < 0)
		return EXIT_FAILURE;
	i_source->i_category = i_category;
	return EXIT_SUCCESS;
}

int Item_setFresh(item * i_source, gboolean fresh)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->fresh = fresh;
	return EXIT_SUCCESS;
}

int Item_setFragility(item * i_source, int fragility)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	if (fragility < ITEM_FRAGILITY_MIN || fragility > ITEM_FRAGILITY_MAX)
		return EXIT_FAILURE;
	i_source->fragility = fragility;
	return EXIT_SUCCESS;
}

int Item_setCost(item * i_source, double cost)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->cost = cost;
	return EXIT_SUCCESS;
}

int Item_setPromotion(item * i_source, gboolean promotion)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->promotion = promotion;
	return EXIT_SUCCESS;
}

int Item_setPos(item * i_source, int x_pos, int y_pos)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->pos_s[X] = x_pos;
	i_source->pos_s[Y] = y_pos;
	return EXIT_SUCCESS;
}

int Item_setSection(item * i_source, section * i_section)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	i_source->i_section = i_section;
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

char * Item_getCategoryString(item * i_source)
{
	return item_category[i_source->i_category];
}

gboolean Item_isFresh(item * i_source)
{
	return i_source->fresh;
}

int Item_getFragility(item * i_source)
{
	return i_source->fragility;
}

double Item_getCost(item * i_source)
{
	return i_source->cost;
}

gboolean Item_isInPromotion(item * i_source)
{
	return i_source->promotion;
}

int Item_getXPos(item * i_source)
{
	return i_source->pos_s[X];
}

int Item_getYPos(item * i_source)
{
	return i_source->pos_s[Y];
}

section * Item_getSection(item * i_source)
{
	return i_source->i_section;
}

void Item_print(item * i_source, gboolean minimal)
{
	if (minimal)
	{
		printf("* Item %d : %s\n", i_source->id, i_source->name);
	}
	else
	{
		char i_fresh_string[] = "Yes";
		char i_promo_string[] = "Yes";

		if (i_source->fresh == FALSE)
			strcpy(i_fresh_string, "No");
		if (i_source->promotion == FALSE)
			strcpy(i_promo_string, "No");

		printf("****** Item ******\n");
		printf("ID               : %d\n", Item_getId(i_source));
		printf("Name             : %s\n", Item_getName(i_source));
		printf("Category         : %s\n", item_category[Item_getCategory(i_source)]);
		printf("Fresh product    : %s\n", i_fresh_string);
		printf("Promotion        : %s\n", i_promo_string);
		printf("Cost             : %.2f\n", Item_getCost(i_source));
		printf("Fragility coeff  : %d\n", Item_getFragility(i_source));
		if (Item_HasSection(i_source))
		{
			printf("Section ID       : %d\n", Item_getSection(i_source)->id);
			printf("pos X in Section : %d\n", Item_getXPos(i_source));
			printf("    Y in Section : %d\n", Item_getYPos(i_source));
		}
		else
			printf("No Section defined for this Item.");
	}
}

void testItem(void)
{
	section testSec;
	testSec.id = 1;
	testSec.size[X] = 20;
	testSec.size[Y] = 3;

	item * item1 = newItem(10, legumes_vert, "endives");
	Item_setCost(item1, 12.20);
	Item_setFragility(item1, 3);
	Item_setFresh(item1, FALSE);
	Item_setPromotion(item1, FALSE);
	Item_setSection(item1, &testSec);
	Item_setPos(item1, 19, 1);

	Item_print(item1, FALSE);
}