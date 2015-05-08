#include "merchant.h"
#include "Astar.h"
#include "Shopping.h"
#include "Store.h"
#include "Section.h"
#include "SectionList.h"
#include "Item.h"
#include "ItemList.h"

int merchant_connect_paths(shopping *shopping)
{
	//to enter this function merchant algorithm must be done

	//first and last coordonate of the shopping
	coord start, end;
	sectionList *sections = store_get_allocatedSections(shopping->Store);

	//calculate all paths
	item *current, *old;
	itemList *list = shopping->List;
	coord c1, c2;
	itemPointerList_set_on_first(list);

	//first path
	current = itemPointerList_get_current(list);
	c1 = add_coord(item_get_pos(shopping->start), section_get_pos(item_get_section(shopping->start)));
	c2 = add_coord(item_get_pos(current), section_get_pos(item_get_section(current)));
	astar(shopping->Store, c1, c2, current->pathTo);
	old = current;
	itemPointerList_next(list);

	//other paths
	while (!itemPointerList_is_out_of(list))
	{
		current = itemPointerList_get_current(list);
		c1 = add_coord(item_get_pos(old), section_get_pos(item_get_section(old)));
		c2 = add_coord(item_get_pos(current), section_get_pos(item_get_section(current)));
		astar(shopping->Store, c1, c2, current->pathTo);
		old = current;
		itemPointerList_next(list);
	}

	//last path
	c1 = add_coord(item_get_pos(old), section_get_pos(item_get_section(old)));
	c2 = add_coord(item_get_pos(shopping->end), section_get_pos(item_get_section(shopping->end)));
	astar(shopping->Store, c1, c2, shopping->end->pathTo);

	return EXIT_SUCCESS;

}

int merchant_optimise_shopping(shopping *shopping)
{
	/*---------------------------------------------------------------*/
	/***************initialize start and end position*****************/
	/*---------------------------------------------------------------*/

	sectionList *sections = store_get_allocatedSections(shopping->Store);
	section *tmp_sec;
	coord tmp_size;

	//start
	sectionPointerList_set_on_first(sections);
	while (section_get_type(sectionPointerList_get_current(sections)) != t_entrance)
	{
		sectionPointerList_next(sections);
	}
	tmp_sec = sectionPointerList_get_current(sections);
	tmp_size = section_get_size(tmp_sec);
	tmp_size.x /= 2;
	tmp_size.y /= 2;

	item_set_section(shopping->start, tmp_sec);
	item_set_pos(shopping->start, tmp_size.x, tmp_size.y);

	//end
	sectionPointerList_set_on_first(sections);
	while (section_get_type(sectionPointerList_get_current(sections)) != t_checkout)
	{
		sectionPointerList_next(sections);
	}
	tmp_sec = sectionPointerList_get_current(sections);
	tmp_size = section_get_size(tmp_sec);
	tmp_size.x /= 2;
	tmp_size.y /= 2;

	item_set_section(shopping->end, tmp_sec);
	item_set_pos(shopping->end, tmp_size.x, tmp_size.y);


	/*---------------------------------------------------------------*/
	/**********************get all paths******************************/
	/*---------------------------------------------------------------*/
	//creating a temporary list to work on
	itemList *tmp_list;
	tmp_list = itemPointerList_new();

	itemPointerList_set_on_first(shopping->List);
	while (!itemPointerList_is_out_of(shopping->List))
	{
		itemPointerList_insert_last(tmp_list, itemPointerList_get_current(shopping->List));
		itemPointerList_next(shopping->List);
	}
	//adding start and end to the list
	itemPointerList_insert_first(tmp_list, shopping->start);
	itemPointerList_insert_last(tmp_list, shopping->end);

	//counting the number of item in the list
	int nbItems = 0;
	int i, s, e;
	itemPointerList_set_on_first(tmp_list);
	while (!itemPointerList_is_out_of(tmp_list))
	{
		itemPointerList_next(tmp_list);
		nbItems++;
	}

	//initializing a tab wich will contain all distance between each item
	int ** pathLenghts = (int**)calloc(nbItems, sizeof(int*));
	for (i = 0; i < nbItems; i++)
	{
		*(pathLenghts + i) = (int*)calloc(nbItems, sizeof(int));
	}

	//set all pathlengt of each item with itself to infinity
	for (i = 0; i < nbItems; i++)
	{
		pathLenghts[i][i] = MY_INFINITY;
	}

	coord start, end;
	item *currentItem;
	for (s = 0; s < nbItems-1; s++)
	{
		//set current item of the list on the s'th position
		itemPointerList_set_on_first(tmp_list);
		for (i = 0; i < s;i++)
			itemPointerList_next(tmp_list);

		//get the start point
		currentItem = itemPointerList_get_current(tmp_list);
		start = add_coord(item_get_pos(currentItem), section_get_pos(item_get_section(currentItem)));
		for (e = s+1; e < nbItems; e++)
		{
			itemPointerList_next(tmp_list);//set current item of the list on the s+e'th position
			currentItem = itemPointerList_get_current(tmp_list);
			end = add_coord(item_get_pos(currentItem), section_get_pos(item_get_section(currentItem)));
			pathLenghts[s][e] = pathLenghts[e][s] = astar(shopping->Store, start, end, NULL);
		}
	}
	merchant_connect_paths(shopping);
}