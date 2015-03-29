#include "Itemlist.h"
#include "Item.h"
#include "Section.h"

nodeItemList * newNodeItemList(item *i, nodeItemList *n)
{
	nodeItemList * newn;
	newn = (nodeItemList*)malloc(sizeof(nodeItemList));

	newn->nextItem = n;
	newn->i = i;

	return newn;
}

itemList * newItemList(void)
{
	itemList * newl;
	newl = (itemList *)malloc(sizeof(itemList));
	initItemList(newl);

	return newl;
}

int deleteItemList(itemList * l)
{
	if (l == NULL)
		return EXIT_FAILURE;
	while (!emptyItemList(l))
	{
		deletfirstItem(l);
	}
	free(l);
	return EXIT_SUCCESS;
}

void initItemList(itemList * l)
{
	l->firstItem = l->lastItem = l->current = NULL;
}

int emptyItemList(itemList * l)
{
	return l->firstItem == NULL;
}

int firstItem(itemList * l)
{
	return l->current == l->firstItem;
}

int lastItem(itemList * l)
{
	return l->current == l->lastItem;
}

int outOfItemList(itemList * l)
{
	return l->current == NULL;
}

void setOnfirstItem(itemList * l)
{
	l->current = l->firstItem;
}

void setOnlastItem(itemList * l)
{
	l->current = l->lastItem;
}

void nextItem(itemList * l)
{
	l->current = l->current->nextItem;
}

item * getCurrentItem(itemList * l)
{
	return l->current->i;
}

void printItemList(itemList * l)
{
	char* header[] = { "----------------------------------------------------------------------------",
					   "|      id      |     name     |   category   |     cost     |  section id  |" };
	int i;
	item * tmp;

	printf("Stock : ");
	if (emptyItemList(l)){
		printf("empty\n");
	}
	else{
		printf("\n");
		setOnfirstItem(l);

		for (i = 0; i < 2; i++)
		{
			printf("%s\n", header[i]);
		}
		printf("%s\n", header[0]);

		while (!outOfItemList(l))
		{
			tmp = l->current->i;
			printf("| %12d | %12s | %12s | %11.2fE | %12d |\n",Item_getId(tmp),
															   Item_getName(tmp),
															   Item_getCategoryString(tmp),
															   Item_getCost(tmp),
															   Item_getSection(tmp)->id
			);
			nextItem(l);
		}
		printf("%s\n", header[0]);
		printf("\n");
	}

}

int insertfirstItem(itemList * l, item * i)
{
	nodeItemList* n = newNodeItemList(i, l->firstItem);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptyItemList(l))
	{
		l->lastItem = l->current = n;
	}
	l->firstItem = n;
	return EXIT_SUCCESS;
}

int insertlastItem(itemList * l, item * i)
{
	nodeItemList* n = newNodeItemList(i, NULL);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptyItemList(l))
	{
		l->firstItem = l->current = n;
	}
	else
		l->lastItem->nextItem = n;
	l->lastItem = n;
	return EXIT_SUCCESS;
}

int insertBeforeCurrentItem(itemList * l, item * i)
{
	nodeItemList* n;
	n = newNodeItemList(i, l->current);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptyItemList(l))
	{
		l->lastItem = l->current = l->lastItem = n;
	}
	else if (firstItem(l))
	{
		insertfirstItem(l, i);
	}
	else if (outOfItemList(l))
	{
		printf("error: trying to write out of the itemList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeItemList* tmp = l->current;
		setOnfirstItem(l);
		while (l->current->nextItem != tmp)
		{
			nextItem(l);
		}
		l->current->nextItem = n;
	}
	return EXIT_SUCCESS;
}

int insertAfterCurrentItem(itemList * l, item * i)
{
	nodeItemList* n;
	n = newNodeItemList(i, l->current->nextItem);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptyItemList(l))
	{
		l->lastItem = l->current = l->lastItem = n;
	}
	else if (outOfItemList(l))
	{
		printf("error: trying to write out of the itemList!");
		return EXIT_FAILURE;
	}
	l->current->nextItem = n;
	return EXIT_SUCCESS;
}

void deletfirstItem(itemList * l)
{
	if (emptyItemList(l)){
		printf("error: trying to delete node in an emptyItemList itemList in %s\n", __FUNCTION__);
	}

	else{
		nodeItemList * n = l->firstItem;
		l->firstItem = n->nextItem;
		if (l->firstItem == NULL)
			initItemList(l);
		free((void*)n);
	}
}

void deletelastItem(itemList * l)
{
	if (emptyItemList(l)){
		printf("error: trying to delete node in an emptyItemList itemList in %s\n", __FUNCTION__);
	}

	else{
		nodeItemList* n = l->lastItem;
		setOnfirstItem(l);
		do
		{
			l->current = l->current->nextItem;
		} while (l->current->nextItem != n);
		l->lastItem = l->current;

		if (l->lastItem == NULL)
			initItemList(l);
		free((void*)n);
	}

}

void deleteCurrentItem(itemList * l)
{
	if (emptyItemList(l)){
		printf("error: trying to delete node in an emptyItemList itemList in %s\n", __FUNCTION__);
	}


	nodeItemList* n = l->current;
	setOnfirstItem(l);

	do
	{
		nextItem(l);
	} while (l->current->nextItem != n);
	l->current->nextItem = n->nextItem;

	if (l->current == NULL)
		initItemList(l);
	free((void*)n);
}

int findItem(itemList * l, item * i)
{
	setOnfirstItem(l);
	while (l->current != l->lastItem)
	{
		if (l->current->i == i)
			return EXIT_SUCCESS;
		nextItem(l);
	}

	return EXIT_FAILURE;
}

int insertSortItem(itemList * l, item * i)
{
	nodeItemList * tmp = l->current;
	if (emptyItemList(l))
	{
		insertfirstItem(l, i);
		return EXIT_SUCCESS;
	}

	setOnfirstItem(l);

	do
	{
		if (l->current->i->id <= i->id)
			nextItem(l);
		else
		{
			insertBeforeCurrentItem(l, i);
			setOnfirstItem(l);
			break;
		}
	} while (!outOfItemList(l));
	if (outOfItemList(l))
		insertlastItem(l, i);

	l->current = tmp;
	return EXIT_SUCCESS;
}