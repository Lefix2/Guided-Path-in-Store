/**
* \file Common.h
* \brief Header of Common.c
* \author GPSTeam
* \date 29/03/2015
*
* Contain all structures and usefull defines
*
*/
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

//uncomment nextItemPointer line to check memory allocation
#define MEMCHECK
#include "myAlloc.h"

/****usefull define ****/
#define MAX_ARRAY_OF_CHAR 256
#define X 0
#define Y 1


/**
* \enum type
* \brief enum of all section's type
*/
typedef enum type{ t_none, t_wall, t_section, t_promo, t_checkout, t_entrance, t_reception }type;

#ifdef SECTYPDEF
char* sec_type[] = {"none", "wall", "section", "promo", "checkout", "entrance", "reception" };
#endif

/**
* \enum category
* \brief enum of all product's category
*/
typedef enum category{ c_none, fromage, pain, legumes_vert, alcool }category;

#ifdef ITECATDEF
char* item_category[] = { "none", "fromage", "pain", "legumes vert", "alcool" };
#endif

/****structure's prototypes****/
typedef struct store store;
typedef struct section section;
typedef struct item item;

typedef struct nodeItemList nodeItemList;
typedef struct itemList itemList;

typedef struct nodeSectionList nodeSectionList;
typedef struct sectionList sectionList;

typedef struct listNode listNode;
typedef struct list list;

gboolean betwn(int a, int x, int b, gboolean equal);
gboolean onBorder(int x, int y, int x_min, int x_max, int y_min, int y_max);

#endif // !COMMON_H