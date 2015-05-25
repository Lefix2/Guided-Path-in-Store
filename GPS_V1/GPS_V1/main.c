#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h> //Fonctions strcpy, strcat

#include "Common.h"
#include "Item.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"
#include "Shopping.h"
#include "merchant.h"
#include "StoreImage.h"

#include "tests.h"

#define MAX_ARRAY_OF_CHAR 255

int my_main(int argc, char* argv[])
{
	//createTable();
	//printf("%d\n",returnRow("C:/Users/rom/Documents/projet.db"));
	//system("PAUSE");
	char **tab;
	tab = (char**)malloc(MAX_ARRAY_OF_CHAR*sizeof(char*));
	//tab = returnValue();
	tab = element_list("C:/Users/rom/Documents/projet.db");
	int i;
	for (i = 0; i < 8; i++)
	{
		printf("%s \n", tab[i]);
		}
	system("pause");
}

int main(int argc, char* argv[]){
	/* initialiser GTK+ */
	gtk_init(&argc, &argv);


	/*Appel de la fonction de felix*/
	principal();

	/* boucle principale */
	gtk_main();

	return EXIT_SUCCESS;
}