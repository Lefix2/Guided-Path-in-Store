#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Fonctions strcpy, strcat

#include "Store_IO_functions.h"

#include "store.h"
#include "Section.h"
#include "Item.h"

//Open database
static sqlite3 *openDb(char *dbName)
{
	sqlite3 *db = NULL;
	int rc;

	rc = sqlite3_open(dbName, &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}
	return db;
}

//Close database
static void closeDb(sqlite3 *db)
{
	sqlite3_close(db);
	printf("Database closed\n");
}

//return the number of row in a store's query
int sqlite_get_row(char *DataBaseName, char *DataBaseTab)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	int rc;

	char *sql = (char*)calloc(MAX_ARRAY_OF_CHAR, sizeof(char));
	int ret = 0;


	//Open database
	db = openDb(DataBaseName);

	/* prepare the sql, leave stmt ready for loop */
	sprintf(sql, "SELECT * from %s;", DataBaseTab);
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return 2;
	}
	printf("SQL prepared ok\n\r");

	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			ret++;
		}
	} while (rc == SQLITE_ROW);

	//Close database
	closeDb(db);

	return ret;
}

//create a new store from a SQLITE database
store* sqlite_new_store_from_database(char *DataBaseName)
{
	int i = 0;

	store* newstore;  //our new store

	// create and initialise the new store
	newstore = sqlite_get_store(DataBaseName);

	//remplissage des sections
	int nb_sections;
	section **all_sections;

	sqlite_get_store_sections(DataBaseName, newstore);
	sqlite_get_store_items(DataBaseName, newstore);

	return newstore;
}

//create and initialise a new store
store* sqlite_get_store(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	int rc;
	char *sql = "SELECT * from store;";
	

	store *newstore;
	int storeId = 0;
	int lengthX = 0;
	int lengthY = 0;
	char *name = NULL;


	//Open database
	db = openDb(DataBaseName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return NULL;
	}

	printf("SQL prepared ok\n\r");


	/* get all store strings */
	if (sqlite3_step(stmt) == 100)
	{
		// récupération des valeurs
		storeId = atoi((char *)sqlite3_column_text(stmt, 0));
		name = (char *)sqlite3_column_text(stmt, 1);
		lengthX = atoi((char *)sqlite3_column_text(stmt, 2));
		lengthY = atoi((char *)sqlite3_column_text(stmt, 3));
	}

	newstore = store_new(storeId, name, lengthX, lengthY);

	//Close database
	closeDb(db);

	// valeur retournée
	return newstore;
}

void sqlite_get_store_sections(char *DataBaseName, store *st_source)
{
	sqlite3_stmt *stmt;
	int rc;
	char *sql = "SELECT * from section;";
	sqlite3 *db = NULL;

	int nb_section = sqlite_get_row(DataBaseName, SQL_TAB_SECTION);
	int sectionId = 0;
	int type = 0;
	int posX = 0;
	int posY = 0;
	int lengthX = 0;
	int lengthY = 0;

	section *tmp_sec;

	int i;

	//Open database
	db = openDb(DataBaseName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
	}
	printf("SQL prepared ok\n\r");

	/* get all section strings */
	for (i = 0; i < nb_section; i++)
	{
		if (sqlite3_step(stmt) == 100)
		{
			// récupération des valeurs
			sectionId = atoi((char *)sqlite3_column_text(stmt, 0));
			type = atoi((char *)sqlite3_column_text(stmt, 1));
			posX = atoi((char *)sqlite3_column_text(stmt, 2));
			posY = atoi((char *)sqlite3_column_text(stmt, 3));
			lengthX = atoi((char *)sqlite3_column_text(stmt, 4));
			lengthY = atoi((char *)sqlite3_column_text(stmt, 5));

			// create new section
			tmp_sec = section_new(sectionId, type);
			section_set_pos(tmp_sec, posX, posY);
			section_set_size(tmp_sec, lengthX, lengthY);
			store_add_section(st_source, tmp_sec);
		}
	}
	
	//Close database
	closeDb(db);
}

void sqlite_get_store_items(char *DataBaseName, store *st_source)
{
	//SQLITE3 et initialisation des variables
	sqlite3_stmt *stmt;
	int rc;
	char *sql = "SELECT * from item;";
	sqlite3 *db = NULL;

	int nb_item = sqlite_get_row(DataBaseName, SQL_TAB_ITEM);

	int itemId ;
	char* item_name;
	int category;
	int fresh;
	int fragility;
	float cost;
	int promotion;
	int posX;
	int posY;
	int sectionId;

	int i;
	item *tmp_item;

	//Open database
	db = openDb(DataBaseName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
	}
	printf("SQL prepared ok\n\r");

	/* get all store strings */
	for (i = 0; i < nb_item; i++)
	{
		if (sqlite3_step(stmt) == 100)
		{
			// récupération des valeurs
			itemId = atoi((char *)sqlite3_column_text(stmt, 0));
			item_name = (char *)sqlite3_column_text(stmt, 1);
			category = atoi((char *)sqlite3_column_text(stmt, 2));
			fresh = atoi((char *)sqlite3_column_text(stmt, 4));
			cost = atof((char *)sqlite3_column_text(stmt, 6));
			promotion = atoi((char *)sqlite3_column_text(stmt, 7));
			posX = atoi((char *)sqlite3_column_text(stmt, 8));
			posY = atoi((char *)sqlite3_column_text(stmt, 9));
			sectionId = atoi((char *)sqlite3_column_text(stmt, 10));

			// recup row item
			tmp_item = item_new(itemId, category, item_name);

			/*if*/
			store_add_item(st_source, tmp_item);

			if (sectionId != -1)
				section_add_item(store_find_section_id(st_source, sectionId), tmp_item, posX, posY);

		}
	}

	//Close database
	closeDb(db);
}

// return all elements of category's table
char **sqlite_get_category(char *DataBaseName, int *nb_category)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	int rc;
	char *sql = "SELECT * from category;";

	int i = 0;
	int category_Id = 0;
	*nb_category = sqlite_get_row(DataBaseName, SQL_TAB_CATEGORY);

	char **category_table = alloc_double_char_pointer(*nb_category, MAX_ARRAY_OF_CHAR);

	//Open database
	db = openDb(DataBaseName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return NULL;
	}
	printf("SQL prepared ok\n\r");

	/* get all category strings */
	for (i = 0; i < *nb_category; i++)
	{
		rc = sqlite3_step(stmt);
		strcpy(category_table[i], (char *)sqlite3_column_text(stmt, 1));
	}

	//Close database
	closeDb(db);

	// valeur retournée
	return category_table;
}