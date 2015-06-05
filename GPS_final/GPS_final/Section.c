/*!
* \file  Section.c
* \brief Defines new Section structures
* \author GPS team
* \date 13/12/2014
*/

#include <string.h>

#include "Section.h"
#include "Item.h"
#include "ItemList.h"


/*!
* \fn section * section_new(int id, type s_type)
* \brief Create a new section
* \param[in] id the section id
* \param[in] s_type the section type
* \return the new allocated section
*/
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

/*!
* \fn section * section_init(section * s_source)
* \brief Initializes all section parameters to zero, and the type to floor
* \param[in] *s_source the section to initialize
* \return the new allocated section
*/
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

	return s_source;
}


/*!
* \fn int section_delete(section * s_source)
* \brief Delete a section
* \param[in] *s_source pointer to the section
* \return EXIT_SUCCES if OK
*/
int section_delete(section * s_source)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	itemPointerList_delete(s_source->stock);
	free(s_source);
	return EXIT_SUCCESS;
}


/*!
* \fn int section_is_empty(section * s_source)
* \brief Tells the user if the section is empty or not
* \param[in] *s_source the section
* \return 1 if the list is empty, 0 otherwise
*/
int section_is_empty(section * s_source)
{
	return (s_source->nb_items == 0);
}

/*!
* \fn int section_has_stock(section * s_source)
* \brief Tells the user if the section has stock or not
* \param[in] *s_source the section
* \return 1 if the list has stock, 0 otherwise
*/
int section_has_stock(section * s_source)
{
	return(s_source->s_type == t_section || s_source->s_type == t_promo);
}


/*!
* \fn int section_set_id(section * s_source, int id)
* \brief Sets the section id to id
* \param[in] *s_source the section
* \param[in] id the id
* \return EXIT_SUCCES if OK
*/
int section_set_id(section * s_source, int id)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (id < 0)
		return EXIT_FAILURE;
	s_source->id = id;
	return EXIT_SUCCESS;
}


/*!
* \fn int section_set_type(section * s_source, type s_type)
* \brief Sets the section type to s_type
* \param[in] *s_source the section
* \param[in] s_type the type
* \return EXIT_SUCCES if OK
*/
int section_set_type(section * s_source, type s_type)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	if (s_type < 0)
		return EXIT_FAILURE;
	s_source->s_type = s_type;
	return EXIT_SUCCESS;
}


/*!
* \fn int section_set_pos(section * s_source, int x_pos, int y_pos)
* \brief Sets the section position to [x_pos,y_pos]
* \param[in] *s_source the section
* \param[in] x_pos the position on the x axis
* \param[in] y_pos the position on the y axis
* \return EXIT_SUCCES if OK
*/
int section_set_pos(section * s_source, int x_pos, int y_pos)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->pos.x = x_pos;
	s_source->pos.y = y_pos;
	return EXIT_SUCCESS;
}


/*!
* \fn int section_set_size(section * s_source, int x_size, int y_size)
* \brief Sets the section position to [x_size,y_size]
* \param[in] *s_source the section
* \param[in] x_size the size on the x axis
* \param[in] y_size the size on the y axis
* \return EXIT_SUCCES if OK
*/
int section_set_size(section * s_source, int x_size, int y_size)
{
	if (s_source == NULL)
		return EXIT_FAILURE;
	s_source->size.x = x_size;
	s_source->size.y = y_size;
	return EXIT_SUCCESS;
}


/*!
* \fn int section_add_item(section * s_source, item * item, int x_pos, int y_pos)
* \brief Add the item i to the section at the [x_pos,y_pos] position
* \param[in] *s_source the section
* \param[in] *item the item
* \param[in] x_pos the position on the x axis
* \param[in] y_pos the position on the y axis
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn int section_remove_item(item * item)
* \brief removes the item item from the list
* \param[in] *item the item
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn int section_get_id(section * s_source)
* \brief Get the id section of the section
* \param[in] *s_source the section
* \return the id section of the section
*/
int section_get_id(section * s_source)
{
	return s_source->id;
}


/*!
* \fn int section_get_type(section * s_source)
* \brief Get the type of the section
* \param[in] *s_source the section
* \return the type of the section
*/
type section_get_type(section * s_source)
{
	return s_source->s_type;
}


/*!
* \fn int section_get_type_string(section * s_source)
* \brief Get the type of the section as string
* \param[in] *s_source the section
* \return the type of the section as string
*/
char * section_get_type_string(section * s_source)
{
	return sec_type[s_source->s_type];
}

/*!
* \fn int section_get_pos(section * s_source)
* \brief Get the pos of the section
* \param[in] *s_source the section
* \return the pos of the section
*/
coord section_get_pos(section * s_source)
{
	return s_source->pos;
}


/*!
* \fn int section_get_size(section * s_source)
* \brief Get the size of the section
* \param[in] *s_source the section
* \return the size of the section
*/
coord section_get_size(section * s_source)
{
	return s_source->size;
}


/*!
* \fn int section_get_nb_items(section * s_source)
* \brief Get the number of items in the section
* \param[in] *s_source the section
* \return the number of items in the section
*/
int section_get_nb_items(section * s_source)
{
	return s_source->nb_items;
}


/*!
* \fn void section_print(section * s_source, gboolean minimal)
* \brief Prints the content of the section
* \param[in] *s_source the section
* \param[in] minimal prints the list in a minimal way if set at true
*/
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


/*!
* \fn void testSect(void)
* \brief Does tests on a section
*/
void testSect(void)
{
	typedef enum category_test{ c_none, fromage, pain, legumes_vert, alcool }category;
	char* item_category[] = { "none", "fromage", "pain", "legumes vert", "alcool" };

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