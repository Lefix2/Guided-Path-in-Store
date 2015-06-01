#include "Shopping.h"
#include "Store.h"
#include "ItemList.h"

shopping *shopping_new()
{
	shopping *s_new;
	s_new = (shopping*)malloc(sizeof(shopping));

	s_new->Store = NULL;
	s_new->start = item_new(-1, c_none, "start");
	s_new->end = item_new(-1, c_none, "end");
	s_new->List = itemPointerList_new();
	return s_new;
}

int shopping_delete(shopping *shopping)
{
	if (shopping == NULL)
		return EXIT_FAILURE;
	if (shopping->Store != NULL)
		store_delete(shopping->Store);
	if (shopping->List != NULL)
		itemPointerList_delete(shopping->List);
	item_delete(shopping->start);
	item_delete(shopping->end);
	free(shopping);
}

int shopping_set_store(shopping * shopping, store * store)
{
	if (shopping->Store != NULL)
	{
		printf("Unloading store %s ...\n", store_get_name(shopping->Store));
		store_delete(shopping->Store);
	}
	shopping->Store = store;
	if (shopping->Store != NULL)
		printf("Store %s Loaded\n", store_get_name(shopping->Store));
	return EXIT_SUCCESS;
}

int shopping_set_list(shopping *shopping, itemList *list)
{
	if (shopping->List != NULL)
		itemPointerList_delete(shopping->List);
	shopping->List = list;
	return EXIT_SUCCESS;
}

store *shopping_get_store(shopping *shopping)
{
	return shopping->Store;
}

itemList *shopping_get_list(shopping *shopping)
{
	return shopping->List;
}