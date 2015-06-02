#include <string.h>

#include "Itemlist.h"
#include "Item.h"
#include "Section.h"

nodeItemList * nodeItemPointerList_new(item *i, nodeItemList *n)
{
	nodeItemList * newn;
	newn = (nodeItemList*)malloc(sizeof(nodeItemList));

	newn->itemPointerList_next = n;
	newn->i = i;

	return newn;
}

itemList * itemPointerList_new(void)
{
	itemList * newl;
	newl = (itemList *)malloc(sizeof(itemList));
	itemPointerList_init(newl);

	return newl;
}

int itemPointerList_delete(itemList * l)
{
	if (l == NULL)
		return EXIT_FAILURE;
	while (!itemPointerList_is_empty(l))
	{
		itemPointerList_delete_first(l);
	}
	free(l);
	return EXIT_SUCCESS;
}

void itemPointerList_init(itemList * l)
{
	l->first = l->last = l->current = NULL;
}

int itemPointerList_is_empty(itemList * l)
{
	return l->first == NULL;
}

int itemPointerList_is_on_first(itemList * l)
{
	return l->current == l->first;
}

int itemPointerList_is_on_last(itemList * l)
{
	return l->current == l->last;
}

int itemPointerList_is_out_of(itemList * l)
{
	return l->current == NULL;
}

void itemPointerList_set_on_first(itemList * l)
{
	l->current = l->first;
}

void itemPointerList_set_on_last(itemList * l)
{
	l->current = l->last;
}

void itemPointerList_next(itemList * l)
{
	if (l->current != NULL)
		l->current = l->current->itemPointerList_next;
}

void itemPointerList_print(itemList * l, gboolean minimal)
{
	char* header[] = { "----------------------------------------------------------------------------",
					   "|      id      |     name     |   category   |     cost     |  section id  |",
					   "|      |-------------------------------------------------------------------|",
					   "|      |*empty section                                                     |"
	};
	int i;

	if (minimal)
	{
		item * tmp;
		char buffer[MAX_ARRAY_OF_CHAR] = { 0 };
		const int tablen = strlen(header[0]);

		printf("%s\n", header[2]);
		if (itemPointerList_is_empty(l)){
			printf("%s\n",header[3]);
		}
		else
		{
			itemPointerList_set_on_first(l);

			strcat(buffer, "|      |");
			while (!itemPointerList_is_out_of(l))
			{
				tmp = l->current->i;
				if (strlen(buffer) + strlen(tmp->name) >= tablen)
				{
					while (strlen(buffer) < tablen-1)
					{
						strcat(buffer, " ");
					}
					strcat(buffer, "|\n");
					printf("%s", buffer);
					buffer[8] = 0; 
				}
				strcat(buffer, " ");
				strcat(buffer, tmp->name);
				strcat(buffer, ",");
				itemPointerList_next(l);
			}
			if (strlen(buffer) < tablen)
			{
				while (strlen(buffer) < tablen-1)
				{
					strcat(buffer, " ");
				}
				strcat(buffer, "|\n");
				printf("%s", buffer);
			}
		}
	}
	else
	{
		item * tmp;

		if (itemPointerList_is_empty(l)){
			printf("empty\n");
		}
		else{
			printf("\n");
			itemPointerList_set_on_first(l);

			for (i = 0; i < 2; i++)
			{
				printf("%s\n", header[i]);
			}
			printf("%s\n", header[0]);

			while (!itemPointerList_is_out_of(l))
			{
				tmp = l->current->i;
				if (item_has_section(tmp))
					printf("| %12d | %12s | %12d | %11.2fE | %12d |\n",
						item_get_id(tmp),
						item_get_name(tmp),
						item_get_category(tmp),
						item_get_cost(tmp),
						item_get_section(tmp)->id
						);
				else
					printf("| %12d | %12s | %12d | %11.2fE | %12s |\n",
						item_get_id(tmp),
						item_get_name(tmp),
						item_get_category(tmp),
						item_get_cost(tmp),
						"No section"
						);
				itemPointerList_next(l);
			}
			printf("%s\n", header[0]);
			printf("\n");
		}
	}
}

int itemPointerList_insert_first(itemList * l, item * i)
{
	nodeItemList* n = nodeItemPointerList_new(i, l->first);
	if (n == NULL)
		return EXIT_FAILURE;

	if (itemPointerList_is_empty(l))
	{
		l->last = l->current = n;
	}
	l->first = n;
	return EXIT_SUCCESS;
}

int itemPointerList_insert_last(itemList * l, item * i)
{
	nodeItemList* n = nodeItemPointerList_new(i, NULL);
	if (n == NULL)
		return EXIT_FAILURE;

	if (itemPointerList_is_empty(l))
	{
		l->first = l->current = n;
	}
	else
		l->last->itemPointerList_next = n;
	l->last = n;
	return EXIT_SUCCESS;
}

int itemPointerList_insert_before_current(itemList * l, item * i)
{
	if (itemPointerList_is_empty(l) || itemPointerList_is_on_first(l))
	{
		return itemPointerList_insert_first(l, i);
	}
	else if (itemPointerList_is_out_of(l))
	{
		printf("error: trying to write out of the itemList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeItemList* n = nodeItemPointerList_new(i, l->current);
		nodeItemList* tmp = l->current;
		itemPointerList_set_on_first(l);
		while (l->current->itemPointerList_next != tmp)
		{
			itemPointerList_next(l);
		}
		l->current->itemPointerList_next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int itemPointerList_insert_after_current(itemList * l, item * i)
{

	if (itemPointerList_is_empty(l))
	{
		return itemPointerList_insert_first(l, i);
	}
	else if (itemPointerList_is_out_of(l))
	{
		printf("error: trying to write out of the itemList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeItemList* n = nodeItemPointerList_new(i, l->current->itemPointerList_next);
		l->current->itemPointerList_next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int itemPointerList_insert_sort(itemList * l, item * i)
{
	int ret;
	if (i == NULL)
	{
		printf("Trying to insert a null pointer in itemPointerList!\n");
		return 0;
	}
	nodeItemList * tmp = l->current;
	if (itemPointerList_is_empty(l))
	{
		return itemPointerList_insert_first(l, i);
	}

	itemPointerList_set_on_first(l);

	do
	{
		if (l->current->i->id <= i->id)
			itemPointerList_next(l);
		else
		{
			ret = itemPointerList_insert_before_current(l, i);
			l->current = tmp;
			return ret;
		}
	} while (!itemPointerList_is_out_of(l));

	l->current = tmp;
	return itemPointerList_insert_last(l, i);
}

item * itemPointerList_delete_first(itemList * l)
{
	if (itemPointerList_is_empty(l)){
		printf("error: trying to delete node in an itemPointerList_is_empty itemList in %s\n", __FUNCTION__);
		return NULL;
	}

	else{
		nodeItemList * n = l->first;
		item * ret = n->i;
		l->first = n->itemPointerList_next;
		if (l->first == NULL)
			itemPointerList_init(l);
		itemPointerList_set_on_first(l);
		free((nodeItemList*)n);
		return ret;
	}
	return NULL;
}

item * itemPointerList_delete_last(itemList * l)
{
	if (itemPointerList_is_empty(l)){
		printf("error: trying to delete node in an itemPointerList_is_empty itemList in %s\n", __FUNCTION__);
		return NULL;
	}
	else if (l->first == l->last)
	{
		return itemPointerList_delete_first(l);
	}
	else{
		nodeItemList* n = l->last;
		item * ret = n->i;
		itemPointerList_set_on_first(l);
		while (l->current->itemPointerList_next != n)
		{
			itemPointerList_next(l);
		}
		l->last = l->current;
		l->last->itemPointerList_next = NULL;
		free((void*)n);
		return ret;
	}
	return NULL;
}

item * itemPointerList_delete_current(itemList * l)
{
	if (itemPointerList_is_empty(l)){
		printf("error: trying to delete node in an itemPointerList_is_empty itemList in %s\n", __FUNCTION__);
		return NULL;
	}
	if (itemPointerList_is_on_first(l))
	{
		return itemPointerList_delete_first(l);
	}
	else if (itemPointerList_is_on_last(l))
	{
		return itemPointerList_delete_last(l);
	}
	else
	{
		nodeItemList* n = l->current;
		item * ret = n->i;
		itemPointerList_set_on_first(l);
		while (l->current->itemPointerList_next != n)
		{
			itemPointerList_next(l);
		}
		l->current->itemPointerList_next = n->itemPointerList_next;

		free((void*)n);
		return ret;
	}
	return NULL;
}

item * itemPointerList_delete_single(itemList * l, item * i)
{
	item * tmp = itemPointerList_find(l, i);
	if (tmp != NULL)
		itemPointerList_delete_current(l);
	return tmp;
}

item * itemPointerList_get_first(itemList * l)
{
	return l->first->i;
}

item * itemPointerList_get_current(itemList * l)
{
	return l->current->i;
}

item * itemPointerList_get_last(itemList * l)
{
	return l->last->i;
}

item * itemPointerList_find(itemList * l, item * i)
{
	itemPointerList_set_on_first(l);
	while (l->current != NULL)
	{
		if (l->current->i == i)
			return l->current->i;
		itemPointerList_next(l);
	}
	return NULL;
}

item * itemPointerList_find_id(itemList * l, int id)
{
	itemPointerList_set_on_first(l);
	while (l->current != NULL)
	{
		if (l->current->i->id == id)
			return l->current->i;
		itemPointerList_next(l);
	}
	return NULL;
}
