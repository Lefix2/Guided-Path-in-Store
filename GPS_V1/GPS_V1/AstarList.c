#include <string.h>

#include "AstarList.h"
#include "Astar.h"

nodeAstar * nodeAstarList_new(nodeAstar * a, nodeAstarList *n)
{
	nodeAstarList * newn;
	newn = (nodeAstarList*)malloc(sizeof(nodeAstarList));

	newn->a = a;
	newn->next = n;

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
		nodeAstar_delete(astarList_delete_first(l));
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

void astarList_next(astarList * l)
{
	l->current = l->current->next;
}

void astarList_print(astarList * l, gboolean minimal)
{
	astarList_set_on_first(l);
	while (astarList_is_out_of(l))
	{
		printf("astarNode : x=%d, y=%d, h=%d, g=%d, f=%d\n", l->current->a->pos.x, l->current->a->pos.y, l->current->a->h, l->current->a->g, l->current->a->f);
		astarList_next(l);
	}
}

int astarList_insert_first(astarList * l, nodeAstar *a)
{
	nodeAstarList* n = nodeAstarList_new(a, l->first);
	if (n == NULL)
		return EXIT_FAILURE;

	if (astarList_is_empty(l))
	{
		l->last = l->current = n;
	}
	l->first = n;
	return EXIT_SUCCESS;
}

int astarList_insert_last(astarList * l, nodeAstar *a)
{
	nodeAstarList* n = nodeAstarList_new(a, NULL);
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

int astarList_insert_before_current(astarList * l, nodeAstar *a)
{
	if (astarList_is_empty(l) || astarList_is_on_first(l))
	{
		return astarList_insert_first(l, a);
	}
	else if (astarList_is_out_of(l))
	{
		printf("error: trying to write out of the astarList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeAstarList* n = nodeAstarList_new(a, l->current);
		nodeAstarList* tmp = l->current;
		astarList_set_on_first(l);
		while (l->current->next != tmp)
		{
			astarList_next(l);
		}
		l->current->next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int astarList_insert_after_current(astarList * l, nodeAstar *a)
{

	if (astarList_is_empty(l))
	{
		return astarList_insert_first(l, a);
	}
	else if (astarList_is_out_of(l))
	{
		printf("error: trying to write out of the astarList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeAstarList* n = nodeAstarList_new(a, l->current->next);
		l->current->next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int astarList_insert_sort(astarList * l, nodeAstar *a)
{
	int ret;
	nodeAstarList * tmp = l->current;
	if (astarList_is_empty(l))
	{
		return astarList_insert_first(l, a);
	}

	astarList_set_on_first(l);
	do
	{
		//sort with f value to get easily the best node
		if (a->f <= l->current->a->f)
		{
			ret = astarList_insert_before_current(l, a);
			l->current = tmp;
			return ret;
		}else astarList_next(l);
	} while (!astarList_is_out_of(l));

	l->current = tmp;
	return astarList_insert_last(l,a);
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
		free(n);
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
			astarList_next(l);
		}
		l->last = l->current;
		l->last->next = NULL;
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
		nodeAstarList* n = l->current;
		nodeAstar * ret = n->a;
		astarList_set_on_first(l);
		while (l->current->next != n)
		{
			astarList_next(l);
		}
		l->current->next = n->next;

		free((nodeAstarList*)n);
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

nodeAstar * astarList_get_first(astarList * l)
{
	return l->first->a;
}

nodeAstar * astarList_get_current(astarList * l)
{
	return l->current->a;
}

nodeAstar * astarList_get_last(astarList * l)
{
	return l->last->a;
}

nodeAstar * astarList_find(astarList * l, nodeAstar * a)
{
	astarList_set_on_first(l);
	while (l->current != NULL)
	{
		if (l->current->a == a)
			return l->current->a;
		astarList_next(l);
	}
	return NULL;
}