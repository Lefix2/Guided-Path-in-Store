#ifndef TEST_H
#define TEST_H

#include "Common.h"
#include "Item.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"
#include "StoreImage.h"
#include <time.h>

store *my_test_store_new()
{
	int magsizex = 50;//min 28
	int magsizey = 48;//min 40
	int i;

	GError **error = NULL;
	GdkPixbuf *sprites = gdk_pixbuf_new_from_file("ressources\\Images\\sprites.png", error);


	store * sttest = store_new(0, "Carrefour - rennes", magsizex, magsizey);

	int id = 0;
	int x,y;

	int entrancesize = 7;
	int checkoutsize = 10;

	int xsectionlenght = 4*magsizex / 15 ;
	int ysectionlenght = 4*magsizey / 15;

	int xsection1start = 1;
	int xsection2start = 1 * magsizex / 3 + 1;
	int xsection3start = 2 * magsizex / 3 + 1;

	int ysection1start = 1;
	int ysection2start = magsizey / 2 + 1;

	store_set_sprites(sttest, sprites);

	store_add_section(sttest, id++, t_wall, 0, 0, 1, magsizey);
	store_add_section(sttest, id++, t_wall, magsizex - 1, 0, 1, magsizey);
	store_add_section(sttest, id++, t_wall, 1, 0, magsizex - 2, 1);
	store_add_section(sttest, id++, t_wall, 1, magsizey - 2, 2, 2);
	store_add_section(sttest, id++, t_checkout, 3, magsizey - 3, checkoutsize, 3);
	store_add_section(sttest, id++, t_wall, checkoutsize + 3, magsizey - 2, magsizex - entrancesize - 20, 2);
	store_add_section(sttest, id++, t_entrance, magsizex - entrancesize - 7, magsizey - 3, entrancesize, 3);
	store_add_section(sttest, id++, t_wall, magsizex - entrancesize , magsizey - 2, 6, 2);

	for (x = 2; x < magsizex / 3 - 4; x += 5)
	{
		for (y = 2; y < 2 * magsizey / 3 - 3; y += 6)
		{
			store_add_section(sttest, id++, t_section, x, y, 3, 4);
		}
		store_add_section(sttest, id++, t_section, x, 2 * magsizey / 3, 2, ysectionlenght);
	}

	for (x = magsizex / 3 + 1; x < 2*magsizex / 3 - 4; x += 3)
	{
		store_add_section(sttest, id++, t_section, x, 1, 2, ysectionlenght);
		store_add_section(sttest, id++, t_promo, x, magsizey / 3 + 1, 2, ysectionlenght);
		store_add_section(sttest, id++, t_section, x, 2*magsizey / 3 + 1, 2, ysectionlenght);
	}

	for (y = 3; y < magsizey-5; y += 3)
	{
		store_add_section(sttest, id++, t_section, xsection3start, y, xsectionlenght, 2);
	}


	store_add_item(sttest, 0, legumes_vert, "haricot");
	store_add_item(sttest, 1, alcool, "desperado");
	store_add_item(sttest, 2, fromage, "gruyere");
	store_add_item(sttest, 3, pain, "brioche");
	store_add_item(sttest, 4, alcool, "vin");
	store_add_item(sttest, 5, legumes_vert, "petits poids");
	store_add_item(sttest, 6, fromage, "gouda");
	store_add_item(sttest, 7, pain, "biscottes");
	store_add_item(sttest, 8, legumes_vert, "asperges");

	
	srand(time(NULL));
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 0), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 1), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 2), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 3), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 4), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 5), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 6), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 7), 1, 0);
	section_add_item(store_find_section_id(sttest, 8 + rand() % (id - 8)), store_find_item_id(sttest, 8), 1, 0);

	return sttest;
}

#endif // !TEST_H
