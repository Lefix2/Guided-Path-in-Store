#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h> //Fonctions strcpy, strcat
#include "Common.h"

#define MAX_ARRAY_OF_CHAR 255

int main(int argc, char* argv[])
{
	//createTable();
	//printf("%d\n",returnRow("C:/Users/rom/Documents/projet.db"));
	//sqlite_get_section("C:/Users/rom/Documents/projet.db");
	sqlite_add_value("C:/Users/rom/Documents/projet.db");
	sqlite_delete_value("C:/Users/rom/Documents/projet.db");
	getch();
	// 
	
}