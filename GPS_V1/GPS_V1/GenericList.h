#ifndef GENERICLIST_H
#define GENERICLIST_H

#include "Common.h"

// a common function used to free malloc'd objects
typedef void(*freeFunction)(void *);

typedef gboolean(*listIterator)(void *);

typedef gboolean(*sortFunction)(void*, void*);

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
};

listNode * node_new(void * element, listNode * next);

list * list_new( int elementSize, freeFunction freeFn);
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
void list_add_sort(list *list, void *element, sortFunction sortFN);

void * list_delete_first(list *list);
void * list_delete_first(list *list);
void * list_delete_current(list *list);

void list_for_each(list *list, listIterator iterator);
void list_head(list *list, void *element, gboolean removeFromList);
void list_tail(list *list, void *element);


#endif // !GENERICLIST_H

//
//item * deletefirstitempointer(itemlist * l);
//item * deletelastitempointer(itemlist * l);
//item * deletecurrentitempointer(itemlist * l);
//item * deletesingleitempointer(itemlist * l, item * i);
//
//item * getcurrentitempointer(itemlist * l);
//item * finditempointer(itemlist * l, item * i);
//item * finditempointerid(itemlist * l, int id);