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
#include <gtk\gtk.h>

//uncomment itemPointerList_next line to check memory allocation
#define MEMCHECK
#include "myAlloc.h"

/****usefull define ****/
#define MAX_ARRAY_OF_CHAR 256
#define max(a,b) ((a) > (b) ? (a) : (b))

/**
* \enum type
* \brief enum of all section's type
*/
typedef enum type{ t_floor, t_wall, t_section, t_promo, t_checkout, t_entrance, t_reception }type;

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
typedef struct nodeAstar nodeAstar;

typedef struct nodeItemList nodeItemList;
typedef struct itemList itemList;

typedef struct nodeSectionList nodeSectionList;
typedef struct sectionList sectionList;

typedef struct listNode listNode;
typedef struct list list;

typedef struct nodeAstarList nodeAstarList;
typedef struct astarList astarList;

typedef struct shopping shopping;

typedef struct coord coord;
struct coord{
	int x;
	int y;
};
static coord zero = { 0, 0 };

typedef struct path path;
struct path
{
	coord *coordinates;
	int nb_coord;
};




gboolean betwn(int a, int x, int b, gboolean equal);
gboolean same_coord(coord p1, coord p2);
gboolean is_in_square(coord p, coord sqrBase, coord sqrSize);
gboolean on_border(coord pos, coord sqrBase, coord sqrSize, int borderSize);
coord add_coord(coord c1, coord c2);
int manhattan_distance(coord p1, coord p2);

int **alloc_double_int_pointer(int size1, int size2);
int **alloc_double_char_pointer(int size1, int size2);
void free_double_int_pointer(int **pt, int size1, int size2);
void free_double_char_pointer(char **pt, int size1, int size2);

void rotab(int *tab, int size);

#endif // !COMMON_H