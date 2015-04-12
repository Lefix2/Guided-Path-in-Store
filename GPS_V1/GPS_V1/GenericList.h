#ifndef GENERICLIST_H
#define GENERICLIST_H

#include "Common.h"

// a common function used to free malloc'd objects
typedef void(*freeFunction)(void *);

//a function that return information about classment of elements
//-1 if element2 < element1
// 0 if element2 = element1
// 1 if element2 > element1
typedef int(*sortFunction)(void*, void*);

typedef gboolean(*listIterator)(void *);

typedef struct listNode {
	void *data;
	struct listNode *next;
};

typedef struct list{
	int logicalLength;
	int elementSize;
	listNode *first;
	listNode *current;
	listNode *last;
	freeFunction freeFn;
	sortFunction dataCompFn;
};

listNode * node_new(void * element, int elementSize, listNode * next);

list * list_new( int elementSize, freeFunction freeFn, sortFunction dataCompFn);
void list_destroy(list *list);

void list_init(list * list);

gboolean list_is_empty(list *list);
gboolean list_is_on_first(list *list);
gboolean list_is_on_last(list *list);
gboolean list_is_out_of(list *list);
int list_size(list *list);

void list_set_on_first(list *list);
void list_set_on_last(list *list);
void list_next(list *list);

void list_add_first(list *list, void *element);
void list_add_last(list *list, void *element);
void list_add_before_current(list *list, void *element);
void list_add_after_current(list *list, void *element);
void list_add_sort(list *list, void *element);

void * list_delete_first(list *list);
void * list_delete_last(list *list);
void * list_delete_current(list *list);

void list_for_each(list *list, listIterator iterator);
void * list_find(list *list, void *element);

#endif // !GENERICLIST_H