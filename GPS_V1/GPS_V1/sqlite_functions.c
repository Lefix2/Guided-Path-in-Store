#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Fonctions strcpy, strcat

#include "sqlite_functions.h"
#include "sqlite3.h"
#include "store.h"
#include "Section.h"
#include "Item.h"
#include "Common.h"



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
int sqlite_store_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from category;";
	char *description;
	int ret = 0;


	//Open database
	db = openDb(dbName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return 2;
	}

	printf("SQL prepared ok\n\r");

	/* allocate memory for decsription and venue */
	description = (char *)malloc(MAX_ARRAY_OF_CHAR*sizeof(char));

	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			ret++;
		}
	} while (rc == SQLITE_ROW);

	/* récupération de la valeur et libération de la mémoire */

	free(description);

	//Close database
	closeDb(db);

	// valeur retournée
	return ret;
}

//return a pointer on a store from database
store* sqlite_get_store(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from store;";
	int storeId = 0;
	int lengthX = 0;
	int lengthY = 0;
	char *name;
	store *newstore;
	name = (char*)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));

	
	//Open database
	db = openDb(dbName);

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
		storeId = (int)atof((char *)sqlite3_column_text(stmt, 0));
		name = (char *)sqlite3_column_text(stmt, 1);
		lengthX = (int)atof((char *)sqlite3_column_text(stmt, 2));
		lengthY = (int)atof((char *)sqlite3_column_text(stmt, 3));
	}
	
	newstore = store_new(storeId, name, lengthX, lengthY);
	printf("%d %s %d %d \n", storeId, name, lengthX, lengthY);

	//Close database
	closeDb(db);
	free(name);

	// valeur retournée
	return newstore;
}

// return the number of row in a section's query
int sqlite_section_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from category;";
	char *description;
	int ret = 0;


	//Open database
	db = openDb(dbName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return 2;
	}

	printf("SQL prepared ok\n\r");

	/* allocate memory for decsription and venue */
	description = (char *)malloc(MAX_ARRAY_OF_CHAR*sizeof(char));

	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			ret++;
		}
	} while (rc == SQLITE_ROW);

	/* récupération de la valeur et libération de la mémoire */

	free(description);

	//Close database
	closeDb(db);

	// valeur retournée
	return ret;
}

//insert sections from database in the store
store* sqlite_new_store_from_database(char *DataBaseName)
{
	//SQLITE3 et initialisation des paramètres
	int i = 0;
	
	store* newstore;

	// création du store
	newstore = sqlite_get_store(DataBaseName);

	//remplissage des sections
	int nb_sections;
	section **all_sections;

	all_sections = sqlite_get_all_sections(DataBaseName, &nb_sections);
	for (i = 0; i < nb_sections; i++)
	{
		store_add_section(newstore, *(all_sections + i));
	}
	free(all_sections);
	
	return newstore;
}

//return all sections of a store
section **sqlite_get_all_sections(char *DataBaseName, int *nb_section)
{
	sqlite3_stmt *stmt;
	int rc;
	char *sql = "SELECT * from section;";
	sqlite3 *db = NULL;
	
	*nb_section = sqlite_section_row(DataBaseName);
	int sectionId = 0;
	int type = 0;
	int posX = 0;
	int posY = 0;
	int lengthX = 0;
	int lengthY = 0;

	int i;
	section **all_sections = (section **)calloc(*nb_section, sizeof(section*));

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
			sectionId = (int)atof((char *)sqlite3_column_text(stmt, 0));
			type = (int)atof((char *)sqlite3_column_text(stmt, 1));
			posX = (int)atof((char *)sqlite3_column_text(stmt, 2));
			posY = (int)atof((char *)sqlite3_column_text(stmt, 3));
			lengthX = (int)atof((char *)sqlite3_column_text(stmt, 4));
			lengthY = (int)atof((char *)sqlite3_column_text(stmt, 5));

			// create new section
			*(all_sections + i) = section_new(sectionId, type);
			section_set_pos(*(all_sections + i), posX, posY);
			section_set_size(*(all_sections + i), lengthX, lengthY);

			printf("%d %d %d %d %d %d \n", sectionId, type, posX, posY, lengthX, lengthY);
		}
	}


	//Close database
	closeDb(db);

	return all_sections;
}

//insert items from database in the store
item **sqlite_get_all_items(char *DataBaseName, int *nb_item)
{
	//SQLITE3 et initialisation des variables

	sqlite3_stmt *stmt;
	int rc;
	char *sql = "SELECT * from section;";
	sqlite3 *db = NULL;

	*nb_item = sqlite_section_row(DataBaseName);
	int itemId = 0;
	int category = 0;
	int posX = 0;
	int posY = 0;

	int i;
	item **all_items = (item **)calloc(*nb_section, sizeof(item*));

	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from item;";
	int i = 0;
	int nb_item;
	nb_item = sqlite_item_row(dbName);
	int itemId = 0;
	char* item_name = 0;
	int category = 0;
	int fresh = 0;
	int fragility = 0;
	float cost = 0.00;
	int promotion = 0;
	int posX = 0;
	int posY = 0;
	int sectionId = 0;
	store* newstore;
	newstore = sqlite_get_store(dbName);
	item *newItem;



	//Open database
	db = openDb(dbName);

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
			itemId = (int)atof((char *)sqlite3_column_text(stmt, 0));
			item_name = (char *)sqlite3_column_text(stmt, 1);
			category = (int)atof((char *)sqlite3_column_text(stmt, 2));
			fresh = (int)atof((char *)sqlite3_column_text(stmt, 3));
			cost = (float)atof((char *)sqlite3_column_text(stmt, 4));
			promotion = (int)atof((char *)sqlite3_column_text(stmt, 5));
			posX = (int)atof((char *)sqlite3_column_text(stmt, 6));
			posY = (int)atof((char *)sqlite3_column_text(stmt, 7));
			sectionId = (int)atof((char *)sqlite3_column_text(stmt, 8));

			// recup row item
			newItem = item_new(itemId, category, item_name);

			/*if*/
			store_add_item(newstore, newItem);

			if (sectionId != -1)
				section_add_item(store_find_section_id(newstore, sectionId), newItem, posX, posY);

		}
	}


	//Close database
	closeDb(db);


}


// return the number of row in an item's query
int sqlite_item_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from category;";
	char *description;
	int ret = 0;


	//Open database
	db = openDb(dbName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return 2;
	}

	printf("SQL prepared ok\n\r");

	/* allocate memory for decsription and venue */
	description = (char *)malloc(MAX_ARRAY_OF_CHAR*sizeof(char));

	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			ret++;
		}
	} while (rc == SQLITE_ROW);

	/* récupération de la valeur et libération de la mémoire */

	free(description);

	//Close database
	closeDb(db);

	// valeur retournée
	return ret;
}

// return the number of rw in a category's query
int sqlite_category_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from category;";
	char *description;
	int ret=0;


	//Open database
	db = openDb(dbName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return 2;
	}

	printf("SQL prepared ok\n\r");

	/* allocate memory for decsription and venue */
	description = (char *)malloc(MAX_ARRAY_OF_CHAR*sizeof(char));

	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			ret++;
		}
	} while (rc == SQLITE_ROW);

	/* récupération de la valeur et libération de la mémoire */

	free(description);

	//Close database
	closeDb(db);

	// valeur retournée
	return ret;
}

// return all elements of category's table
char** sqlite_get_category(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = "C:/Users/rom/Documents/projet.db";
	int rc;
	char *sql = "SELECT * from category;";
	int i = 0;
	int nb_category;
	nb_category = sqlite_category_row(dbName);
	int category_Id = 0;

	char** category_table = alloc_double_char_pointer(nb_category, MAX_ARRAY_OF_CHAR);
	
	//Open database
	db = openDb(dbName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
		return NULL;
	}

	printf("SQL prepared ok\n\r");

	/* get all category strings */
	for (i = 0; i < nb_category; i++)
	{
		rc = sqlite3_step(stmt);
		strcpy(category_table[i], (char *)sqlite3_column_text(stmt, 1));
		printf("%s\n", category_table[i]);
	}

	//Close database
	closeDb(db);

	// valeur retournée
	return category_table;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	NotUsed = 0;

	for (int i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}
int sqlite_add_value()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char command[MAX_ARRAY_OF_CHAR];
	char sectionId = 0;
	char *DbName = "C:/Users/rom/Documents/projet.db";
	
	/* Open database */
	db = openDb(DbName);

	/* Create SQL statement */
	unsigned char tableName[10];
	printf("Donnez le nom de la table où ajouter une valeur : ");
	scanf("%s", tableName);
	if (strcmp(tableName, "section") == 0)
	{
		sectionId = sqlite_section_row(DbName)+1;
		unsigned char table[] = "INSERT INTO section VALUES( ";
		printf("type :  ");
		scanf("%s", tableName);
		sprintf(command, "%s%s", table, tableName);
		printf("%s\n", command);
		system("pause");
	}
	



	/* Execute SQL statement */
	rc = sqlite3_exec(db, command, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "Table created successfully\n");
	}
	closeDb(db);
	return 0;
}

/*void dropTable(char *dataBaseName, char *tableName);
void addValue(char *dataBaseName, char *tableName);
void dropValue(char *dataBaseName, char *tableName);
void alterValue(char *dataBaseName, char *tableName, int Id);

*/

