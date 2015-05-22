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
	char *sql = "SELECT * from item where itemId = 1;";
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

char** sqlite_get_store(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from store where storeId = 1;";
	char **description;
	int i = 0;
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
	description = (char**)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			description[0] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[1] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[2] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[3] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			strcpy(description[0], (char *)sqlite3_column_text(stmt, 0));
			strcpy(description[1], (char *)sqlite3_column_text(stmt, 1));//récupération de la valeur grâce à la requête
			strcpy(description[2], (char *)sqlite3_column_text(stmt, 2));
			strcpy(description[3], (char *)sqlite3_column_text(stmt, 3));
			//item_set_Id(item, atof(description[0]));
		}
	} while (rc == SQLITE_ROW);

	/* finish off */
	sqlite3_close(db);


	//Close database
	closeDb(db);
	
	return description;
}

store* create_store()
{
	char **tab;
	tab = (char**)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	tab = element_store("C:/Users/rom/Documents/projet.db");
	int a = 0;
	int b = 0;
	int c = 0;
	char *name;
	store *Aucampos;
	name = (char*)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	name = tab[1];
	a = (int)atof(tab[0]);
	b = (int)atof(tab[2]);
	c = (int)atof(tab[3]);
	Aucampos = store_new(a, name, b, c);
	printf("%d %s %d %d", a, name, b, c);
	system("PAUSE");



	return Aucampos;
}

int sqlite_section_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from item where itemId = 1;";
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

char** element_section(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from section";
	char **description;
	int i = 0;
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
	description = (char**)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	/* loop reading each row until step returns anything other than SQLITE_ROW */
	do {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) { //can read data
			description[0] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[1] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[2] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[3] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[4] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			description[5] = malloc(MAX_ARRAY_OF_CHAR*sizeof(char));
			strcpy(description[0], (char *)sqlite3_column_text(stmt, 0));
			strcpy(description[1], (char *)sqlite3_column_text(stmt, 1));//récupération de la valeur grâce à la requête
			strcpy(description[2], (char *)sqlite3_column_text(stmt, 2));
			strcpy(description[3], (char *)sqlite3_column_text(stmt, 3));
			strcpy(description[4], (char *)sqlite3_column_text(stmt, 4));
			strcpy(description[5], (char *)sqlite3_column_text(stmt, 5));
			strcpy(description[6], (char *)sqlite3_column_text(stmt, 6));
			
		}
	} while (rc == SQLITE_ROW);

	/* finish off */
	sqlite3_close(db);


	//Close database
	closeDb(db);

	return description;
}

void create_section()
{
	char **tab;
	tab = (char**)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	tab = element_section("C:/Users/rom/Documents/projet.db");
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	char *name;
	a = atof(tab[0]);
	b = atof(tab[2]);
	c = atof(tab[3]);
	d = atof(tab[4]);
	e = atof(tab[5]);
	f = atof(tab[6]);
	store* Aucampos;
	Aucampos = create_store();

	/*recup row section*/
	/*for*/
	store_add_new_section(Aucampos, a, b, c, d, e, f);
	/*fin for*/

	item *newItem;
	/*recup row item*/
	/*for*/
	newItem = item_new(/*id*/,/*cat*/,/*name*/);
	/*if*/
	store_add_item(Aucampos,newItem);

	/*if item_section != -1*/
	section_add_item(store_find_section_id(Aucampos,/*id*/), newItem,/*x*/,/*y*/);
	/*endif*/
	
	section_add_item()
	/*fin*/
	
}

int sqlite_item_row(char *DataBaseName)
{
	//SQLITE3
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt;
	char *dbName = DataBaseName;
	int rc;
	char *sql = "SELECT * from item where itemId = 1;";
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
