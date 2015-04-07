#include <string.h>

#include "Itemlist.h"
#include "Item.h"
#include "Section.h"

nodeItemList * newNodeItemPointer(item *i, nodeItemList *n)
{
	nodeItemList * newn;
	newn = (nodeItemList*)malloc(sizeof(nodeItemList));

	newn->nextItemPointer = n;
	newn->i = i;

	return newn;
}

itemList * newItemPointerList(void)
{
	itemList * newl;
	newl = (itemList *)malloc(sizeof(itemList));
	initItemPointerList(newl);

	return newl;
}

int deleteItemPointerList(itemList * l)
{
	if (l == NULL)
		return EXIT_FAILURE;
	while (!emptyItemPointerList(l))
	{
		deleteFirstItemPointer(l);
	}
	free(l);
	return EXIT_SUCCESS;
}

void initItemPointerList(itemList * l)
{
	l->firstItemPointer = l->lastItemPointer = l->currentItem = NULL;
}

int emptyItemPointerList(itemList * l)
{
	return l->firstItemPointer == NULL;
}

int firstItemPointer(itemList * l)
{
	return l->currentItem == l->firstItemPointer;
}

int lastItemPointer(itemList * l)
{
	return l->currentItem == l->lastItemPointer;
}

int outOfItemPointerList(itemList * l)
{
	return l->currentItem == NULL;
}

void setOnFirstItemPointer(itemList * l)
{
	l->currentItem = l->firstItemPointer;
}

void setOnLastItemPointer(itemList * l)
{
	l->currentItem = l->lastItemPointer;
}

void nextItemPointer(itemList * l)
{
	l->currentItem = l->currentItem->nextItemPointer;
}

void printItemList(itemList * l, gboolean minimal)
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
		if (emptyItemPointerList(l)){
			printf("%s\n",header[3]);
		}
		else
		{
			setOnFirstItemPointer(l);

			strcat(buffer, "|      |");
			while (!outOfItemPointerList(l))
			{
				tmp = l->currentItem->i;
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
				nextItemPointer(l);
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

		if (emptyItemPointerList(l)){
			printf("empty\n");
		}
		else{
			printf("\n");
			setOnFirstItemPointer(l);

			for (i = 0; i < 2; i++)
			{
				printf("%s\n", header[i]);
			}
			printf("%s\n", header[0]);

			while (!outOfItemPointerList(l))
			{
				tmp = l->currentItem->i;
				if (Item_HasSection(tmp))
					printf("| %12d | %12s | %12s | %11.2fE | %12d |\n",
						Item_getId(tmp),
						Item_getName(tmp),
						Item_getCategoryString(tmp),
						Item_getCost(tmp),
						Item_getSection(tmp)->id
						);
				else
					printf("| %12d | %12s | %12s | %11.2fE | %12s |\n",
						Item_getId(tmp),
						Item_getName(tmp),
						Item_getCategoryString(tmp),
						Item_getCost(tmp),
						"No section"
						);
				nextItemPointer(l);
			}
			printf("%s\n", header[0]);
			printf("\n");
		}
	}
}

int insertFirstItemPointer(itemList * l, item * i)
{
	nodeItemList* n = newNodeItemPointer(i, l->firstItemPointer);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptyItemPointerList(l))
	{
		l->lastItemPointer = l->currentItem = n;
	}
	l->firstItemPointer = n;
	return EXIT_SUCCESS;
}

int insertlastItemPointer(itemList * l, item * i)
{
	nodeItemList* n = newNodeItemPointer(i, NULL);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptyItemPointerList(l))
	{
		l->firstItemPointer = l->currentItem = n;
	}
	else
		l->lastItemPointer->nextItemPointer = n;
	l->lastItemPointer = n;
	return EXIT_SUCCESS;
}

int insertBeforeCurrentItemPointer(itemList * l, item * i)
{
	if (emptyItemPointerList(l) || firstItemPointer(l))
	{
		return insertFirstItemPointer(l, i);
	}
	else if (outOfItemPointerList(l))
	{
		printf("error: trying to write out of the itemList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeItemList* n = newNodeItemPointer(i, l->currentItem);
		nodeItemList* tmp = l->currentItem;
		setOnFirstItemPointer(l);
		while (l->currentItem->nextItemPointer != tmp)
		{
			nextItemPointer(l);
		}
		l->currentItem->nextItemPointer = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int insertAfterCurrentItemPointer(itemList * l, item * i)
{

	if (emptyItemPointerList(l))
	{
		return insertFirstItemPointer(l, i);
	}
	else if (outOfItemPointerList(l))
	{
		printf("error: trying to write out of the itemList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeItemList* n = newNodeItemPointer(i, l->currentItem->nextItemPointer);
		l->currentItem->nextItemPointer = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int insertSortItemPointer(itemList * l, item * i)
{
	nodeItemList * tmp = l->currentItem;
	if (emptyItemPointerList(l))
	{
		return insertFirstItemPointer(l, i);
	}

	setOnFirstItemPointer(l);

	do
	{
		if (l->currentItem->i->id <= i->id)
			nextItemPointer(l);
		else
		{
			insertBeforeCurrentItemPointer(l, i);
			setOnFirstItemPointer(l);
			break;
		}
	} while (!outOfItemPointerList(l));
	if (outOfItemPointerList(l))
		insertlastItemPointer(l, i);

	l->currentItem = tmp;
	return EXIT_SUCCESS;
}

item * deleteFirstItemPointer(itemList * l)
{
	if (emptyItemPointerList(l)){
		printf("error: trying to delete node in an emptyItemPointerList itemList in %s\n", __FUNCTION__);
		return NULL;
	}

	else{
		nodeItemList * n = l->firstItemPointer;
		item * ret = n->i;
		l->firstItemPointer = n->nextItemPointer;
		if (l->firstItemPointer == NULL)
			initItemPointerList(l);
		setOnFirstItemPointer(l);
		free((nodeItemList*)n);
		return ret;
	}
	return NULL;
}

item * deleteLastItemPointer(itemList * l)
{
	if (emptyItemPointerList(l)){
		printf("error: trying to delete node in an emptyItemPointerList itemList in %s\n", __FUNCTION__);
		return NULL;
	}
	else if (l->firstItemPointer == l->lastItemPointer)
	{
		return deleteFirstItemPointer(l);
	}
	else{
		nodeItemList* n = l->lastItemPointer;
		item * ret = n->i;
		setOnFirstItemPointer(l);
		while (l->currentItem->nextItemPointer != n)
		{
			nextItemPointer(l);
		}
		l->lastItemPointer = l->currentItem;
		free((void*)n);
		return ret;
	}
	return NULL;
}

item * deleteCurrentItemPointer(itemList * l)
{
	if (emptyItemPointerList(l)){
		printf("error: trying to delete node in an emptyItemPointerList itemList in %s\n", __FUNCTION__);
		return NULL;
	}
	if (firstItemPointer(l))
	{
		return deleteFirstItemPointer(l);
	}
	else if (lastItemPointer(l))
	{
		return deleteLastItemPointer(l);
	}
	else
	{
		nodeItemList* n = l->currentItem;
		item * ret = n->i;
		setOnFirstItemPointer(l);
		while (l->currentItem->nextItemPointer != n)
		{
			nextItemPointer(l);
		}
		l->currentItem->nextItemPointer = n->nextItemPointer;

		free((void*)n);
		return ret;
	}
	return NULL;
}

item * deleteSingleItemPointer(itemList * l, item * i)
{
	item * tmp = findItemPointer(l, i);
	if (tmp != NULL)
		deleteCurrentItemPointer(l);
	return tmp;
}

item * getCurrentItemPointer(itemList * l)
{
	return l->currentItem->i;
}

item * findItemPointer(itemList * l, item * i)
{
	setOnFirstItemPointer(l);
	while (l->currentItem != NULL)
	{
		if (l->currentItem->i == i)
			return l->currentItem->i;
		nextItemPointer(l);
	}
	return NULL;
}

item * findItemPointerId(itemList * l, int id)
{
	setOnFirstItemPointer(l);
	while (l->currentItem != NULL)
	{
		if (l->currentItem->i->id == id)
			return l->currentItem->i;
		nextItemPointer(l);
	}
	return NULL;
}
