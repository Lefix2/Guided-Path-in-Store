#include "sectionList.h"
#include "Section.h"
#include "ItemList.h"

nodeSectionList * newNodeSectionPointer(section * s, nodeSectionList *n)
{
	nodeSectionList * newn;
	newn = (nodeSectionList*)malloc(sizeof(nodeSectionList));

	newn->nextSectionPointer = n;
	newn->s = s;

	return newn;
}

sectionList * newSectionPointerList(void)
{
	sectionList * newl;
	newl = (sectionList *)malloc(sizeof(sectionList));
	initSectionPointerList(newl);

	return newl;
}

int deleteSectionList(sectionList * l)
{
	if (l == NULL)
		return EXIT_FAILURE;
	while (!emptySectionPointerList(l))
	{
		deletFirstSectionPointer(l);
	}
	free(l);
	return EXIT_SUCCESS;
}

void initSectionPointerList(sectionList * l)
{
	l->firstSectionPointer = l->lastSectionPointer = l->currentSection = NULL;
}

int emptySectionPointerList(sectionList * l)
{
	return l->firstSectionPointer == NULL;
}

int firstSectionPointer(sectionList * l)
{
	return l->currentSection == l->firstSectionPointer;
}

int lastSectionPointer(sectionList * l)
{
	return l->currentSection == l->lastSectionPointer;
}

int outOfSectionPointerList(sectionList * l)
{
	return l->currentSection == NULL;
}

void setOnFirstSectionPointer(sectionList * l)
{
	l->currentSection = l->firstSectionPointer;
}

void setOnLastSectionPointer(sectionList * l)
{
	l->currentSection = l->lastSectionPointer;
}

void nextSectionPointer(sectionList * l)
{
	l->currentSection = l->currentSection->nextSectionPointer;
}

void printSectionPointerList(sectionList * l)
{
	char* header[] = { ".--------------------------------------------------------------------------.",
					   "|  id  |      type      | items in stock |     size x     |     size y     |" };
	int i;
	section * tmp;

	printf("Section : ");
	if (emptySectionPointerList(l)){
		printf("empty\n");
	}
	else{
		printf("\n");
		setOnFirstSectionPointer(l);

		for (i = 0; i < 2; i++)
		{
			printf("%s\n", header[i]);
		}
		printf("%s\n", header[0]);

		while (!outOfSectionPointerList(l))
		{
			tmp = l->currentSection->s;
			printf("| %4d | %14s | %14d | %14d | %14d |\n",Section_getId(tmp),
														   Section_getTypeString(tmp),
														   Section_getNbItems(tmp),
														   Section_getXSize(tmp),
														   Section_getYSize(tmp)
			);
			if (tmp->s_type == t_section)
				printItemList(tmp->stock, TRUE);
			printf("%s\n", header[0]);
			nextSectionPointer(l);
		}
		printf("\n");
	}

}

int insertFirstSectionPointer(sectionList * l, section * s)
{
	nodeSectionList* n = newNodeSectionPointer(s, l->firstSectionPointer);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptySectionPointerList(l))
	{
		l->lastSectionPointer = l->currentSection = n;
	}
	l->firstSectionPointer = n;
	return EXIT_SUCCESS;
}

int insertLastSectionPointer(sectionList * l, section * s)
{
	nodeSectionList* n = newNodeSectionPointer(s, NULL);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptySectionPointerList(l))
	{
		l->firstSectionPointer = l->currentSection = n;
	}
	else
		l->lastSectionPointer->nextSectionPointer = n;
	l->lastSectionPointer = n;
	return EXIT_SUCCESS;
}

int insertBeforeCurrentSectionPointer(sectionList * l, section * s)
{
	nodeSectionList* n;
	n = newNodeSectionPointer(s, l->currentSection);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptySectionPointerList(l))
	{
		l->lastSectionPointer = l->currentSection = l->lastSectionPointer = n;
	}
	else if (firstSectionPointer(l))
	{
		insertFirstSectionPointer(l, s);
	}
	else if (outOfSectionPointerList(l))
	{
		printf("error: trying to write out of the sectionList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeSectionList* tmp = l->currentSection;
		setOnFirstSectionPointer(l);
		while (l->currentSection->nextSectionPointer != tmp)
		{
			nextSectionPointer(l);
		}
		l->currentSection->nextSectionPointer = n;
	}
	return EXIT_SUCCESS;
}

int insertAfterCurrentSectionPointer(sectionList * l, section * s)
{
	nodeSectionList* n;
	n = newNodeSectionPointer(s, l->currentSection->nextSectionPointer);
	if (n == NULL)
		return EXIT_FAILURE;

	if (emptySectionPointerList(l))
	{
		l->lastSectionPointer = l->currentSection = l->lastSectionPointer = n;
	}
	else if (outOfSectionPointerList(l))
	{
		printf("error: trying to write out of the sectionList!");
		return EXIT_FAILURE;
	}
	l->currentSection->nextSectionPointer = n;
	return EXIT_SUCCESS;
}

int insertSortSectionPointer(sectionList * l, section * s)
{
	nodeSectionList * tmp = l->currentSection;
	if (emptySectionPointerList(l))
	{
		insertFirstSectionPointer(l, s);
		return EXIT_SUCCESS;
	}

	setOnFirstSectionPointer(l);

	do
	{
		if (l->currentSection->s->id <= s->id)
			nextSectionPointer(l);
		else
		{
			insertBeforeCurrentSectionPointer(l, s);
			setOnFirstSectionPointer(l);
			break;
		}
	} while (!outOfSectionPointerList(l));
	if (outOfSectionPointerList(l))
		insertLastSectionPointer(l, s);

	l->currentSection = tmp;
	return EXIT_SUCCESS;
}

section * deletFirstSectionPointer(sectionList * l)
{
	if (emptySectionPointerList(l)){
		printf("error: trying to delete node in an emptySectionPointerList sectionList in %s\n", __FUNCTION__);
		return NULL;
	}

	else{
		nodeSectionList * n = l->firstSectionPointer;
		section * ret = n->s;
		l->firstSectionPointer = n->nextSectionPointer;
		if (l->firstSectionPointer == NULL)
			initSectionPointerList(l);
		setOnFirstSectionPointer(l);
		free((void*)n);
		return ret;
	}
	return NULL;
}

section * deleteLastSectionPointer(sectionList * l)
{
	if (emptySectionPointerList(l)){						//no node
		printf("error: trying to delete node in an empty sectionList in %s\n", __FUNCTION__);
		return NULL;
	}
	else if (l->firstSectionPointer == l->lastSectionPointer)		//only one node
	{
		return deletFirstSectionPointer(l);
	}
	else{											//at least 2 nodes
		nodeSectionList* n = l->lastSectionPointer;
		section * ret = n->s;
		setOnFirstSectionPointer(l);
		while (l->currentSection->nextSectionPointer != n)
		{
			nextSectionPointer(l);
		}
		l->lastSectionPointer = l->currentSection;
		free((void*)n);
		return ret;
	}
	return NULL;
}

section * deleteCurrentSectionPointer(sectionList * l)
{
	if (emptySectionPointerList(l)){
		printf("error: trying to delete node in an empty sectionList in %s\n", __FUNCTION__);
		return NULL;
	}
	if (firstSectionPointer(l))
	{
		return deletFirstSectionPointer(l);
	}
	else if (lastSectionPointer(l))
	{
		return deleteLastSectionPointer(l);
	}
	else
	{
		nodeSectionList* n = l->currentSection;
		section * ret = n->s;
		setOnFirstSectionPointer(l);
		while (l->currentSection->nextSectionPointer != n)
		{
			nextSectionPointer(l);
		}
		l->currentSection->nextSectionPointer = n->nextSectionPointer;

		free((void*)n);
		return ret;
	}
	return NULL;
}

section * deleteSingleSectionPointer(sectionList * l, section * s)
{
	section * tmp = findSectionPointer(l, s);
	if(tmp != NULL)
		deleteCurrentSectionPointer(l);
	return tmp;
}

section * getCurrentSectionPointer(sectionList * l)
{
	return l->currentSection->s;
}

section * findSectionPointer(sectionList * l, section * s)
{
	setOnFirstSectionPointer(l);
	while (l->currentSection != NULL)
	{
		if (l->currentSection->s == s)
			return l->currentSection->s;
		nextSectionPointer(l);
	}
	return NULL;
}

section * findSectionPointerId(sectionList * l, int id)
{
	setOnFirstSectionPointer(l);
	while (l->currentSection != NULL)
	{
		if (l->currentSection->s->id == id)
			return l->currentSection->s;
		nextSectionPointer(l);
	}
	return NULL;
}