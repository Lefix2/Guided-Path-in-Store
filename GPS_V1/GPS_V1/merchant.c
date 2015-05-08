#include "merchant.h"
#include "Astar.h"
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

	sectionPointerList_set_on_first(sections);
	while (section_get_type(sectionPointerList_get_current(sections)) != t_entrance)
	{
		sectionPointerList_next(sections);
	}
	start = section_get_pos(sectionPointerList_get_current(sections));

	sectionPointerList_set_on_first(sections);
	while (section_get_type(sectionPointerList_get_current(sections)) != t_checkout)
	{
		sectionPointerList_next(sections);
	}
	end = section_get_pos(sectionPointerList_get_current(sections));

	//calculate all paths
	item *current, *old;
	itemList *list = shopping->List;
	coord c1, c2;
	itemPointerList_set_on_first(list);

	//first path
	current = itemPointerList_get_current(list);
	c1 = start;
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
	return EXIT_SUCCESS;

}