#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Section.h"
#include "Item.h"

char* sec_type[] = {"none", "wall", "section", "promo", "checkout", "entrance", "reception" };

void testSect(void)
{
	item itest;
	itest.category = legumes_vert;
	itest.id = 1;
	strcpy(itest.name, "haricots");
	itest.cost = 3.50;
	itest.i_section = NULL;

	section stest;
	Section_init(&stest);
	Section_setId(&stest, 1);
	Section_setType(&stest, t_section);
	Section_setPos(&stest, 10, 15);
	Section_setSize(&stest, 8, 2);

	Section_addItem(&stest, &itest);

	Section_print(&stest);
}

section * newSection(int id, type s_type)
{
	section * s_new;
	s_new = (section *)malloc(sizeof(section));

	Section_init(s_new);
	s_new->id = id;
	s_new->s_type = s_type;

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

int Section_empty(section * s_source)
{
	return (s_source->nb_items == 0);
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
	if (Section_empty(s_source))
		s_source->stock = malloc(sizeof(item*));
	else
		s_source->stock = realloc(s_source->stock, (s_source->nb_items+1)*sizeof(item*));
	*((s_source->stock) + s_source->nb_items) = i_source;
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
	return 0;
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
	printf("section ID    : %d\n", s_source->id);
	printf("section type  : %s\n", sec_type[s_source->s_type]);
	printf("section pos X : %d -> %d (%d)\n", s_source->pos[X], s_source->size[X] + s_source->pos[X], s_source->size[X]);
	printf("            Y : %d -> %d (%d)\n", s_source->pos[Y], s_source->size[Y] + s_source->pos[Y], s_source->size[Y]);
	if (s_source->s_type == t_section)
	{
		int i;
		printf("%d items in stock :\n", s_source->nb_items);
		Item_printHeader(true);
		for (i = 0; i < s_source->nb_items; i++)
		{
			Item_print(*(s_source->stock + i));
		}
	}
}