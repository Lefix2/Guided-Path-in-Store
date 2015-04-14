#include <string.h>

#include "AstarList.h"
#include "Astar.h"

nodeAstar * nodeAstar_new(coord pos, nodeAstar *parent)
{
	nodeAstar * newn;
	newn = (nodeAstar*)malloc(sizeof(nodeAstar));

	newn->pos = pos;
	newn->h = 0;
	newn->g = 0;
	newn->f = 0;
	newn->parent = parent;

	return newn;
}

astarList * astarList_new(void)
{
	astarList * newl;
	newl = (astarList *)malloc(sizeof(astarList));
	astarList_init(newl);

	return newl;
}

int astarList_delete(astarList * l)
{
	if (l == NULL)
		return EXIT_FAILURE;
	while (!astarList_is_empty(l))
	{
		astarList_delete_first(l);
	}
	free(l);
	return EXIT_SUCCESS;
}

void astarList_init(astarList * l)
{
	l->first = l->last = l->current = NULL;
}

int astarList_is_empty(astarList * l)
{
	return l->first == NULL;
}

int astarList_is_on_first(astarList * l)
{
	return l->current == l->first;
}

int astarList_is_on_last(astarList * l)
{
	return l->current == l->last;
}

int astarList_is_out_of(astarList * l)
{
	return l->current == NULL;
}

void astarList_set_on_first(astarList * l)
{
	l->current = l->first;
}

void astarList_set_on_last(astarList * l)
{
	l->current = l->last;
}

void next(astarList * l)
{
	l->current = l->current->next;
}

void astarList_print(astarList * l, gboolean minimal)
{
	
}

int astarList_insert_first(astarList * l, coord pos)
{
	nodeAstar* n = nodeAstar_new(pos, l->first);
	if (n == NULL)
		return EXIT_FAILURE;

	if (astarList_is_empty(l))
	{
		l->last = l->current = n;
	}
	l->first = n;
	return EXIT_SUCCESS;
}

int astarList_insert_last(astarList * l, coord pos)
{
	nodeAstar* n = nodeAstar_new(pos, NULL);
	if (n == NULL)
		return EXIT_FAILURE;

	if (astarList_is_empty(l))
	{
		l->first = l->current = n;
	}
	else
		l->last->next = n;
	l->last = n;
	return EXIT_SUCCESS;
}

int astarList_insert_before_current(astarList * l, coord pos)
{
	if (astarList_is_empty(l) || astarList_is_on_first(l))
	{
		return astarList_insert_first(l, pos);
	}
	else if (astarList_is_out_of(l))
	{
		printf("error: trying to write out of the astarList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeAstar* n = nodeAstar_new(pos, l->current);
		nodeAstar* tmp = l->current;
		astarList_set_on_first(l);
		while (l->current->next != tmp)
		{
			next(l);
		}
		l->current->next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int astarList_insert_after_current(astarList * l, coord pos)
{

	if (astarList_is_empty(l))
	{
		return astarList_insert_first(l, pos);
	}
	else if (astarList_is_out_of(l))
	{
		printf("error: trying to write out of the astarList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeAstar* n = nodeAstar_new(pos, l->current->next);
		l->current->next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int astarList_insert_sort(astarList * l, coord pos)
{
	nodeAstar * tmp = l->current;
	if (astarList_is_empty(l))
	{
		return astarList_insert_first(l, pos);
	}

	astarList_set_on_first(l);

//à faire en fonction des coordonnées
	l->current = tmp;
	return EXIT_SUCCESS;
}

nodeAstar * astarList_delete_first(astarList * l)
{
	if (astarList_is_empty(l)){
		printf("error: trying to delete node in an astarList_is_empty astarList in %s\n", __FUNCTION__);
		return NULL;
	}

	else{
		nodeAstarList * n = l->first;
		nodeAstar * ret = n->a;
		l->first = n->next;
		if (l->first == NULL)
			astarList_init(l);
		astarList_set_on_first(l);
		free((nodeAstarList*)n);
		return ret;
	}
	return NULL;
}

nodeAstar * astarList_delete_last(astarList * l)
{
	if (astarList_is_empty(l)){
		printf("error: trying to delete node in an astarList_is_empty astarList in %s\n", __FUNCTION__);
		return NULL;
	}
	else if (l->first == l->last)
	{
		return astarList_delete_first(l);
	}
	else{
		nodeAstarList* n = l->last;
		nodeAstar * ret = n->a;
		astarList_set_on_first(l);
		while (l->current->next != n)
		{
			next(l);
		}
		l->last = l->current;
		free((nodeAstarList*)n);
		return ret;
	}
	return NULL;
}

nodeAstar * astarList_delete_current(astarList * l)
{
	if (astarList_is_empty(l)){
		printf("error: trying to delete node in an astarList_is_empty astarList in %s\n", __FUNCTION__);
		return NULL;
	}
	if (astarList_is_on_first(l))
	{
		return astarList_delete_first(l);
	}
	else if (astarList_is_on_last(l))
	{
		return astarList_delete_last(l);
	}
	else
	{
		nodeAstarList* n = l->last;
		nodeAstar * ret = n->a;
		astarList_set_on_first(l);
		while (l->current->next != n)
		{
			next(l);
		}
		free((nodeAstarList*)n);

		free((void*)n);
		return ret;
	}
	return NULL;
}

nodeAstar * astarList_delete_single(astarList * l, nodeAstar * a)
{
	nodeAstar * tmp = astarList_find(l, a);
	if (tmp != NULL)
		astarList_delete_current(l);
	return tmp;
}

nodeAstar * astarList_get_current(astarList * l)
{
	return l->current->a;
}

nodeAstar * astarList_find(astarList * l, nodeAstar * a)
{
	astarList_set_on_first(l);
	while (l->current != NULL)
	{
		if (l->current->a == a)
			return l->current->a;
		next(l);
	}
	return NULL;
}