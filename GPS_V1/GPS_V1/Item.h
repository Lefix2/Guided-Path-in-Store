#ifndef ITEM_H
#define ITEM_H

#define ITECATDEF
#include "Common.h"

#define ITEM_FRAGILITY_MIN 0
#define ITEM_FRAGILITY_MAX 15

/**
* \struct item
* \brief Structure image of an item
*/
struct item{
	int id;							/*!< item's identifiant */
	char name[MAX_ARRAY_OF_CHAR];	/*!< item's name */
	category category;			/*!< item's category */
	gboolean fresh;					/*!< Value set to true if the product must be stored in a freezer */
	int fragility;					/*!< image of the fragility of the item */
	double cost;					/*!< item's cost */
	gboolean promotion;				/*!< Values set to true if the product is in promotion */
	coord posInSec;				/*!< position of the item in the section in X and Y */
	section * section;			/*!< pointer to the associated section i the store */
};

item * item_new(int id, category category, char * name);
item * item_init(item * item);
int item_delete(item * item);

gboolean item_has_section(item * item);

int item_set_Id(item * item, int id);
int item_set_name(item * item, char * name);
int item_set_category(item * item, category category);
int item_set_fresh(item * item, gboolean fresh);
int item_set_fragility(item * item, int fragility);
int item_set_cost(item * item, double cost);
int item_set_promotion(item * item, gboolean promotion);
int item_set_pos(item * item, int x_pos, int y_pos);
int item_set_section(item * item, section * section);

int item_get_id(item * item);
char * item_get_name(item * item);
category item_get_category(item * item);
char * item_get_category_string(item * item);
gboolean item_is_fresh(item * item);
int item_get_fragility(item * item);
double item_get_cost(item * item);
gboolean item_is_in_promotion(item * item);
int item_get_X_pos(item * item);
int item_get_Y_pos(item * item);
section * item_get_section(item * item);

//fonction pour liste générique
int item_compare_id(void *element1, void *element2);


void item_print(item * item, gboolean minimal);

void testItem(void);

#endif // !ITEM_H