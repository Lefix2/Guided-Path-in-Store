/*!
* \file  astarList.c
* \brief functions to manage linked list of astar nodes
* \author GPS team
* \date 13/12/2014
*/

#include <string.h>

#include "AstarList.h"
#include "Astar.h"

/*!
* \fn nodeAstar * nodeAstarList_new(nodeAstar * a, nodeAstarList *n)
* \brief Create a new node astar list
* \param[in] *a the astar node
* \param[in] *n the next astar node
* \return the new allocated node
*/
nodeAstar * nodeAstarList_new(nodeAstar * a, nodeAstarList *n)
{
	nodeAstarList * newn;
	newn = (nodeAstarList*)malloc(sizeof(nodeAstarList));

	newn->a = a;
	newn->next = n;

	return newn;
}


/*!
* \fn astarList * astarList_new(void)
* \brief Create a new astar list
* \return the new allocated astar list
*/
astarList * astarList_new(void)
{
	astarList * newl;
	newl = (astarList *)malloc(sizeof(astarList));
	astarList_init(newl);

	return newl;
}

/*!
* \fn int astarList_delete(astarList * l)
* \brief Delete an astar list
* \param[in] *l pointer to the astarlist
* \return EXIT_SUCCES if OK
*/
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

/*!
* \fn void astarList_init(astarList * l)
* \brief Initializes astarlist
* \param[in] *l the astarList to initialize
*/
void astarList_init(astarList * l)
{
	l->first = l->last = l->current = NULL;
}

/*!
* \fn int astarList_is_empty(astarList * l)
* \brief Tells the user if the list is empty or not
* \param[in] *l the astar list
* \return 1 if the list is empty, 0 otherwise
*/
int astarList_is_empty(astarList * l)
{
	return l->first == NULL;
}

/*!
* \fn int astarList_is_on_first(astarList * l)
* \brief Tells the user if the list current cursor is on the first node astar
* \param[in] *l the astar list
* \return 1 if the list is on the first item, 0 otherwise
*/
int astarList_is_on_first(astarList * l)
{
	return l->current == l->first;
}

/*!
* \fn void astarList_is_on_last(astarList * l)
* \brief Tells the user if the list current cursor is on the last item
* \param[in] *l the astarList
* \return 1 if the list is on the last item, 0 otherwise
*/
int astarList_is_on_last(astarList * l)
{
	return l->current == l->last;
}

/*!
* \fn void astarList_is_out_of(astarList * l)
* \brief Tells the user if the list current cursor is out of the list
* \param[in] *l the astarList
* \return 1 if the list cursor is out of the list, 0 otherwise
*/
int astarList_is_out_of(astarList * l)
{
	return l->current == NULL;
}

/*!
* \fn void astarList_set_on_first(astarList * l)
* \brief Set the current cursor of the list on the first item
* \param[in] *l the astarList
*/
void astarList_set_on_first(astarList * l)
{
	l->current = l->first;
}

/*!
* \fn void astarList_set_on_last(astarList * l)
* \brief Set the current cursor of the list on the last item
* \param[in] *l the astarList
*/
void astarList_set_on_last(astarList * l)
{
	l->current = l->last;
}

/*!
* \fn void astarList_next(astarList * l)
* \brief Set the current cursor of the list on the next item
* \param[in] *l the astarList
*/
void astarList_next(astarList * l)
{
	l->current = l->current->next;
}

/*!
* \fn void astarList_print(astarList * l, gboolean minimal)
* \brief Prints the content of the astarList
* \param[in] *l the astarList
* \param[in] minimal prints the list in a minimal way if set at true
*/
void astarList_print(astarList * l, gboolean minimal)
{
	astarList_set_on_first(l);
	while (astarList_is_out_of(l))
	{
		printf("astarNode : x=%d, y=%d, h=%d, g=%d, f=%d\n", l->current->a->pos.x, l->current->a->pos.y, l->current->a->h, l->current->a->g, l->current->a->f);
		astarList_next(l);
	}
}

/*!
* \fn int astarList_insert_first(astarList * l, item * i)
* \brief Insert the item i at the beginning of in the astarList l
* \param[in] *l the list the node is in
* \param[in] *i the item to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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

/*!
* \fn int astarList_insert_last(astarList * l, item * i)
* \brief Insert the item i at the end of the astarList l
* \param[in] *l the list the node is in
* \param[in] *i the item to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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

/*!
* \fn int astarList_insert_before_current(astarList * l, item * i)
* \brief Insert the item i in the astarList l just before the current cursor
* \param[in] *l the list the node is in
* \param[in] *i the item to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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

/*!
* \fn int astarList_insert_after_current(astarList * l, item * i)
* \brief Insert the item i in the astarList l just after the current cursor
* \param[in] *l the list the node is in
* \param[in] *i the item to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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

/*!
* \fn int astarList_insert_sort(astarList * l, item * i)
* \brief Insert the item i in the astarList l sorted by id
* \param[in] *l the list the node is in
* \param[in] *i the item to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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

/*!
* \fn item * astarList_delete_first(astarList * l)
* \brief deletes the first item in the astarList and free the memory
* \param[in] *l the astarList
* \return the item deleted
*/
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

/*!
* \fn item * astarList_delete_last(astarList * l)
* \brief deletes the last item in the astarList and free the memory
* \param[in] *l the astarList
* \return the item deleted
*/
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

/*!
* \fn item * astarList_delete_current(astarList * l)
* \brief deletes the current item in the astarList and free the memory
* \param[in] *l the astarList
* \return the item deleted
*/
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

/*!
* \fn item * astarList_delete_single(astarList * l, item * i)
* \brief deletes the item i in the astarList and free the memory
* \param[in] *l the astarList
* \param[in] *i the item
* \return the item deleted
*/
nodeAstar * astarList_delete_single(astarList * l, nodeAstar * a)
{
	nodeAstar * tmp = astarList_find(l, a);
	if (tmp != NULL)
		astarList_delete_current(l);
	return tmp;
}

/*!
* \fn item * astarList_get_first(astarList * l)
* \brief Get the first item of the astarList
* \param[in] *l the astarList
* \return the first item of the astarList
*/
nodeAstar * astarList_get_first(astarList * l)
{
	return l->first->a;
}

/*!
* \fn item * astarList_get_current(astarList * l)
* \brief Get the current item of the astarList
* \param[in] *l the astarList
* \return the current item of the astarList
*/
nodeAstar * astarList_get_current(astarList * l)
{
	return l->current->a;
}

/*!
* \fn item * astarList_get_last(astarList * l)
* \brief Get the last item of the astarList
* \param[in] *l the astarList
* \return the last item of the astarList
*/
nodeAstar * astarList_get_last(astarList * l)
{
	return l->last->a;
}

/*!
* \fn item * astarList_find(astarList * l, item * i)
* \brief Get the item i of the astarList
* \param[in] *l the astarList
* \param[in] *i the item to search
* \return the item i if contained in the astarList
*/
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