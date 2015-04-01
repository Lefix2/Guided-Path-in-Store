#ifndef SECTIONLIST_H
#define SECTIONLIST_H

#include "Common.h"

/**
* \struct nodeSectionList
* \brief Structure for a node of a sectionList of items
*/
struct nodeSectionList{
	section * s;						/*!< pointer to a section */
	struct nodeSectionList *nextSectionPointer;/*!< pointer to the next nodeSectionList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct sectionList{
	nodeSectionList *firstSectionPointer;	/*!< first section of the list*/
	nodeSectionList *currentSection;/*!< current section of the list*/
	nodeSectionList *lastSectionPointer;	/*!< last section of the list*/
};

nodeSectionList * newNodeSectionPointer(section *i, nodeSectionList *n);

sectionList * newSectionPointerList(void);
int deleteSectionList(sectionList * l);

void initSectionPointerList(sectionList * l);
int emptySectionPointerList(sectionList * l);

int firstSectionPointer(sectionList * l);
int lastSectionPointer(sectionList * l);
int outOfSectionPointerList(sectionList * l);

void setOnFirstSectionPointer(sectionList * l);
void setOnLastSectionPointer(sectionList * l);
void nextSectionPointer(sectionList * l);

void printSectionPointerList(sectionList * l);

int insertFirstSectionPointer(sectionList * l, section * s);
int insertLastSectionPointer(sectionList * l, section * s);
int insertBeforeCurrentSectionPointer(sectionList * l, section * s);
int insertAfterCurrentSectionPointer(sectionList * l, section * s);
int insertSortSectionPointer(sectionList * l, section * s);

section * deletFirstSectionPointer(sectionList * l);
section * deleteLastSectionPointer(sectionList * l);
section * deleteCurrentSectionPointer(sectionList * l);
section * deleteSingleSectionPointer(sectionList * l, section * s);

section * findSectionPointer(sectionList * l, section * s);
section * findSectionPointerId(sectionList * l, int id);

section * getCurrentSectionPointer(sectionList * l);

#endif // !SECTIONLIST_H
