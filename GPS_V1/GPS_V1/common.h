#ifndef COMMON_H
#define COMMON_H

#define X 0
#define Y 1

#define MAX_ARRAY_OF_CHAR 256

typedef enum boolean{ false, true }boolean;
typedef enum type{ t_none, t_wall, t_section, t_promo, t_checkout, t_entrance, t_reception }type;
typedef enum category{ c_none, fromage, pain, legumes_vert }category;

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
	int category;
	boolean fresh;
	int fragility;
	float cost;
	boolean promotion;
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

#endif // !COMMON_H