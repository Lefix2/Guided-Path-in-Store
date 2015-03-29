#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define X 0
#define Y 1

#define MAX_ARRAY_OF_CHAR 256
#define MAX_STORE_SIZE 128

typedef enum type{ t_none, t_wall, t_section, t_promo, t_checkout, t_entrance, t_reception }type;
typedef enum category{ c_none, fromage, pain, legumes_vert, alcool }category;

#ifdef SECTYPDEF
char* sec_type[] = {"none", "wall", "section", "promo", "checkout", "entrance", "reception" };
#endif

#ifdef ITECATDEF
char* item_category[] = { "none", "fromage", "pain", "legumes vert", "alcool" };
#endif

typedef struct section section;
typedef struct item item;
typedef struct nodeList nodeList;
typedef struct list list;
typedef struct store store;

struct section{
	int id;
	type s_type;
	int pos[2];
	int size[2];
	int nb_items;
	list * stock;
};


#define ITEM_FRAGILITY_MIN 0
#define ITEM_FRAGILITY_MAX 15

struct item{
	int id;
	char name[MAX_ARRAY_OF_CHAR];
	category i_category;
	gboolean fresh;
	int fragility;
	double cost;
	gboolean promotion;
	int pos_s[2];
	section * i_section;
};

struct nodeList{
	item * i;
	struct nodeList * next;
};

struct list{
	nodeList *first;
	nodeList *current;
	nodeList *last;
};

struct store{
	char name[MAX_ARRAY_OF_CHAR];
	section * sections;
	int * cartography;
	int size[2];
};

gboolean betwn(int a, int x, int b, gboolean equal);
gboolean onBorder(int x, int y, int x_min, int x_max, int y_min, int y_max);

#endif // !COMMON_H