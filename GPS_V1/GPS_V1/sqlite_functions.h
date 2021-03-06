#ifndef _SQLITE_FUNCTIONS_H_
#define _SQLITE_FUNCTIONS_H_

#include "Common.h"
#include "sqlite3.h"

static sqlite3 *openDb(char *dbName); // open the store's database
static void closeDb(sqlite3 *db); // close the store's database
int sqlite_store_row(char *DataBaseName); // return the number of row in a store's query
int sqlite_section_row(char *DataBaseName); //return the number of row in a section's query
int sqlite_item_row(char *DataBaseName); // return the number of row in a item's query
store* sqlite_get_store(char *DataBaseName); // return a pointer on a store from database
store* sqlite_new_store_from_database(char *DataBaseName); // insert sections from database in the store
section **sqlite_get_all_sections(char *DataBaseName, int *nb_section);
item **sqlite_get_all_items(char *DataBaseName, int *nb_item);
int sqlite_category_row(char *DataBaseName);
char** sqlite_get_category(char *DataBaseName);
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int sqlite_add_value();
void sqlite_drop_value(char *dataBaseName, char *tableName);
void sqlite_alter_value(char *dataBaseName, char *tableName, int Id);

#endif