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
		//fprintf(stderr, "Opened database successfully\n");
	}
	return db;
}

//Close database
static void closeDb(sqlite3 *db)
{
	sqlite3_close(db);
	//printf("Database closed\n");
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
	//printf("SQL prepared ok\n\r");

	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			ret++;
		}
	} while (rc == SQLITE_ROW);

	//Close database
	closeDb(db);
	free(sql);

	return ret;
}

//create a new store from a SQLITE database
store* sqlite_new_store_from_database(char *DataBaseName)
{
	int i = 0;

	store* newstore;  //our new store

	// create and initialise the new store
	newstore = sqlite_get_store(DataBaseName);

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

	//printf("SQL prepared ok\n\r");


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
	//printf("SQL prepared ok\n\r");

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
	//printf("SQL prepared ok\n\r");

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
	//printf("SQL prepared ok\n\r");

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

// return in C comments of SQlite
int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	NotUsed = 0;

	for (int i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}
// add value in section
void sqlite_add_section_value(char *DataBaseName)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char command[MAX_ARRAY_OF_CHAR];
	int sectionId = 0;
	int type = 0;
	int posX = 0;
	int posY = 0;
	int lengthX = 0;
	int lengthY = 0;
	char *DbName = DataBaseName;

	/* Open database */
	db = openDb(DbName);

	/* Create SQL statement */

	sectionId = sqlite_get_row(DbName, SQL_TAB_SECTION) + 1;

	unsigned char table[] = "INSERT INTO section VALUES(";
	printf("type :  ");
	scanf("%d", &type);
	printf("posX :  ");
	scanf("%d", &posX);
	printf("posY :  ");
	scanf("%d", &posY);
	printf("lengthX :  ");
	scanf("%d", &lengthX);
	printf("lengthY :  ");
	scanf("%d", &lengthY);
	sprintf(command, "%s%d,%d,%d,%d,%d,%d);", table, sectionId, type, posX, posY, lengthX, lengthY);

	/* Execute SQL statement */
	rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "section created successfully\n");
	}
	closeDb(db);

}
// add item in section
void sqlite_add_item_value(char *DataBaseName)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char command[MAX_ARRAY_OF_CHAR];
	int itemId = 0;
	char item_name[MAX_ARRAY_OF_CHAR];
	int category = 0;
	int stock = 0;
	int fresh = 0;
	int fragility = 0;
	float cost = 0;
	int promotion = 0;
	int posX = 0;
	int posY = 0;
	int sectionId = 0;
	char *DbName = "C:/Users/rom/Documents/projet.db";

	/* Open database */
	db = openDb(DbName);

	/* Create SQL statement */


	itemId = sqlite_get_row(DbName, SQL_TAB_ITEM) + 1;

	unsigned char table[] = "INSERT INTO item VALUES(";
	printf("item's name :  ");
	scanf("%s", item_name);
	printf("category :  ");
	scanf("%d", &category);
	printf("stock :  ");
	scanf("%d", &stock);
	printf("fresh :  ");
	scanf("%d", &fresh);
	printf("fragility :  ");
	scanf("%d", &fragility);
	printf("cost :  ");
	scanf("%f", &cost);
	printf("promotion :  ");
	scanf("%d", &promotion);
	printf("posX in section :  ");
	scanf("%d", &posX);
	printf("posY in section :  ");
	scanf("%d", &posY);
	printf("section :  ");
	scanf("%d", &sectionId);

	sprintf(command, "%s%d,'%s',%d,%d,%d,%d,%f,%d,%d,%d,%d); \n", table, itemId, item_name, category, stock, fresh, fragility, cost, promotion, posX, posY, sectionId);

	/* Execute SQL statement */
	rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "item created successfully\n");
	}
	closeDb(db);
}
// add value in class
void sqlite_add_value(char *DataBaseName)
{
	char *DbName = DataBaseName;
	char class[MAX_ARRAY_OF_CHAR];
	printf("In which class would you add a value ? \n choice betwenn section and item \n answer :");
	scanf("%s", class);
	if (strcmp(class, "section") == 0)
	{
		sqlite_add_section_value(DbName);
	}
	else if (strcmp(class, "item") == 0)
	{
		sqlite_add_item_value(DbName);
	}
	else
	{
		printf("This response does not match any class");
		sqlite_add_value(DbName);
	}
}
// delete value in section
void sqlite_delete_section_value(char *DataBaseName)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char command[MAX_ARRAY_OF_CHAR];
	int sectionId = 0;
	int number_section;
	int first_section = 1;
	char *DbName = DataBaseName;

	/* Open database */
	db = openDb(DbName);

	/* Create SQL statement */
	number_section = sqlite_get_row(DbName, SQL_TAB_SECTION);
	unsigned char table[] = "DELETE FROM SECTION WHERE sectionId =";

	printf("sectionId : ");
	scanf("%d", &sectionId);
	if (sectionId > number_section)
	{
		printf("This section doesn't exist \n");
		sqlite_delete_section_value(DbName);
	}
	else if (sectionId < first_section)
	{
		printf("This section doesn't exist \n");
		sqlite_delete_section_value(DbName);
	}
	else
	{
		sprintf(command, "%s%d;", table, sectionId);
	}


	/* Execute SQL statement */
	rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "section deleted successfully\n");
	}
	closeDb(db);

}
// delete value in item
void sqlite_delete_item_value(char *DataBaseName)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char command[MAX_ARRAY_OF_CHAR];
	int itemId = 0;
	int number_item;
	int first_item = 1;
	char *DbName = DataBaseName;

	/* Open database */
	db = openDb(DbName);

	/* Create SQL statement */
	number_item = sqlite_get_row(DbName, SQL_TAB_ITEM);
	unsigned char table[] = "DELETE FROM item WHERE itemId =";

	printf("itemId : ");
	scanf("%d", &itemId);
	if (itemId > number_item)
	{
		printf("This item doesn't exist \n");
		sqlite_delete_item_value(DbName);
	}
	else if (itemId < first_item)
	{
		printf("This item doesn't exist \n");
		sqlite_delete_item_value(DbName);
	}
	else
	{
		sprintf(command, "%s%d;", table, itemId);
	}


	/* Execute SQL statement */
	rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "item deleted successfully\n");
	}
	closeDb(db);

}
// delete value in class
void sqlite_delete_value(char *DataBaseName)
{
	char *DbName = DataBaseName;
	char class[MAX_ARRAY_OF_CHAR];
	printf("In which class would you delete a value ? \n choice betwenn section and item \n answer :");
	scanf("%s", class);
	if (strcmp(class, "section") == 0)
	{
		sqlite_delete_section_value(DbName);
	}
	else if (strcmp(class, "item") == 0)
	{
		sqlite_delete_item_value(DbName);
	}
	else
	{
		printf("This response does not match any class");
		sqlite_delete_value(DbName);
	}
}