#include <string.h>

#include "Store.h"
#include "Section.h"
#include "SectionList.h"
#include "Item.h"
#include "ItemList.h"
#include "Astar.h"

store * store_new(int id, char * name, int x_size, int y_size)
{
	store * st_new = (store *)malloc(sizeof(store));

	store_init(st_new);
	store_set_id(st_new, id);
	store_set_name(st_new, name);
	store_set_size(st_new, x_size, y_size);
	st_new->allocatedStock = itemPointerList_new();
	st_new->allocatedSections = sectionPointerList_new();
	Store_computeCartography(st_new);

	return st_new;
}

store * store_init(store * st_source)
{
	st_source->id = 0;
	st_source->name[0] = 0;
	st_source->size.x = 0;
	st_source->size.y = 0;
	st_source->allocatedStock = NULL;
	st_source->cartography = NULL;
	st_source->sprites = NULL;
	
	return st_source;
}

int store_delete(store * st_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	store_free_carto(st_source);
	store_delete_stock(st_source);
	store_delete_sections(st_source);
	if (st_source->sprites != NULL)
		g_object_unref(st_source->sprites);
	free(st_source);
	return EXIT_SUCCESS;
}

int store_set_id(store * st_source, int id)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	st_source->id = id;
	return EXIT_SUCCESS;
}

int store_set_name(store * st_source, char * name)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	strcpy(st_source->name, name);
	return EXIT_SUCCESS;
}

int store_set_size(store * st_source, int x_size, int y_size)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	store_free_carto(st_source);
	st_source->size.x = x_size;
	st_source->size.y = y_size;
	return EXIT_SUCCESS;
}

int store_set_sprites(store * st_source, GdkPixbuf *sprites)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	if (st_source->sprites != NULL)
		g_object_unref(sprites);
	st_source->sprites = sprites;
	return EXIT_SUCCESS;
}

int store_get_id(store * st_source)
{
	return st_source->id;
}

char * store_get_name(store * st_source)
{
	return st_source->name;
}

itemList *store_get_allocatedStock(store * st_source)
{
	return st_source->allocatedStock;
}

sectionList *store_get_allocatedSections(store * st_source)
{
	return st_source->allocatedSections;
}

int store_get_x_size(store * st_source)
{
	return st_source->size.x;
}

int store_get_y_size(store * st_source)
{
	return st_source->size.y;
}

GdkPixbuf *store_get_sprites(store * st_source)
{
	return st_source->sprites;
}

void store_print(store * st_source)
{
	printf("***** Store  *****\n");
	printf("ID    : %d\n", st_source->id);
	printf("name  : %s\n", st_source->name);
	printf("size X : %d\n", st_source->size.x);
	printf("     Y : %d\n", st_source->size.y);
	printf("\n");
	printf("->Section : ");
	sectionPointerList_print(st_source->allocatedSections);
	printf("->Cartography :\n");
	store_print_carto(st_source);
	printf("\n");
}

void store_print_carto(store * st_source){
	int x, y;
	for (y = 0; y < st_source->size.y; y++){
		for (x = 0; x < st_source->size.x; x++){
			printf("%d", st_source->cartography[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}


int store_free_carto(store * st_source)
{
	for (int i = 0; i < st_source->size.x; i++)
	{
		free(*(st_source->cartography+i));
	}
	free(st_source->cartography);
	st_source->cartography = NULL;
	return EXIT_SUCCESS;
}

int Store_computeCartography(store * st_source)
{
	//allocation de la mémoire
	if (st_source->cartography != NULL)
		store_free_carto(st_source);
	st_source->cartography = (int**)calloc(st_source->size.x, sizeof(int*));
	for (int i = 0; i < st_source->size.x; i++)
	{
		*(st_source->cartography + i) = (int*)calloc(st_source->size.y, sizeof(int));
	}

	//code calculant pour la position (x,y)  la valeur 0(vide) ou 1(obstacle) en fonction des sections
	int x,y;
	int x_pos, y_pos;
	int x_size, y_size;

	sectionPointerList_set_on_first(st_source->allocatedSections);
	while (!sectionPointerList_is_out_of(st_source->allocatedSections))
	{
		x_pos = st_source->allocatedSections->current->s->pos.x;
		y_pos = st_source->allocatedSections->current->s->pos.y;
		x_size = st_source->allocatedSections->current->s->size.x;
		y_size = st_source->allocatedSections->current->s->size.y;

		for (x = 0; x < x_size; x++){
			for (y = 0; y < y_size; y++){
				(st_source->cartography[x_pos + x][y_pos + y]) = 1;
			}
		}
		sectionPointerList_next(st_source->allocatedSections);
	}
	return EXIT_SUCCESS;
}

int store_add_item(store * st_source, int id, category category, char * name)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	item * new_i = item_new(id, category, name);
	item * tmp = itemPointerList_find_id(st_source->allocatedStock, id);
	if (tmp != NULL)
	{
		printf("error : Trying to add an Item with existing id in Store\n");
		printf("existing : "); item_print(tmp, TRUE);
		printf("new : "); item_print(new_i, TRUE);
		printf("\n");
		item_delete(new_i);
		return EXIT_FAILURE;
	}
	itemPointerList_insert_sort(st_source->allocatedStock, new_i);
	return EXIT_SUCCESS;
}

int store_add_section(store * st_source, int id, type s_type, int x_pos, int y_pos, int x_size, int y_size)
{
	int i, j;
	if (st_source == NULL)
		return EXIT_FAILURE;
	section * tmp = sectionPointerList_find_id(st_source->allocatedSections, id);
	if (tmp != NULL)
	{
		printf("error : Trying to add a section with existing id in Store\n");
		section_print(tmp, TRUE);
		printf("\n");
		return EXIT_FAILURE;
	}
	if (((x_size + x_pos) > st_source->size.x) || ((y_size + y_pos) > st_source->size.y)){
		printf("Error : Trying to add a section out of the store\n");
		return EXIT_FAILURE;
	}
	if (store_detect_collision(st_source, x_pos, y_pos, x_size, y_size))
	{
		printf("error : Trying to add a section on an existing section\n");
		return EXIT_FAILURE;
	}
	section * new_s = section_new(id, s_type);
	section_set_pos(new_s, x_pos, y_pos);
	section_set_size(new_s, x_size, y_size);
	sectionPointerList_insert_sort(st_source->allocatedSections, new_s);

	return EXIT_SUCCESS;
}

int store_delete_item(store * st_source, item * item)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	section_remove_item(item->section, item);
	return item_delete(itemPointerList_delete_single(st_source->allocatedStock, item));
}

int store_delete_stock(store * st_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	while (!itemPointerList_is_empty(st_source->allocatedStock))
	{
		item_delete(itemPointerList_delete_first(st_source->allocatedStock));
	}
	free(st_source->allocatedStock);
	return EXIT_SUCCESS;
}

int store_delete_section(store * st_source, section * s_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	return section_delete(sectionPointerList_delete_single(st_source->allocatedStock, s_source));
}

int store_delete_sections(store * st_source)
{
	if (st_source == NULL)
		return EXIT_FAILURE;
	while (!sectionPointerList_is_empty(st_source->allocatedSections))
	{
		section_delete(sectionPointerList_delete_first(st_source->allocatedSections));
	}
	free(st_source->allocatedSections);
	return EXIT_SUCCESS;
}

int store_detect_collision(store * st_source, int x_pos, int y_pos, int x_size, int y_size)
{
	int x, y;

	Store_computeCartography(st_source);
	for (x = 0; x < x_size; x++){
		for (y = 0; y < y_size; y++){
			if (st_source->cartography[x_pos + x][y_pos + y] != 0){
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

void testStore(void)
{
	int magsizex = 50;
	int magsizey = 50;

	store * sttest = store_new(0, "Carrefour - rennes", magsizex, magsizey);

	store_add_section(sttest, 01, t_section, 3, 3, 7, 3);
	store_add_section(sttest, 02, t_section, 18, 18, 10, 3);
	store_add_section(sttest, 03, t_wall, 0, 1, 1, magsizey - 1);
	store_add_section(sttest, 04, t_wall, 1, magsizey - 1, magsizex - 1, 1);
	store_add_section(sttest, 06, t_wall, magsizex - 1, 0, 1, magsizey - 1);
	store_add_section(sttest, 05, t_wall, 0, 0, magsizex - 1, 1);
	store_add_section(sttest, 07, t_wall, 18, 18, 5, 5);

	store_add_item(sttest, 22, legumes_vert, "salade");
	store_add_item(sttest, 23, legumes_vert, "haricot vert");
	store_add_item(sttest, 24, legumes_vert, "patates");
	store_add_item(sttest, 25, legumes_vert, "poireau");
	store_add_item(sttest, 26, legumes_vert, "concombre");
	store_add_item(sttest, 27, legumes_vert, "petits poids");
	store_add_item(sttest, 28, legumes_vert, "choux");
	store_add_item(sttest, 29, legumes_vert, "avocat");
	store_add_item(sttest, 30, fromage, "comté");
	store_add_item(sttest, 31, fromage, "gouda");
	store_add_item(sttest, 32, fromage, "bleu");
	store_add_item(sttest, 22, legumes_vert, "asperge");

	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 22), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 23), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 24), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 25), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 26), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 27), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 28), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 29), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 30), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 31), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 32), 6, 2);
	section_add_item(sectionPointerList_find_id(sttest->allocatedSections, 01), itemPointerList_find_id(sttest->allocatedStock, 22), 6, 2);


	section_remove_item(itemPointerList_find_id(sectionPointerList_find_id(sttest->allocatedSections, 01)->stock, 31));

	Store_computeCartography(sttest);
	store_print(sttest);
	store_delete(sttest);

	printf("bloc alloue : %d\n", myCheck());
}