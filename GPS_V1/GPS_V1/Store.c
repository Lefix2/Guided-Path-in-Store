#include <string.h>

#include "Store.h"
#include "Section.h"
#include "SectionList.h"
#include "Item.h"
#include "ItemList.h"

store * newStore(int id, char * name, int x_size, int y_size)
{
	store * st_new = (store *)malloc(sizeof(store));

	Store_init(st_new);
	Store_setId(st_new, id);
	Store_setName(st_new, name);
	Store_setSize(st_new, x_size, y_size);
	st_new->allocated_stock = newItemPointerList();
	st_new->allocated_sections = newSectionPointerList();
	Store_computeCartography(st_new);

	return st_new;
}

store * Store_init(store * st_source)
{
	st_source->id = 0;
	st_source->name[0] = 0;
	st_source->size[X] = 0;
	st_source->size[Y] = 0;
	st_source->allocated_stock = NULL;
	st_source->cartography = NULL;
	
	return st_source;
}

int Store_delete(store * st_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	Store_freeCartography(st_source);
	Store_deleteAllocatedStock(st_source);
	Store_deleteAllocatedSections(st_source);
	free(st_source);
	return EXIT_SUCCESS;
}

int Store_setId(store * st_source, int id)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	st_source->id = id;
	return EXIT_SUCCESS;
}

int Store_setName(store * st_source, char * name)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	strcpy(st_source->name, name);
	return EXIT_SUCCESS;
}

int Store_setSize(store * st_source, int x_size, int y_size)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	Store_freeCartography(st_source);
	st_source->size[X] = x_size;
	st_source->size[Y] = y_size;
	return EXIT_SUCCESS;
}

int Store_getId(store * st_source)
{
	return st_source->id;
}

char * Store_getName(store * st_source)
{
	return st_source->name;
}

int Store_getXSize(store * st_source)
{
	return st_source->size[X];
}

int Store_getYSize(store * st_source)
{
	return st_source->size[Y];
}

void Store_print(store * st_source)
{
	int i, j;
	printf("***** Store  *****\n");
	printf("ID    : %d\n", st_source->id);
	printf("name  : %s\n", st_source->name);
	printf("size X : %d\n", st_source->size[X]);
	printf("     Y : %d\n", st_source->size[Y]);
	printSectionPointerList(st_source->allocated_sections);
	printf("Cartography :\n");
	for (i = 0; i < st_source->size[Y]+2; i++){
		printf("X");
	}
	printf("\n");
	for (i = 0; i < st_source->size[X]; i++){
		printf("X");
		for (j = 0; j < st_source->size[Y]; j++){
			printf("%d", st_source->cartography[i][j]);
		}
		printf("X\n");
	}
	for (i = 0; i < st_source->size[Y]+2; i++){
		printf("X");
	}
	printf("\n\n");
}

int Store_freeCartography(store * st_source)
{
	for (int i = 0; i < st_source->size[X]; i++)
	{
		free(*(st_source->cartography+i));
	}
	free(st_source->cartography);
	return EXIT_SUCCESS;
}

int Store_computeCartography(store * st_source)
{
	st_source->cartography = (int**)calloc(st_source->size[X], sizeof(int*));
	for (int i = 0; i < st_source->size[X]; i++)
	{
		*(st_source->cartography + i) = (int*)calloc(st_source->size[Y], sizeof(int));
	}
	return EXIT_SUCCESS;
}

int Store_addItem(store * st_source, int id, category i_category, char * name)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	item * new_i = newItem(id, i_category, name);
	item * tmp = findItemPointerId(st_source->allocated_stock, id);
	if (tmp != NULL)
	{
		printf("error : Trying to add an Item with existing id in Store\n");
		printf("existing : "); Item_print(tmp, TRUE);
		printf("new : "); Item_print(new_i, TRUE);
		printf("\n");
		Item_delete(new_i);
		return EXIT_FAILURE;
	}
	insertSortItemPointer(st_source->allocated_stock, new_i);
	return EXIT_SUCCESS;
}

int Store_addSection(store * st_source, int id, type s_type, int x_pos, int y_pos, int x_size, int y_size)
{
	int i, j;
	if (st_source == NULL)
		return EXIT_FAILURE;
	section * tmp = findSectionPointerId(st_source->allocated_sections, id);
	if (tmp != NULL)
	{
		printf("error : Trying to add a section with existing id in Store\n");
		Section_print(tmp, TRUE);
		printf("\n");
		return EXIT_FAILURE;
	}
	if (((x_size + x_pos) > st_source->size[X]) || ((y_size + y_pos) > st_source->size[Y])){
		printf("Error : Trying to add a section out of the store\n");
		return EXIT_FAILURE;
	}
	for (i = 0; i < x_size; i++){
		for (j = 0; j < y_size; j++){
			if (st_source->cartography[x_pos + i][y_pos + j] != 0){
				printf("error : Trying to add a section on an existing section\n");
				return EXIT_FAILURE;
			}
		}
	}
	section * new_s = newSection(id, s_type);
	Section_setPos(new_s, x_pos, y_pos);
	Section_setSize(new_s, x_size, y_size);
	insertSortSectionPointer(st_source->allocated_sections, new_s);
	for (i = 0; i < x_size; i++){
		for (j = 0; j < y_size; j++){
			(st_source->cartography[x_pos + i][y_pos + j]) = 1;
		}
	}
	return EXIT_SUCCESS;
}

int Store_deleteItem(store * st_source, item * i_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	Section_removeItem(i_source->i_section, i_source);
	return Item_delete(deleteSingleItemPointer(st_source->allocated_stock, i_source));
}

int Store_deleteAllocatedStock(store * st_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	while (!emptyItemPointerList(st_source->allocated_stock))
	{
		Item_delete(deleteFirstItemPointer(st_source->allocated_stock));
	}
	free(st_source->allocated_stock);
	return EXIT_SUCCESS;
}

int Store_deleteSection(store * st_source, section * s_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	return Section_delete(deleteSingleSectionPointer(st_source->allocated_stock, s_source));
}

int Store_deleteAllocatedSections(store * st_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	while (!emptySectionPointerList(st_source->allocated_sections))
	{
		Section_delete(deletFirstSectionPointer(st_source->allocated_sections));
	}
	free(st_source->allocated_sections);
	return EXIT_SUCCESS;
}

void testStore(void)
{
	store * sttest = newStore(0, "Carrefour - rennes", 100, 70);

	Store_addSection(sttest, 01, t_section, 5, 5, 10, 3);
	Store_addSection(sttest, 02, t_section, 20, 20, 10, 3);
	Store_addSection(sttest, 02, t_wall, 100, 1, 0, 0);
	Store_addSection(sttest, 03, t_wall, 0, 99, 100, 1);
	Store_addSection(sttest, 04, t_wall, 0, 0, 100, 1);
	Store_addSection(sttest, 06, t_wall, 0, 0, 1, 100);
	Store_addSection(sttest, 05, t_wall, 99, 0, 1, 100);
	Store_addSection(sttest, 07, t_wall, 18, 18, 5, 5);

	Store_addItem(sttest, 22, legumes_vert, "salade");
	Store_addItem(sttest, 23, legumes_vert, "haricot vert");
	Store_addItem(sttest, 24, legumes_vert, "patates");
	Store_addItem(sttest, 25, legumes_vert, "poireau");
	Store_addItem(sttest, 26, legumes_vert, "concombre");
	Store_addItem(sttest, 27, legumes_vert, "petits poids");
	Store_addItem(sttest, 28, legumes_vert, "choux");
	Store_addItem(sttest, 29, legumes_vert, "avocat");
	Store_addItem(sttest, 30, fromage, "comté");
	Store_addItem(sttest, 31, fromage, "gouda");
	Store_addItem(sttest, 32, fromage, "bleu");
	Store_addItem(sttest, 22, legumes_vert, "asperge");

	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 22), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 23), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 24), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 25), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 26), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 27), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 28), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 29), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 30), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 31), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 32), 9, 2);
	Section_addItem(findSectionPointerId(sttest->allocated_sections, 01), findItemPointerId(sttest->allocated_stock, 22), 9, 2);


	Section_removeItem(findItemPointerId(findSectionPointerId(sttest->allocated_sections, 01)->stock, 31));

	Store_print(sttest);
	Store_delete(sttest);

	printf("bloc alloue : %d\n", myCheck());
}