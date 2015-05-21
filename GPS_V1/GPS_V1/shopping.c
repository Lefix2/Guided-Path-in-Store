#include "Shopping.h"

shopping *shopping_new(store *Store)
{
	shopping *s_new;
	s_new = (shopping*)malloc(sizeof(shopping));

	s_new->Store = Store;
	s_new->start = item_new(-1, c_none, "start");
	s_new->end = item_new(-1, c_none, "end");
	s_new->List = NULL;
}

int shopping_delete(shopping *shopping)
{
	if (shopping == NULL)
		return EXIT_FAILURE;
	item_delete(shopping->start);
	item_delete(shopping->end);
	free(shopping);
}