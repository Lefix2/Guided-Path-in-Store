#include <string.h>

#include "Section.h"
#include "Item.h"
#include "ItemList.h"

section * newSection(int id, type s_type)
{
	section * s_new;
	s_new = (section *)malloc(sizeof(section));

	Section_init(s_new);
	Section_setId(s_new, id);
	Section_setType(s_new, s_type);

	if (Section_hasStock(s_new))
	{
		s_new->stock = item_newPointerList();
	}

	return s_new;
}

section * Section_init(section * s_source)
{
	s_source->id = 0;
	s_source->s_type = t_none;
	s_source->pos.x = 0;
	s_source->pos.y = 0;
	s_source->size.x = 0;
	s_source->size.y = 0;
	s_source->nb_items = 0;
	s_source->stock = NULL;

	return s_source;
}

int Section_delete(section * s_source)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	deleteItemPointerList(s_source->stock);
	free(s_source);
	return EXIT_SUCCESS;
}

int Section_isemptyItemPointerList(section * s_source)
{
	return (s_source->nb_items == 0);
}

int Section_hasStock(section * s_source)
{
	return(s_source->s_type == t_section || s_source->s_type == t_promo);
}

int Section_setId(section * s_source, int id)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (id < 0)
		return EXIT_FAILURE;
	s_source->id = id;
	return EXIT_SUCCESS;
}

int Section_setType(section * s_source, type s_type)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (s_type < 0)
		return EXIT_FAILURE;
	s_source->s_type = s_type;
	return EXIT_SUCCESS;
}

int Section_setPos(section * s_source, int x_pos, int y_pos)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->pos.x = x_pos;
	s_source->pos.y = y_pos;
	return EXIT_SUCCESS;
}

int Section_setSize(section * s_source, int x_size, int y_size)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->size.x = x_size;
	s_source->size.y = y_size;
	return EXIT_SUCCESS;
}

int Section_addItem(section * s_source, item * item, int x_pos, int y_pos)
{
	if (s_source == NULL || item == NULL)
		return EXIT_FAILURE;
	if (item->section != NULL)
	{
		printf("error : Trying to add an item already stored in a section\n");
		item_print(item, TRUE);
		Section_print(s_source, TRUE);
		printf("\n");
		return EXIT_FAILURE;
	}

	int x_max = s_source->size.x;
	int y_max = s_source->size.y;
	if (!on_border(x_pos, y_pos, 0, x_max, 0, y_max))
	{
		printf("error : Trying to put an item out of section borders\n");
		item_print(item, TRUE);
		printf("\n");
		return EXIT_FAILURE;
	}

	item_set_pos(item, x_pos, y_pos);
	item_set_section(item, s_source);
	insertlastItemPointer(s_source->stock, item);
	s_source->nb_items++;
	return EXIT_SUCCESS;
}

int Section_removeItem(item * item)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (item->section == NULL)
		return EXIT_FAILURE;

	if (!findItemPointer(item->section->stock, item))
		return EXIT_FAILURE;
	deleteCurrentItemPointer(item->section->stock);
	item->section->nb_items--;

	item_set_section(item, NULL);
	item_set_pos(item, 0, 0);

	return EXIT_SUCCESS;
}

int Section_getId(section * s_source)
{
	return s_source->id;
}

type Section_getType(section * s_source)
{
	return s_source->s_type;
}

char * Section_getTypeString(section * s_source)
{
	return sec_type[s_source->s_type];
}

int Section_getXPos(section * s_source)
{
	return s_source->pos.x;
}

int Section_getYPos(section * s_source)
{
	return s_source->pos.y;
}

int Section_getXSize(section * s_source)
{
	return s_source->size.x;
}

int Section_getYSize(section * s_source)
{
	return s_source->size.y;
}

int Section_getNbItems(section * s_source)
{
	return s_source->nb_items;
}

void Section_print(section * s_source, gboolean minimal)
{
	if (minimal)
	{
		printf("* Section %d\n", s_source->id);
	}
	else
	{
		printf("***** Section*****\n");
		printf("ID    : %d\n", s_source->id);
		printf("type  : %s\n", sec_type[s_source->s_type]);
		printf("pos X : %d -> %d (%d)\n", s_source->pos.x, s_source->size.x + s_source->pos.x, s_source->size.x);
		printf("    Y : %d -> %d (%d)\n", s_source->pos.y, s_source->size.y + s_source->pos.y, s_source->size.y);
		if (Section_hasStock(s_source))
		{
			printf("Stock : ");
			printItemList(s_source->stock, FALSE);
		}
	}

}

void testSect(void)
{
	item * itest1 = item_new(1, legumes_vert, "haricots");
	item_set_cost(itest1, 3.50);

	item * itest2 = item_new(2, fromage, "lerdammer");
	item_set_cost(itest2, 7.40);

	item * itest3 = item_new(3, alcool, "Grimbergen");
	item_set_cost(itest3, 8.00);

	section * stest = newSection(1, t_section);
	Section_setPos(stest, 10, 15);
	Section_setSize(stest, 8, 3);

	Section_addItem(stest, itest1, 0, 0);
	Section_addItem(stest, itest2, 2, 1);//cet item ne peut être ajouté au millieu de la section
	Section_addItem(stest, itest3, 1, 2);

	Section_print(stest, FALSE);

	//delete function may only be used in Store functions
	item_delete(itest1);
	item_delete(itest2);
	item_delete(itest3);

	Section_delete(stest);
}