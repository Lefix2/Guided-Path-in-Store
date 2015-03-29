#include <string.h>

#include "Store.h"

store * newStore(char * name, int size_x, int size_y){
	store * newst;
	newst = (store *)malloc(sizeof(store));

	initStore(newst);
	strcpy(newst->name, name);
	newst->size[X] = size_x;
	newst->size[Y] = size_y;

	return newst;
}

store * initStore(store * sourceStore){
	sourceStore->name[0] = 0;
	sourceStore->cartography = NULL;
	sourceStore->sections = NULL;
	sourceStore->size[X] = 0;
	sourceStore->size[Y] = 0;
}