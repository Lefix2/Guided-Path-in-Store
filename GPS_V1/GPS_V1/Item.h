#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include <string.h>
#include "Section.h"

typedef struct item{
	int id;
	char name[MAX_ARRAY_OF_CHAR];
	char category[MAX_ARRAY_OF_CHAR];
	bool fresh;
	int fragility;
	float cost;
	bool promotion;
	section sect;
}item;

#endif