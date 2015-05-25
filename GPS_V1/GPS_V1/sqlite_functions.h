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
void sqlite_get_section(char *DataBaseName); // insert sections from database in the store
void sqlite_get_item(char *DataBaseName); // insert items from database in the store
void createFile();
int callback(void *NotUsed, int argc, char **argv, char **azColName);

void addValue(char *dataBaseName, char *tableName); 
void dropValue(char *dataBaseName, char *tableName);
void alterValue(char *dataBaseName, char *tableName, int Id);

#endif