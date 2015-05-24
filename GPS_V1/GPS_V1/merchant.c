#include "merchant.h"
#include "Astar.h"
#include "Shopping.h"
#include "Store.h"
#include "Section.h"
#include "SectionList.h"
#include "Item.h"
#include "ItemList.h"

#define random(x) rand()%x
#define NBPOP 20			/* number of population to mutate*/
#define ITERATION_FACTOR 500  /* higher factor for best results, lower for higher perf*/
#define PUNISH_START_END TRUE /*force the algo to keep the first and last item given at first and last position*/

int merchant_optimise_shopping(shopping *shopping)
{
	int i, j;

	printf("Merchant : starting...\n");
	/*---------------------------------------------------------------*/
	/***************initialize start and end position*****************/
	/*---------------------------------------------------------------*/
	printf("Merchant : initialize start and end...");
	sectionList *sections = store_get_allocatedSections(shopping->Store);
	section *tmp_sec;
	coord tmp_size;

	//start
	sectionPointerList_set_on_first(sections);
	while (section_get_type(sectionPointerList_get_current(sections)) != t_entrance)
	{
		sectionPointerList_next(sections);
	}
	tmp_sec = sectionPointerList_get_current(sections);
	tmp_size = section_get_size(tmp_sec);
	tmp_size.x /= 2;
	tmp_size.y /= 2;

	item_set_section(shopping->start, tmp_sec);
	item_set_pos(shopping->start, tmp_size.x, tmp_size.y);

	//end
	sectionPointerList_set_on_first(sections);
	while (section_get_type(sectionPointerList_get_current(sections)) != t_checkout)
	{
		sectionPointerList_next(sections);
	}
	tmp_sec = sectionPointerList_get_current(sections);
	tmp_size = section_get_size(tmp_sec);
	tmp_size.x /= 2;
	tmp_size.y /= 2;

	item_set_section(shopping->end, tmp_sec);
	item_set_pos(shopping->end, tmp_size.x, tmp_size.y);
	printf("done\n");

	/*---------------------------------------------------------------*/
	/**********************get all paths******************************/
	/*---------------------------------------------------------------*/
	printf("Merchant : get all path...");
	//creating a temporary list to work on
	itemList *tmp_list;
	tmp_list = itemPointerList_new();

	itemPointerList_set_on_first(shopping->List);
	while (!itemPointerList_is_out_of(shopping->List))
	{
		itemPointerList_insert_last(tmp_list, itemPointerList_get_current(shopping->List));
		itemPointerList_next(shopping->List);
	}
	//adding start and end to the list
	itemPointerList_insert_first(tmp_list, shopping->start);
	itemPointerList_insert_last(tmp_list, shopping->end);

	//counting the number of item in the list
	int nbItems = 0;
	int s, e;
	itemPointerList_set_on_first(tmp_list);
	while (!itemPointerList_is_out_of(tmp_list))
	{
		itemPointerList_next(tmp_list);
		nbItems++;
	}

	//initializing a tab wich will contain all distance between each item
	int ** pathLenghts = (int**)calloc(nbItems, sizeof(int*));
	for (i = 0; i < nbItems; i++)
	{
		*(pathLenghts + i) = (int*)calloc(nbItems, sizeof(int));
	}

	//set all pathlengt of each item with itself to 0
	for (i = 0; i < nbItems; i++)
	{
		pathLenghts[i][i] = 0;
	}

	coord start, end;
	item *currentItem;

	//compute the map for the astar
	Store_computeCartography(shopping->Store, TRUE);

	for (s = 0; s < nbItems-1; s++)
	{
		//set current item of the list on the s'th position
		itemPointerList_set_on_first(tmp_list);
		for (i = 0; i < s;i++)
			itemPointerList_next(tmp_list);

		//get the start point
		currentItem = itemPointerList_get_current(tmp_list);
		start = add_coord(item_get_pos(currentItem), section_get_pos(item_get_section(currentItem)));
		for (e = s+1; e < nbItems; e++)
		{
			itemPointerList_next(tmp_list);//set current item of the list on the s+e'th position
			currentItem = itemPointerList_get_current(tmp_list);
			end = add_coord(item_get_pos(currentItem), section_get_pos(item_get_section(currentItem)));
			pathLenghts[s][e] = pathLenghts[e][s] = astar(shopping->Store, start, end, NULL);
		}
	}
	pathLenghts[0][nbItems - 1] = pathLenghts[nbItems - 1][0] = 0; //little hack to be sure that start and end will follow in merchant algo
	printf("done\n");

	/*---------------------------------------------------------------*/
	/*********************compute merchant algo***********************/
	/*---------------------------------------------------------------*/
	printf("Merchant : compute algo...");
	int *path = merchant_find_path(nbItems, pathLenghts);

	while (path[0] != 0)
	{
		rotab(path, nbItems);
	}

	printf("done\n");

	/*---------------------------------------------------------------*/
	/***********************create sorted list************************/
	/*---------------------------------------------------------------*/
	printf("Merchant : sorting shopping list...");
	int pos;
	//empty shopping list
	itemPointerList_set_on_first(shopping->List);
	while (!itemPointerList_is_empty(shopping->List))
	{
		itemPointerList_delete_current(shopping->List);
	}

	//fill it with ordonate path
	for (i = 0; i < nbItems; i++)
	{
		pos = path[i];
		if (pos == 0 || pos == nbItems - 1)
			continue;
		itemPointerList_set_on_first(tmp_list);
		for (j = 0; j < pos; j++)
		{
			itemPointerList_next(tmp_list);
		}
		itemPointerList_insert_last(shopping->List, itemPointerList_get_current(tmp_list));
	}
	printf("done\n");

	merchant_connect_paths(shopping);
	printf("Merchant : finished!\n\n");
}

int merchant_connect_paths(shopping *shopping)
{
	//to enter this function merchant algorithm must be done

	//first and last coordonate of the shopping
	coord start, end;
	sectionList *sections = store_get_allocatedSections(shopping->Store);

	//calculate all paths
	item *current, *old;
	itemList *list = shopping->List;
	coord c1, c2;
	itemPointerList_set_on_first(list);

	//first path
	current = itemPointerList_get_current(list);
	c1 = add_coord(item_get_pos(shopping->start), section_get_pos(item_get_section(shopping->start)));
	c2 = add_coord(item_get_pos(current), section_get_pos(item_get_section(current)));
	astar(shopping->Store, c1, c2, current->pathTo);
	old = current;
	itemPointerList_next(list);

	//other paths
	while (!itemPointerList_is_out_of(list))
	{
		current = itemPointerList_get_current(list);
		c1 = add_coord(item_get_pos(old), section_get_pos(item_get_section(old)));
		c2 = add_coord(item_get_pos(current), section_get_pos(item_get_section(current)));
		astar(shopping->Store, c1, c2, current->pathTo);
		old = current;
		itemPointerList_next(list);
	}

	//last path
	c1 = add_coord(item_get_pos(old), section_get_pos(item_get_section(old)));
	c2 = add_coord(item_get_pos(shopping->end), section_get_pos(item_get_section(shopping->end)));
	astar(shopping->Store, c1, c2, shopping->end->pathTo);

	return EXIT_SUCCESS;

}

//main function of tsp
int* merchant_find_path(int nbr, int **pathlen)
{
	int i;
	int maxpath = merchant_find_longest(nbr, pathlen);
	int fx[20];
	int posmin[2],
		posmax[2];
	int **path = alloc_double_int_pointer(20, nbr);
	int **child = alloc_double_int_pointer(2, nbr);
	int *ret = (int*)calloc(nbr, sizeof(int));

	merchant_init_population(nbr, pathlen, path);
	merchant_evaluate(nbr, pathlen, path, fx, maxpath);
	merchant_selection(fx, posmin, posmax);
	merchant_crossover(nbr, posmin, path, child);
	merchant_mutation(nbr, child);
	merchant_insert(nbr, child, posmax, path);

	for (i = 1; i < nbr * ITERATION_FACTOR; i++)
	{
		merchant_evaluate(nbr, pathlen, path, fx, maxpath);
		merchant_selection(fx, posmin, posmax);
		merchant_crossover(nbr, posmin, path, child);
		merchant_mutation(nbr, child);
		merchant_insert(nbr, child, posmax, path);

	}

	merchant_evaluate(nbr, pathlen, path, fx, maxpath);
	merchant_selection(fx, posmin, posmax);

	for (int i = 0; i < nbr; i++)
	{
		ret[i] = path[posmin[0]][i];
	}
	/*
	for (int g = 0; g < 20; g++)
	{
	for (int h = 0; h < nbr; h++)
	{
	printf("%2d ", path[g][h]);
	}
	printf("%d\n",fx[g]);
	}
	*/

	free_double_int_pointer(path, 20, nbr);
	free_double_int_pointer(child, 2, nbr);

	return ret;
}

void merchant_init_population(int nbr, int **pathlen, int **path)
{
	int i, j, k;

	for (i = 0; i < NBPOP; i++)
	{
		for (j = 0; j < nbr; j++)
		{
			path[i][j] = random(nbr);

			for (k = j - 1; k >= 0; k--)
			{
				if (path[i][j] == path[i][k]) //checking to avoid repetition
				{
					path[i][j] = random(nbr);
					k = j;
				}
			}
		}
	}
}

void merchant_evaluate(int nbr, int **pathlen, int **path, int *fx, int maxpath)
{
	int i, j;
	int a, b;
	int sum;

	//calculating the sum of the path taken by all individue
	for (i = 0; i < NBPOP; i++)
	{
		sum = 0;
			if (path[i][0] != 0)
				sum += PUNISH_START_END*maxpath*nbr;
			if (path[i][nbr - 1] != nbr - 1)
				sum += PUNISH_START_END*maxpath*nbr;
		for (j = 0; j < nbr - 1; j++)
		{
			a = path[i][j];
			b = path[i][j + 1];
			sum += pathlen[a][b];
		}
		fx[i] = sum;
	}
}

void merchant_selection(int *fx, int posmin[2], int posmax[2])
{
	int i;
	int min1 = fx[0],
		min2 = fx[0];
	int max1 = 0,
		max2 = 0;

	posmin[0] = 0;
	posmin[1] = 0;
	posmax[0] = 0;
	posmax[1] = 0;

	//calculating the minimum position
	for (i = 1; i < NBPOP; i++)
	{
		if (fx[i] < min1)
		{
			min1 = fx[i];
			posmin[0] = i;
		}
	}

	//calculating the second minimum position
	for (i = 1; i < NBPOP; i++)
	{
		if (fx[i] < min2 && i != posmin[0])
		{
			min2 = fx[i];
			posmin[1] = i;
		}
	}

	//calculating the maximum position
	for (i = 0; i < NBPOP; i++)
	{
		if (fx[i] > max1)
		{
			max1 = fx[i];
			posmax[0] = i;
		}
	}

	//calculating the second maximum position
	for (i = 0; i < NBPOP; i++)
	{
		if (fx[i] > max2 && i != posmax[0])
		{
			max2 = fx[i];
			posmax[1] = i;
		}
	}
}

void merchant_crossover(int nbr, int posmin[2], int **path, int **child)
{
	int i, j;
	int crosspt1, crosspt2;
	int temp1, temp2;
	int **temp;
	temp = alloc_double_int_pointer(2, nbr);

	//taking 2 cross points
	do
	{
		crosspt1 = random(nbr);
	} while (crosspt1 > nbr / 2);
	do
	{
		crosspt2 = random(nbr);
	} while (crosspt2 <= nbr / 2 + 1);

	for (j = 0; j < nbr; j++)
	{
		child[0][j] = path[posmin[0]][j];
		child[1][j] = path[posmin[1]][j];
	}

	//swapping the paths between two crosspoint
	int cnt = 0;

	for (j = crosspt1 + 1; j <= crosspt2; j++)
	{
		temp[1][cnt] = child[0][j];
		temp[0][cnt] = child[1][j];
		temp1 = child[0][j];
		child[0][j] = child[1][j];
		child[1][j] = temp1;
		cnt++;
	}

	int k, m;
	for (m = 0; m < 2; m++)
	{
		for (i = 0; i < crosspt1 + 1; i++) //taking the path before cross point
		{
			for (j = 0; j < cnt; j++) //comparing the path within crossover point
			{
				if (child[m][i] == temp[m][j]) //if found then
				{
					if (m == 0) //for child 1
					{
						temp2 = temp[1][j]; //take the path from child2 crossover

						for (k = 0; k < nbr; k++)
						{
							if (child[m][k] == temp2) //if still the path repeats then repeat the process again
							{
								temp2 = random(nbr);
								k = 0;
							}
						}

						child[m][i] = temp2; //finally putting the vallue in child
					}
					else //for child 2
					{
						temp2 = temp[0][j];
						for (k = 0; k < nbr; k++)
						{
							if (child[m][k] == temp2)
							{
								temp2 = random(nbr);
								k = 0;
							}
						}
						child[m][i] = temp2;
					}

				}
			}
		}
	}

	for (m = 0; m < 2; m++)
	{
		for (i = crosspt2 + 1; i < nbr; i++) //now checking the path after the second crosspoint
		{
			for (j = 0; j < cnt; j++) //comparing the path within cross over point
			{
				if (child[m][i] == temp[m][j]) //if found then
				{
					if (m == 0) //for child 1
					{
						temp2 = temp[1][j]; //take the path from child2 crossover
						for (k = 0; k < nbr; k++)
						{
							if (child[m][k] == temp2)
							{
								temp2 = random(nbr);
								k = 0;
							}
						}
						child[m][i] = temp2; //finally assigning the value
					}
					else //for child 2
					{
						temp2 = temp[0][j];
						for (k = 0; k < cnt; k++)
						{
							if (child[m][k] == temp2)
							{
								temp2 = random(nbr);
								k = 0;
							}
						}
						child[m][i] = temp2;
					}
				}
			}
		}
	}

	free_double_int_pointer(temp, 2, nbr);
}

//inserting the paths in population removing those having maximum fx
void merchant_insert(int nbr, int **child, int posmax[2], int **path)
{
	for (int j = 0; j < nbr; j++)
	{
		path[posmax[0]][j] = child[0][j];
		path[posmax[1]][j] = child[1][j];
	}
}

//performing mutation
void merchant_mutation(int nbr, int **child)
{
	int sel = random(2);
	int pos1 = random(nbr);
	int pos2 = random(nbr);
	int temp = child[sel][pos1];
	child[sel][pos1] = child[sel][pos2];
	child[sel][pos2] = temp;
}

//find the longest path
int merchant_find_longest(int nbr, int **pathlen)
{
	int s, e, maxlen = 0;
	for (s = 0; s < nbr - 1; s++)
	{
		for (e = s + 1; e < nbr; e++)
		{
			maxlen = max(maxlen, pathlen[s][e]);
		}
	}
	return maxlen;
}

void merchant_print_paths(int nbr, int **paths)
{
	for (int i = 0; i < nbr; i++)
	{
		for (int j = 0; j < nbr; j++)
		{
			printf(" %2d", paths[i][j]);
		}
		printf("\n");
	}
}
