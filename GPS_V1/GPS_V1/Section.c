#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Section.h"
#include "ItemList.h"

char* sec_type[] = {"none", "wall", "section", "promo", "checkout", "entrance", "reception" };

void testSect(void)
{
	item itest1;
	itest1.category = legumes_vert;
	itest1.id = 1;
	strcpy(itest1.name, "haricots");
	itest1.cost = 3.50;
	itest1.i_section = NULL;

	item itest2;
	itest2.category = fromage;
	itest2.id = 2;
	strcpy(itest2.name, "lerdammer");
	itest2.cost = 7.40;
	itest2.i_section = NULL;

	section * stest = newSection(1, t_section);
	Section_setPos(stest, 10, 15);
	Section_setSize(stest, 8, 2);

	Section_addItem(stest, &itest1);
	Section_addItem(stest, &itest2);

	Section_print(stest);
}

section * newSection(int id, type s_type)
{
	section * s_new;
	s_new = (section *)malloc(sizeof(section));

	Section_init(s_new);
	s_new->id = id;
	s_new->s_type = s_type;

	if (Section_hasStock(s_new))
	{
		s_new->stock = (list *)malloc(sizeof(list));
		initList(s_new->stock);
	}

	return s_new;
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
	if (id < 0)
		return EXIT_FAILURE;
	s_source->id = id;
	return EXIT_SUCCESS;
}

int Section_setType(section * s_source, type s_type)
{
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

int Section_addItem(section * s_source, item * i_source)
{
	if (s_source == NULL || i_source == NULL)
		return EXIT_FAILURE;
	if (i_source->i_section != NULL)
		return EXIT_FAILURE;
	insertLast(s_source->stock, i_source);
	i_source->i_section = s_source;
	s_source->nb_items++;
	return EXIT_SUCCESS;
}

int Section_removeItem(item * i_source)
{
	if (i_source == NULL)
		return EXIT_FAILURE;
	if (i_source->i_section == NULL)
		return EXIT_FAILURE;

	section * s_temp = i_source->i_section;

	if (!find(s_temp->stock, i_source))
		return EXIT_FAILURE;
	deleteCurrent(s_temp->stock);
	s_temp->nb_items--;

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