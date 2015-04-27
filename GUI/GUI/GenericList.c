#include "GenericList.h"

listNode * node_new(void * element,int elementSize, listNode * next)
{
	listNode *newNode;
	newNode= (listNode*)malloc(sizeof(listNode));

	newNode->data = malloc(elementSize);
	memcpy(newNode->data, element, elementSize);
	newNode->next = next;

	return newNode;
}

list * list_new(int elementSize, freeFunction freeFn)
{
	if (elementSize <= 0)
		return NULL;

	list *newList = (list *)malloc(sizeof(list));
	list_init(newList);
	newList->logicalLength = 0;
	newList->elementSize = elementSize;
	newList->freeFn = freeFn;

	return newList;
}

void list_destroy(list *list)
{
	while (!list_is_empty(list))
	{
		list_delete_first(list);
		list_next(list);
	}
}

void list_init(list * list)
{
	list->first = list->current = list->last = NULL;
}

gboolean list_is_empty(list *list)
{
	return list->first == NULL;
}

gboolean list_is_on_first(list *list)
{
	return list->current == list->first;
}

gboolean list_is_on_last(list *list)
{
	return list->current == list->last;
}

gboolean list_is_out_of(list *list)
{
	return list->current == NULL;
}

int list_size(list *list)
{
	return list->logicalLength;
}

void list_set_on_first(list *list)
{
	list->current = list->first;
}

void list_set_on_last(list *list)
{
	list->current = list->last;
}

void list_next(list *list)
{
	list->current = list->current->next;
}

void list_add_first(list *list, void *element)
{
	listNode *node = node_new(element, list->elementSize, list->first);

	if (list_is_empty(list))
		list->current = list->last = node;
	list->first = node;
	list->logicalLength++;
}

void list_add_last(list *list, void *element)
{
	listNode *node = node_new(element, list->elementSize, NULL);

	if (list_is_empty(list))
		list->current = list->first = list->last = node;
	else
		list->last->next = node;
	list->last = node;
}

void list_add_before_current(list *list, void *element)
{
	if (list_is_empty(list) || list_is_on_first(list))
		list_add_first(list, element);
	else if (list_is_out_of(list))
		printf("error : in %s, trying to write out of the list\n", __FUNCTION__);
	else
	{
		listNode *node = node_new(element, list->elementSize, list->current);
		listNode *current = list->current;
		list_set_on_first(list);
		while (list->current->next != current)
		{
			list_next(list);
		}
		list->current->next = node;
	}
}

void list_add_after_current(list *list, void *element)
{
	if (list_is_empty(list))
		list_add_first(list, element);
	else if (list_is_out_of(list))
		printf("error : in %s, trying to write out of the list\n", __FUNCTION__);
	else
	{
		listNode *node = node_new(element, list->elementSize, list->current->next);
		list->current->next = node;
	}
}

void list_add_sort(list *list, void *element)
{
	if (list_is_empty(list))
		list_add_first(list, element);
	else
	{
		list_set_on_first(list);
		while (!list_is_out_of(list))
		{
			if (list->dataCompFn(list->current, element) < 0)
				list_next(list);
			else
			{
				list_add_before_current(list, element);
				break;
			}
		} 
		if (list_is_out_of(list))
			list_add_last(list, element);
	}
}

void * list_delete_first(list *list)
{
	if (list_is_empty(list))
		printf("error : in %s, trying to delete node in an empty list\n", __FUNCTION__);
	else
	{
		listNode *node = list->first;
		void * ret = node->data;
		if (list->first == list->last)
			list_init(list);
		else
			list->first = node->next;

		if (list->freeFn)
		{
			list->freeFn(node->data);
			return NULL;
		}
		free(node);
		return ret;
	}
	return NULL;
}

void * list_delete_last(list *list)
{
	if (list_is_empty(list))
		printf("error : in %s, trying to delete node in an empty list\n", __FUNCTION__);
	else if (list->first == list->last)
		list_delete_first(list);
	else
	{
		listNode *node = list->last;
		void *ret = node->data;
		list_set_on_first(list);
		while (list->current->next != node)
		{
			list_next(list);
		}
		list->last = list->current;

		if (list->freeFn)
		{
			list->freeFn(node->data);
			return NULL;
		}
		free(node);
		return ret;
	}
	return NULL;
}

void * list_delete_current(list *list)
{
	if (list_is_empty(list))
		printf("error : in %s, trying to delete node in an empty list\n", __FUNCTION__);
	if (list_is_on_last(list))
		list_delete_last(list);
	else
	{
		listNode *node = list->current;
		void *ret = node->data;
		list_set_on_first(list);
		while (list->current->next != node)
		{
			list_next(list);
		}
		list->current->next = node->next;

		if (list->freeFn)
		{
			list->freeFn(node->data);
			return NULL;
		}
		free(node);
		return ret;
	}
	return NULL;
}

void list_for_each(list *list, listIterator iterator)
{
	gboolean result = TRUE;
	list_set_on_first(list);
	while (!list_is_out_of(list) && result) {
		result = iterator(list->current->data);
		list_next(list);
	}
}

void * list_find(list *list, void *element)
{
	list_set_on_first(list);
	while (!list_is_out_of(list))
	{
		if (list->dataCompFn(list->current->data, element))
			return list->current->data;
		list_next(list);
	}
	return NULL;
}