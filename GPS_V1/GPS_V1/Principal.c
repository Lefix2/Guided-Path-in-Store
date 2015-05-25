#include "Common.h"
#include "Item.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"
#include "Shopping.h"
#include "merchant.h"
#include "StoreImage.h"
#include "map.h"

#include "tests.h"

int principal(int argc, char *argv[])
{

	/* déclaration des variables */
	GtkWidget *window, *label, *h_box, *b_box, *v_box,*button, *button1, *button2, *button3, *button4, *button5;
	gchar *txtSchema = NULL;


	shopping *shopping;

	shopping = shopping_new(my_test_store_new());
	shopping->List = itemPointerList_new();

	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 0));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 1));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 2));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 3));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 4));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 5));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 6));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 7));
	itemPointerList_insert_sort(shopping->List, store_find_item_id(shopping->Store, 8));
	
	merchant_optimise_shopping(shopping);

	init_map(shopping);

	

	store_delete(shopping->Store);
	shopping_delete(shopping);
	return EXIT_SUCCESS;
}
