#ifndef COMMON_H
#define COMMON_H

#define X 0
#define Y 1
#define MAX_ARRAY_OF_CHAR 256

typedef enum boolean{ false, true }boolean;
typedef enum type{ t_wall, t_section, t_promo, t_checkout, t_entrance, t_reception }type;
typedef enum category{ fromage, pain, legumes_vert }category;

typedef struct item item;
typedef struct section section;

struct section{
	int id;
	type s_type;
	int pos[2];
	int size[2];
	item ** stock;
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

#endif // !COMMON_H