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
		s_new->stock = (list *)malloc(sizeof(list));
		initList(s_new->stock);
	}

	return s_new;
}

section * Section_delete(section * s_source)
{
	section * tmp = s_source;
	free(s_source);
	return tmp;
}

section * Section_init(section * s_source)
{
	s_source->id = 0;
	s_source->s_type = t_none;
	s_source->pos[X] = 0;
	s_source->pos[Y] = 0;
	s_source->size[X] = 0;
	s_source->size[Y] = 0;
	s_source->nb_items = 0;
	s_source->stock = NULL;

	return s_source;
}

int Section_isEmpty(section * s_source)
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
	s_source->pos[X] = x_pos;
	s_source->pos[Y] = y_pos;
	return EXIT_SUCCESS;
}

int Section_setSize(section * s_source, int x_size, int y_size)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->size[X] = x_size;
	s_source->size[Y] = y_size;
	return EXIT_SUCCESS;
}

int Section_addItem(section * s_source, item * i_source, int pos_x, int pos_y)
{
	if (s_source == NULL || i_source == NULL)
		return EXIT_FAILURE;
	if (i_source->i_section != NULL)
		return EXIT_FAILURE;

	int x_max = s_source->size[X];
	int y_max = s_source->size[Y];
	if (!onBorder(pos_x, pos_y, 0, x_max, 0, y_max))
	{
		printf("error : Trying to put an item out of section borders\n");
		return EXIT_FAILURE;
	}

	Item_setPos(i_source, pos_x, pos_y);
	Item_setSection(i_source, s_source);
	insertLast(s_source->stock, i_source);
	s_source->nb_items++;
	return EXIT_SUCCESS;
}

int Section_removeItem(item * i_source)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	if (i_source->i_section == NULL)
		return EXIT_FAILURE;

	if (!find(i_source->i_section->stock, i_source))
		return EXIT_FAILURE;
	deleteCurrent(i_source->i_section->stock);
	i_source->i_section->nb_items--;

	Item_setSection(i_source, NULL);
	Item_setPos(i_source, 0, 0);

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

int Section_getXPos(section * s_source)
{
	return s_source->pos[X];
}

int Section_getYPos(section * s_source)
{
	return s_source->pos[Y];
}

int Section_getXSize(section * s_source)
{
	return s_source->size[X];
}

int Section_getYSize(section * s_source)
{
	return s_source->size[Y];
}

int Section_getNbItems(section * s_source)
{
	return s_source->nb_items;
}

void Section_print(section * s_source)
{
	printf("***** Section*****\n");
	printf("ID    : %d\n", s_source->id);
	printf("type  : %s\n", sec_type[s_source->s_type]);
	printf("pos X : %d -> %d (%d)\n", s_source->pos[X], s_source->size[X] + s_source->pos[X], s_source->size[X]);
	printf("    Y : %d -> %d (%d)\n", s_source->pos[Y], s_source->size[Y] + s_source->pos[Y], s_source->size[Y]);
	if (Section_hasStock(s_source))
	{
		printList(s_source->stock);
	}
}

void testSect(void)
{
	item * itest1 = newItem(1, legumes_vert, "haricots");
	Item_setCost(itest1, 3.50);

	item * itest2 = newItem(2, fromage, "lerdammer");
	Item_setCost(itest2, 7.40);

	item * itest3 = newItem(3, alcool, "Grimbergen");
	Item_setCost(itest3, 8.00);

	section * stest = newSection(1, t_section);
	Section_setPos(stest, 10, 15);
	Section_setSize(stest, 8, 2);

	Section_addItem(stest, itest1, 0, 0);
	Section_addItem(stest, itest2, 0, 0);
	Section_addItem(stest, itest3, 1, 5);//cet item ne peut être ajouté au millieu de la section

	Section_print(stest);

	Item_print(itest3);

	//delete function may only be used in Store functions
	Item_delete(itest1);
	Item_delete(itest2);
	Item_delete(itest3);

	Section_delete(stest);
}