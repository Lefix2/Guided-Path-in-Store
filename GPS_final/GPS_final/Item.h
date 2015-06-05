/**
* \file Item.h
* \brief Header Item.c
* \author GPSTeam
* \date 29/03/2015
*
* Contain prototypes of Item
* Make link between our programm and the database
*/

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
	category category;				/*!< item's category */
	int stock;						/*!< used for numerous usage*/
	gboolean fresh;					/*!< Value set to true if the product must be stored in a freezer */
	int fragility;					/*!< image of the fragility of the item */
	double cost;					/*!< item's cost */
	gboolean promotion;				/*!< Values set to true if the product is in promotion */
	coord posInSec;					/*!< position of the item in the section in X and Y */
	section * section;				/*!< pointer to the associated section i the store */
	path *pathTo;					/*!< path from the precedent item, variable only used in the user checklist*/
};

/*!< create a new item*/
item * item_new(int id, category category, char * name);

/*!< init an item*/
item * item_init(item * item);

/*!< delete an item*/
int item_delete(item * item);

/*!<look if the item has already a section*/
gboolean item_has_section(item * item);

/*!< set the Id of the item*/
int item_set_Id(item * item, int id);

/*!< set the name of the item*/
int item_set_name(item * item, char * name);

/*!< set the category of the item*/
int item_set_category(item * item, category category);

/*!< set the stock of the item*/
int item_set_stock(item * item, int stock);

/*!< set the fresh of the item*/
int item_set_fresh(item * item, gboolean fresh);

/*!< set fragility of an item*/
int item_set_fragility(item * item, int fragility);

/*!< set cost of an item*/
int item_set_cost(item * item, double cost);

/*!< set promotion of an item*/
int item_set_promotion(item * item, gboolean promotion);

/*!< set positions of an item*/
int item_set_pos(item * item, int x_pos, int y_pos);

/*!< set section of an item*/
int item_set_section(item * item, section * section);

/*!< get Id of an item*/
int item_get_id(item * item);

/*!< get the name of an item*/
char * item_get_name(item * item);

/*!< set the name of an item*/
category item_get_category(item * item);

/*!< set the category of an item*/
char * item_get_category_string(item * item);

/*!< get stock of an item*/
int item_get_stock(item *item);

/*!< get fresh of an item*/
gboolean item_is_fresh(item * item);

/*!< get fragility of an item*/
int item_get_fragility(item * item);

/*!< get cost of an item */
double item_get_cost(item * item);

/*!<get promotion of an item*/
gboolean item_is_in_promotion(item * item);

/*!< get position of an item*/
coord item_get_pos(item * item);

/*!< get section of an item*/
section * item_get_section(item * item);

/*!< get path to an item*/
path * item_get_pathTo(item * item);

/*!< compare two items*/
int item_compare_id(void *element1, void *element2);

/*!< print informations of an item*/
void item_print(item * item, gboolean minimal);

/*!< test item*/
void testItem(void);

#endif // !ITEM_H