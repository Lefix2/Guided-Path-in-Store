#include <string.h>

#include "Section.h"
#include "Item.h"
#include "ItemList.h"

section * section_new(int id, type s_type)
{
	section * s_new;
	s_new = (section *)malloc(sizeof(section));

	section_init(s_new);
	section_set_id(s_new, id);
	section_set_type(s_new, s_type);

	if (section_has_stock(s_new))
	{
		s_new->stock = itemPointerList_new();
	}

	return s_new;
}

section * section_init(section * s_source)
{
	s_source->id = 0;
	s_source->s_type = t_floor;
	s_source->pos.x = 0;
	s_source->pos.y = 0;
	s_source->size.x = 0;
	s_source->size.y = 0;
	s_source->nb_items = 0;
	s_source->stock = NULL;
	s_source->pixbuf = NULL;

	return s_source;
}

int section_delete(section * s_source)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	itemPointerList_delete(s_source->stock);
	if (s_source->pixbuf != NULL)
		g_object_unref(s_source->pixbuf);
	free(s_source);
	return EXIT_SUCCESS;
}

int section_is_empty(section * s_source)
{
	return (s_source->nb_items == 0);
}

int section_has_stock(section * s_source)
{
	return(s_source->s_type == t_section || s_source->s_type == t_promo);
}

int section_set_id(section * s_source, int id)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (id < 0)
		return EXIT_FAILURE;
	s_source->id = id;
	return EXIT_SUCCESS;
}

int section_set_type(section * s_source, type s_type)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (s_type < 0)
		return EXIT_FAILURE;
	s_source->s_type = s_type;
	return EXIT_SUCCESS;
}

int section_set_pos(section * s_source, int x_pos, int y_pos)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->pos.x = x_pos;
	s_source->pos.y = y_pos;
	return EXIT_SUCCESS;
}

int section_set_size(section * s_source, int x_size, int y_size)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->size.x = x_size;
	s_source->size.y = y_size;
	return EXIT_SUCCESS;
}

int section_set_pixbuf(section * s_source, GdkPixbuf *pixbuf)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (s_source->pixbuf != NULL)
		g_object_unref(s_source->pixbuf);
	s_source->pixbuf = pixbuf;
	return EXIT_SUCCESS;
}

int section_add_item(section * s_source, item * item, int x_pos, int y_pos)
{
	if (s_source == NULL || item == NULL)
		return EXIT_FAILURE;
	if (item->section != NULL)
	{
		printf("error : Trying to add an item already stored in a section\n");
		item_print(item, TRUE);
		section_print(s_source, TRUE);
		printf("\n");
		return EXIT_FAILURE;
	}
	coord itemPos = { x_pos, y_pos };
	if (!on_border(itemPos, zero, s_source->size, 1))
	{
		printf("error : Trying to put an item out of section borders\n");
		item_print(item, TRUE);
		printf("\n");
		return EXIT_FAILURE;
	}

	item_set_pos(item, x_pos, y_pos);
	item_set_section(item, s_source);
	itemPointerList_insert_last(s_source->stock, item);
	s_source->nb_items++;
	return EXIT_SUCCESS;
}

int section_remove_item(item * item)
{
	if (item == NULL)
		return EXIT_FAILURE;
	if (item->section == NULL)
		return EXIT_FAILURE;

	if (!itemPointerList_find(item->section->stock, item))
		return EXIT_FAILURE;
	itemPointerList_delete_current(item->section->stock);
	item->section->nb_items--;

	item_set_section(item, NULL);
	item_set_pos(item, 0, 0);

	return EXIT_SUCCESS;
}

int section_get_id(section * s_source)
{
	return s_source->id;
}

type section_get_type(section * s_source)
{
	return s_source->s_type;
}

char * section_get_type_string(section * s_source)
{
	return sec_type[s_source->s_type];
}

int section_get_x_pos(section * s_source)
{
	return s_source->pos.x;
}

int section_get_y_pos(section * s_source)
{
	return s_source->pos.y;
}

int section_get_x_size(section * s_source)
{
	return s_source->size.x;
}

int section_get_y_size(section * s_source)
{
	return s_source->size.y;
}

int section_get_nb_items(section * s_source)
{
	return s_source->nb_items;
}

GdkPixbuf* section_get_pixbuf(section * s_source)
{
	return s_source->pixbuf;
}

void section_print(section * s_source, gboolean minimal)
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
		if (section_has_stock(s_source))
		{
			printf("Stock : ");
			itemPointerList_print(s_source->stock, FALSE);
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

	section * stest = section_new(1, t_section);
	section_set_pos(stest, 10, 15);
	section_set_size(stest, 8, 3);

	section_add_item(stest, itest1, 0, 0);
	section_add_item(stest, itest2, 2, 1);//cet item ne peut être ajouté au millieu de la section
	section_add_item(stest, itest3, 1, 2);

	section_print(stest, FALSE);

	//delete function may only be used in Store functions
	item_delete(itest1);
	item_delete(itest2);
	item_delete(itest3);

	section_delete(stest);
}