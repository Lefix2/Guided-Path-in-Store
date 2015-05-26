#ifndef STORE_IO_FUNCTIONS
#define STORE_IO_FUNCTIONS

#include "Common.h"
#include "sqlite3.h"

#define SQL_TAB_STORE "store"
#define SQL_TAB_ITEM "item"
#define SQL_TAB_SECTION "section"
#define SQL_TAB_CATEGORY "category"

static sqlite3 *openDb(char *dbName);
static void closeDb(sqlite3 *db);

int sqlite_get_row(char *DataBaseName, char *DataBaseTab);
store* sqlite_new_store_from_database(char *DataBaseName);
store* sqlite_get_store(char *DataBaseName);
void sqlite_get_store_sections(char *DataBaseName, store *st_source);
void sqlite_get_store_items(char *DataBaseName, store *st_source);

#endif // !STORE_IO_FUNCTIONS
