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

//return a pointer on a store from database

// return the number of row in a section's query
int sqlite_section_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from section;";
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

//return all sections of a store

//insert items from database in the store


// return the number of row in an item's query
int sqlite_item_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from item;";
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

// return all elements of category's table

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
	
	sectionId = sqlite_section_row(DbName)+1;
		
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

	
	itemId = sqlite_item_row(DbName) + 1;

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

	sprintf(command, "%s%d,'%s',%d,%d,%d,%d,%f,%d,%d,%d,%d); \n", table, itemId, item_name, category, stock,fresh, fragility, cost,promotion,posX,posY,sectionId);
		
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
	number_section = sqlite_section_row(DbName);
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
	int first_item =1;
	char *DbName = DataBaseName;

	/* Open database */
	db = openDb(DbName);

	/* Create SQL statement */
	number_item = sqlite_item_row(DbName);
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

/*
void alterValue(char *dataBaseName, char *tableName, int Id);

*/

