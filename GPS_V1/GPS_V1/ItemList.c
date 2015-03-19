#include <stdio.h>
#include <stdlib.h>

#include "Itemlist.h"

char* item_category[] = { "none", "fromage", "pain", "legumes vert" };

nodeList * newNodeList(item *i, nodeList *n)
{
	nodeList * newn;
	newn = (nodeList*)malloc(sizeof(nodeList));

	newn->next = n;
	newn->i = i;

	return newn;
}

void initList(list * l)
{
	l->first = l->last = l->current = NULL;
}

int empty(list * l)
{
	return l->first == NULL;
}

int first(list * l)
{
	return l->current == l->first;
}

int last(list * l)
{
	return l->current == l->last;
}

int outOfList(list * l)
{
	return l->current == NULL;
}

void setOnFirst(list * l)
{
	l->current = l->first;
}

void setOnLast(list * l)
{
	l->current = l->last;
}

void next(list * l)
{
	l->current = l->current->next;
}

item * getCurrentItem(list * l)
{
	return l->current->i;
}

void printList(list * l)
{
	char* header[] = { "----------------------------------------------------------------------------",
					   "|      id      |     name     |   category   |     cost     |  section id  |" };
	int i;

	printf("***** Stock : ");
	if (empty(l)){
		printf("vide\n");
	}
	else{
		printf("\n");
		setOnFirst(l);

		for (i = 0; i < 2; i++)
		{
			printf("%s\n", header[i]);
		}
		printf("%s\n", header[0]);

		while (!outOfList(l))
		{
			printf("| %12d | %12s | %12s | %11.2fE | %12d |\n", l->current->i->id, l->current->i->name, item_category[l->current->i->category], l->current->i->cost, l->current->i->i_section->id);
			next(l);
		}
		printf("\n");
	}

}

int insertFirst(list * l, item * i)
{
	nodeList* n = newNodeList(i, l->first);
	if (n == NULL)
		return 0;

	if (empty(l))
	{
		l->last = l->current = n;
	}
	l->first = n;
	return 1;
}

int insertLast(list * l, item * i)
{
	nodeList* n = newNodeList(i, NULL);
	if (n == NULL)
		return 0;

	if (empty(l))
	{
		l->first = l->current = n;
	}
	else
		l->last->next = n;
	l->last = n;
	return 1;
}

int insertBeforeCurrent(list * l, item * i)
{
	nodeList* n;
	n = newNodeList(i, l->current);
	if (n == NULL)
		return 0;

	if (empty(l))
	{
		l->last = l->current = l->last = n;
	}
	else if (first(l))
	{
		insertFirst(l, i);
	}
	else if (outOfList(l))
	{
		printf("error: trying to write out of the list!");
		return 0;
	}
	else
	{
		nodeList* tmp = l->current;
		setOnFirst(l);
		while (l->current->next != tmp)
		{
			next(l);
		}
		l->current->next = n;
	}
	return 1;
}

int insertAfterCurrent(list * l, item * i)
{
	nodeList* n;
	n = newNodeList(i, l->current->next);
	if (n == NULL)
		return 0;

	if (empty(l))
	{
		l->last = l->current = l->last = n;
	}
	else if (outOfList(l))
	{
		printf("error: trying to write out of the list!");
		return 0;
	}
	l->current->next = n;
	return 1;
}

void deletFirst(list * l)
{
	if (empty(l)){
		printf("error: trying to delete node in an empty list in %s\n", __FUNCTION__);
	}

	else{
		nodeList * n = l->first;
		l->first = n->next;
		if (l->first == NULL)
			initList(l);
		free((void*)n);
	}
}

void deleteLast(list * l)
{
	if (empty(l)){
		printf("error: trying to delete node in an empty list in %s\n", __FUNCTION__);
	}

	else{
		nodeList* n = l->last;
		setOnFirst(l);
		do
		{
			l->current = l->current->next;
		} while (l->current->next != n);
		l->last = l->current;

		if (l->last == NULL)
			initList(l);
		free((void*)n);
	}

}

void deleteCurrent(list * l)
{
	if (empty(l)){
		printf("error: trying to delete node in an empty list in %s\n", __FUNCTION__);
	}


	nodeList* n = l->current;
	setOnFirst(l);

	do
	{
		next(l);
	} while (l->current->next != n);
	l->current->next = n->next;

	if (l->current == NULL)
		initList(l);
	free((void*)n);
}

int find(list * l, item * i)
{
	setOnFirst(l);
	while (l->current != l->last)
	{
		if (l->current->i == i)
			return 1;
		next(l);
	}

	return 0;
}

int insertSort(list * l, item * i)
{
	nodeList * tmp = l->current;
	if (empty(l))
	{
		insertFirst(l, i);
		return 1;
	}

	setOnFirst(l);

	do
	{
		if (l->current->i->id <= i->id)
			next(l);
		else
		{
			insertBeforeCurrent(l, i);
			setOnFirst(l);
			break;
		}
	} while (!outOfList(l));
	if (outOfList(l))
		insertLast(l, i);

	l->current = tmp;
	return 1;
}