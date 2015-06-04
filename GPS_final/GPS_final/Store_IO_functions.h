/**
* \file Store_iO_functions.h
* \brief Header Store_IO_functions.c
* \author GPSTeam
* \date 29/03/2015
*
* Contain prototypes of Store_IO_functions
* Make link between our programm and the database 
*/

#ifndef STORE_IO_FUNCTIONS
#define STORE_IO_FUNCTIONS

#include "Common.h"
#include "sqlite3.h"

/*!<All class in the Database*/
#define SQL_TAB_STORE "store"
#define SQL_TAB_ITEM "item"
#define SQL_TAB_SECTION "section"
#define SQL_TAB_CATEGORY "category"

/*!<Open the database in parameter*/
static sqlite3 *openDb(char *dbName);

/*!<Close the database in parameter*/
static void closeDb(sqlite3 *db);

/*!<return the number of row in the class in parameter*/
int sqlite_get_row(char *DataBaseName, char *DataBaseTab);

/*!<create a new store*/
store* sqlite_new_store_from_database(char *DataBaseName);

/*!<Enter differents parameters from the store */
store* sqlite_get_store(char *DataBaseName);

/*!<Put sections in store*/
void sqlite_get_store_sections(char *DataBaseName, store *st_source);

/*!<Put items in store*/
void sqlite_get_store_items(char *DataBaseName, store *st_source);

/*!<return a pointer of table corresponding to category's table*/
char **sqlite_get_category(char *DataBaseName, int nb_category);

/*!<Allow to give to database informations given in the programm*/
int callback(void *NotUsed, int argc, char **argv, char **azColName);

/*!<Create a new section*/
void sqlite_add_section_value(char *DataBaseName);

/*!<create a new item*/
void sqlite_add_item_value(char *DataBaseName);

/*!<add item or section to database*/
void sqlite_add_value(char *DataBaseName);

/*!<Instructions to delete a section's value*/
void sqlite_delete_section_value(char *DataBaseName);

/*!<Instructions to delete an item's value*/
void sqlite_delete_item_value(char *DataBaseName);

/*!<Delete value from database*/
void sqlite_delete_value(char *DataBaseName);

#endif // !STORE_IO_FUNCTIONS
