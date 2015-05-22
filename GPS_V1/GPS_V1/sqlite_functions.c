#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Fonctions strcpy, strcat

#include "sqlite_functions.h"
#include "sqlite3.h"
#include "store.h"
#include "Section.h"
#include "Item.h"


static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

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


int createTable()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char command[MAX_ARRAY_OF_CHAR];

	/* Open database */
	db = openDb("test.db");

	/* Create SQL statement */
	unsigned char tableName[10];
	printf("Donnez le nom de la table a ajouter : ");
	scanf("%s", tableName);
	unsigned char table[] = "CREATE TABLE ";
	unsigned char Id[] = "(ID INT PRIMARY KEY NOT NULL);";
	sprintf(command, "%s%s%s", table, tableName, Id);
	printf("%s\n", command);
	system("pause");
	

	 
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


char** returnValue(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from item where category = 'fruit';";
	char **description;
	int i = 0;
	

	
	//Open database
	db = openDb(dbName);

	/* prepare the sql, leave stmt ready for loop */
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare database\n\r");
		sqlite3_close(db);
	
	}

	printf("SQL prepared ok\n\r");

	/* allocate memory for decsription and venue */
	//description = (char *)malloc(100);
	description = (char**)malloc(returnRow(DataBaseName)*sizeof(char*));
	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			description[i] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			strcpy(description[i], (char *)sqlite3_column_text(stmt, 1));//récupération de la valeur grâce à la requête
			printf("%s \n", description[i]);
			i++;
			}
	} while (rc == SQLITE_ROW);

	/* finish off */
	sqlite3_close(db);
	

	//Close database
	closeDb(db);

	return description;
}

int sqlite_store_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from store;";
	char *description;
	int ret;
	

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
			strcpy(description, sqlite3_column_text(stmt, 0));//récupération de la valeur grâce à la requête
			printf("Description : %s \n", description);
		}
	} while (rc == SQLITE_ROW);;

	/* finish off */
	sqlite3_close(db);
	ret = (int)atof(description);
	free(description);

	//Close database
	closeDb(db);

	return ret;
}

store* sqlite_get_store(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = "C:/Users/rom/Documents/projet.db";
	int rc;
	char *sql = "SELECT * from store;";
	char **description;
	int i = 0;
	int size_row;
	size_row = sqlite_store_row(dbName);
	//nodeItemPointerList_new();



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

	/* allocate memory for decsription and venue */
	//description = (char *)malloc(100);
	description = (char**)malloc(size_row*sizeof(char*));
	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			for (i = 0; i <= 3; i++)
			{
				description[i] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
				strcpy(description[i], (char *)sqlite3_column_text(stmt, i));
				
			}
			
		}
	} while (rc == SQLITE_ROW);

	//Close database
	closeDb(db);

	int storeId = 0;
	int lengthX = 0;
	int lengthY = 0;
	char *name;
	store *Aucampos;
	name = (char*)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	name = description[1];
	storeId = (int)atof(description[0]);
	lengthX = (int)atof(description[2]);
	lengthY = (int)atof(description[3]);
	Aucampos = store_new(storeId, name, lengthX, lengthY);

	for (i = 0; i <= 3; i++)
	{
		free(description[i]);
	}
	free(description);

	return Aucampos;
}


int sqlite_section_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from section;";
	char *description;
	int ret;


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
			strcpy(description, sqlite3_column_text(stmt, 0));//récupération de la valeur grâce à la requête
			printf("Description : %s \n", description);
		}
	} while (rc == SQLITE_ROW);;

	/* finish off */
	sqlite3_close(db);
	ret = (int)atof(description);
	free(description);

	//Close database
	closeDb(db);

	return ret;
}

void sqlite_get_section(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = "C:/Users/rom/Documents/projet.db";
	int rc;
	char *sql = "SELECT * from section;";
	char **description;
	int i = 0;
	int size_row;
	size_row = sqlite_section_row(dbName);
	int sectionId = 0;
	int type = 0;
	int posX = 0;
	int posY = 0;
	int lengthX = 0;
	int lengthY = 0;


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

	/* allocate memory for decsription and venue */
	//description = (char *)malloc(100);
	description = (char**)malloc(size_row*sizeof(char*));
	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			for (i = 0; i <= 5; i++)
			{
				description[i] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
				strcpy(description[i], (char *)sqlite3_column_int(stmt, i));

			}

		}
	} while (rc == SQLITE_ROW);

	//Close database
	closeDb(db);

	store* Aucampos;
	Aucampos = sqlite_get_store(dbName);
	/*recupérer values*/
	sectionId = description[0];
	type = description[1];
	posX = description[2];
	posY = description[3];
	lengthX = description[4];
	lengthY = description[5];

	/*recup row section*/
	for (i = 0; i < size_row; i++)
	{
		store_add_new_section(Aucampos, sectionId, type, posX, posY, lengthX, lengthY);
	}

	for (i = 0; i <= 5; i++)
	{
		free(description[i]);
	}
	free(description);

}


int sqlite_item_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from item;";
	char *description;
	int ret;


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
			strcpy(description, sqlite3_column_text(stmt, 0));//récupération de la valeur grâce à la requête
			printf("Description : %s \n", description);
		}
	} while (rc == SQLITE_ROW);;

	/* finish off */
	sqlite3_close(db);
	ret = (int)atof(description);
	free(description);

	//Close database
	closeDb(db);

	return ret;
}

void sqlite_get_item(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = "C:/Users/rom/Documents/projet.db";
	int rc;
	char *sql = "SELECT * from item;";
	char **description;
	int i = 0;
	int size_row;
	size_row = sqlite_item_row(dbName);
	int itemId = 0;
	char* name = 0;
	int category = 0;
	int fresh = 0;
	int fragility = 0;
	float cost = 0.00;
	int promotion = 0;
	int posX = 0;
	int posY = 0;
	int sectionId = 0;



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

	/* allocate memory for decsription and venue */
	//description = (char *)malloc(100);
	description = (char**)malloc(size_row*sizeof(char*));
	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			for (i = 0; i <= 9; i++)
			{
				description[i] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
				strcpy(description[i], (char *)sqlite3_column_text(stmt, i));

			}

		}
	} while (rc == SQLITE_ROW);

	//Close database
	closeDb(db);

	itemId = (int)atof(description[0]);
	name = description[1];
	category = (int)atof(description[2]); 
	fresh = (int)atof(description[3]);
	fragility = (int)aof(description[4]);
	cost = (float)atof(description[5]);
	promotion = (int)atof(description[6]);
	posX = (int)atof(description[7]);
	posY = (int)atof(description[8]);
	sectionId = (int)atof(description[9]);


	store* Aucampos;
	Aucampos = sqlite_get_store(dbName);

	item *newItem;
	/*recup row item*/
	for (i = 0; i < size_row; i++)
	{
		newItem = item_new(itemId, category, name);
	}
	/*if*/
	store_add_item(Aucampos, newItem);

	if (sectionId != -1)
	section_add_item(store_find_section_id(Aucampos,sectionId), newItem,posX,posY);
	
	for (i = 0; i <= 9; i++)
	{
		free(description[i]);
	}
	free(description);

}
/*
int addValue(char *dataBaseName, char *tableName)
{
sqlite3 *db;
char *zErrMsg = 0;
int  rc;
char *sql;
const char* data = "Callback function called";

/* Open database */
/*rc = sqlite3_open("dataBaseName", &db);
if (rc){
fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
exit(0);
}
else{
fprintf(stdout, "Opened database successfully\n");
}
//char s[30] = strcat("CREATE TABLE ", tableName);
//printf("%c", s);
*/
/* Create SQL statement */
/*
sql = "create table zoo";
*/
/* Execute SQL statement */
/*rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
if (rc != SQLITE_OK){
fprintf(stderr, "SQL error: %s\n", zErrMsg);
sqlite3_free(zErrMsg);
}
else{
fprintf(stdout, "Value added successfully\n");
}
sqlite3_close(db);
return 0;
}*/

/*void dropTable(char *dataBaseName, char *tableName);
void addValue(char *dataBaseName, char *tableName);
void dropValue(char *dataBaseName, char *tableName);
void alterValue(char *dataBaseName, char *tableName, int Id);
void printTable(char *dataBaseName, char *tableName);
char returnValue(char *dataBaseName, char *tableName);
char returnInformations(char *dataBaseName, char *tableName);
*/

//FUNCTIONS

/*
char* createFile()
{
char tableName[10];
printf("Donnez le nom de la table a ajouter: ");
scanf("%s", tableName);
char table[30] = "CREATE TABLE ";
char Id[50] = "(ID INT PRIMARY KEY NOT NULL);";
char *d = strcat(table, tableName);
printf("%s\n", d);
system("pause");
char *s = strcat(d, Id);
printf("%s\n", s);
system("pause");
//createTable("test.db", "rue");
return  s;
}
*/
