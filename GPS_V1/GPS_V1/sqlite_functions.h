#ifndef _SQLITE_FUNCTIONS_H_
#define _SQLITE_FUNCTIONS_H_

#include "Common.h"
#include "sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName);
static sqlite3 *openDb(char *dbName);
static void closeDb(sqlite3 *db);
static sqlite3 *openDb(char *dbName);
static void closeDb(sqlite3 *db);
int createTable();
char** returnValue(char *DataBaseName);
int sqlite_store_row(char *DataBaseName);
int sqlite_section_row(char *DataBaseName);
int sqlite_item_row(char *DataBaseName);
store* sqlite_get_store(char *DataBaseName);
void sqlite_get_section(char *DataBaseName);
void sqlite_get_item(char *DataBaseName);

void dropTable(char *dataBaseName, char *tableName);
void addValue(char *dataBaseName, char *tableName);
void dropValue(char *dataBaseName, char *tableName);
void alterValue(char *dataBaseName, char *tableName, int Id);
void printTable(char *dataBaseName, char *tableName);
char returnInformations(char *dataBaseName, char *tableName);
void edit();
#endif