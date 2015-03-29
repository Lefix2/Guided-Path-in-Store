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

//uncomment nextItem line to check memory allocation
//#define MEMCHECK
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

/**
* \struct store
* \brief Structure image of a store
*/
struct store{
	int id;							/*!< Store's identifiant */
	char name[MAX_ARRAY_OF_CHAR];	/*!< Store's name */
	itemList * allocated_stock;			/*!< itemList of item allocated in memory */
	int size[2];					/*!< size in X and Y of the store */
	int ** cartography;				/*!< tab image of the store's cartography */
};

/**
* \struct section
* \brief Structure image of a section
*
*Can be a wall, a section, an entrance etc.
*
*/
struct section{
	int id;							/*!< section's identifiant */
	type s_type;					/*!< section's type (wall, section etc...*/
	int pos[2];						/*!< section's position in store in X and Y */
	int size[2];					/*!< section's size in X and Y */
	int nb_items;					/*!< number of items stored in the section of type section */
	itemList * stock;					/*!< itemList of item pointers pointing to a Store allocated_Stock */
};

#define ITEM_FRAGILITY_MIN 0
#define ITEM_FRAGILITY_MAX 15
/**
* \struct item
* \brief Structure image of an item
*/
struct item{
	int id;							/*!< item's identifiant */
	char name[MAX_ARRAY_OF_CHAR];	/*!< item's name */
	category i_category;			/*!< item's category */
	gboolean fresh;					/*!< Value set to true if the product must be stored in a freezer */
	int fragility;					/*!< image of the fragility of the item */
	double cost;					/*!< item's cost */
	gboolean promotion;				/*!< Values set to true if the product is in promotion */
	int pos_s[2];					/*!< position of the item in the section in X and Y */
	section * i_section;			/*!< pointer to the associated section i the store */
};

/**
* \struct nodeItemList
* \brief Structure for a node of a itemList of items
*/
struct nodeItemList{
	item * i;						/*!< pointer to an item */
	struct nodeItemList * nextItem;			/*!< pointer to the nextItem nodeItemList*/
};

/**
* \struct itemList
* \brief list of pointer to items
*/
struct itemList{
	nodeItemList *firstItem;
	nodeItemList *current;
	nodeItemList *lastItem;
};

gboolean betwn(int a, int x, int b, gboolean equal);
gboolean onBorder(int x, int y, int x_min, int x_max, int y_min, int y_max);

#endif // !COMMON_H