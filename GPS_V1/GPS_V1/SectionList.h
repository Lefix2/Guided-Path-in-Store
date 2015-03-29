#ifndef SECTIONLIST_H
#define SECTIONLIST_H

#include "Common.h"

/**
* \struct nodeSectionList
* \brief Structure for a node of a sectionList of items
*/
struct nodeSectionList{
	section * s;						/*!< pointer to an item */
	struct nodeSectionList *nextSection;/*!< pointer to the nextItem nodeItemList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct sectionList{
	nodeSectionList *firstSection;	/*!< first section of the list*/
	nodeSectionList *currentSection;/*!< current section of the list*/
	nodeSectionList *lastSection;	/*!< last section of the list*/
};

nodeSectionList * newNodeSectionList(section *i, nodeSectionList *n);

sectionList * newSectionList(void);
int deleteSectionList(sectionList * l);

void initSectionList(sectionList * l);
int emptySectionList(sectionList * l);
int firstSection(sectionList * l);
int lastSection(sectionList * l);
int outOfSectionList(sectionList * l);
void setOnfirstSection(sectionList * l);
void setOnlastSection(sectionList * l);
void nextSection(sectionList * l);
section * getCurrentSection(sectionList * l);
void printSectionList(sectionList * l);
int insertFirstSection(sectionList * l, section * s);
int insertLastSection(sectionList * l, section * s);
int insertBeforeCurrentSection(sectionList * l, section * s);
int insertAfterCurrentSection(sectionList * l, section * s);
void deletFirstSection(sectionList * l);
void deleteLastSection(sectionList * l);
void deleteCurrentSection(sectionList * l);
int findSection(sectionList * l, section * s);
int insertSortSection(sectionList * l, section * s);
int deleteSectionList(sectionList * l, section * s);

#endif // !SECTIONLIST_H
