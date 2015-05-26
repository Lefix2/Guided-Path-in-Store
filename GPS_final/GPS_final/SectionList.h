#ifndef SECTIONLIST_H
#define SECTIONLIST_H

#include "Common.h"

/**
* \struct nodeSectionList
* \brief Structure for a node of a sectionList of items
*/
struct nodeSectionList{
	section * s;						/*!< pointer to a section */
	struct nodeSectionList *sectionPointerList_next;/*!< pointer to the next nodeSectionList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct sectionList{
	nodeSectionList *first;	/*!< first section of the list*/
	nodeSectionList *current;/*!< current section of the list*/
	nodeSectionList *last;	/*!< last section of the list*/
};

nodeSectionList * nodeSectionPointerList_new(section *i, nodeSectionList *n);

sectionList * sectionPointerList_new(void);
int sectionPointerList_delete(sectionList * l);

void sectionPointerList_init(sectionList * l);
int sectionPointerList_is_empty(sectionList * l);

int sectionPointerList_is_on_first(sectionList * l);
int sectionPointerList_is_on_last(sectionList * l);
int sectionPointerList_is_out_of(sectionList * l);

void sectionPointerList_set_on_first(sectionList * l);
void sectionPointerList_set_on_last(sectionList * l);
void sectionPointerList_next(sectionList * l);

void sectionPointerList_print(sectionList * l);

int sectionPointerList_insert_first(sectionList * l, section * s);
int sectionPointerList_insert_last(sectionList * l, section * s);
int sectionPointerList_insert_before_current(sectionList * l, section * s);
int sectionPointerList_insert_after_current(sectionList * l, section * s);
int sectionPointerList_insert_sort(sectionList * l, section * s);

section * sectionPointerList_delete_first(sectionList * l);
section * sectionPointerList_delete_last(sectionList * l);
section * sectionPointerList_delete_current(sectionList * l);
section * sectionPointerList_delete_single(sectionList * l, section * s);

section * sectionPointerList_get_current(sectionList * l);
section * sectionPointerList_find(sectionList * l, section * s);
section * sectionPointerList_find_id(sectionList * l, int id);

section * getcurrent(sectionList * l);

#endif // !SECTIONLIST_H
