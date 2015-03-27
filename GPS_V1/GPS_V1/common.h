#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define X 0
#define Y 1

#define MAX_ARRAY_OF_CHAR 256

typedef enum boolean{ false, true }boolean;
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

struct section{
	int id;
	type s_type;
	int pos[2];
	int size[2];
	int nb_items;
	list * stock;
};

struct item{
	int id;
	char name[MAX_ARRAY_OF_CHAR];
	category i_category;
	boolean fresh;
	int fragility;
	double cost;
	boolean promotion;
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

boolean betwn(int a, int x, int b, boolean equal);
boolean onBorder(int x, int y, int x_min, int x_max, int y_min, int y_max);

#endif // !COMMON_H