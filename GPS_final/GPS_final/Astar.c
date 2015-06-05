/*!
* \file  Astar.c
* \brief Used to compute astar algorithm between two points in a store
* \author GPS team
* \date 16/12/2013
*/

#include "Astar.h"
#include "AstarList.h"
#include "Store.h"

/*!
* \fn nodeAstar * nodeAstar_new(coord pos, nodeAstar *parent)
* \brief Create a new astar node
* \param[in] pos the pos of the node
* \param[in] *parent the parent node
* \return the new allocated node
*/
nodeAstar * nodeAstar_new(coord pos, nodeAstar *parent)
{
	nodeAstar *newn = (nodeAstar*)malloc(sizeof(nodeAstar));

	newn->pos = pos;		/*!<the pos in the cartesien domain*/
	newn->h = 0;			/*!<the cost from start*/
	newn->g = 0;			/*!<the estimated distance to end*/
	newn->f = 0;			/*!<the sum of g and h*/
	newn->parent = parent;	/*!<is the parent node*/

	return newn;
}

/*!
* \fn int nodeAstar_delete(nodeAstar * nodeAstar)
* \brief Delete an astar node
* \param[in] nodeAstar pointer to the node
* \return EXIT_SUCCES if OK
*/
int nodeAstar_delete(nodeAstar * nodeAstar)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	free(nodeAstar);
	return EXIT_SUCCESS;
}

/*!
* \fn path * path_new()
* \brief Allocate memory for a path
* \return a pointer to the new path
*/
path * path_new()
{
	path * newpath = (path*)malloc(sizeof(path));

	newpath->coordinates = (coord*)malloc(0);
	newpath->nb_coord = 0;

	return newpath;
}

/*!
* \fn int path_delete(path *path)
* \brief free memory of a path
* \param[in] path pointer to the path
* \return EXIT_SUCCESS if OK
*/
int path_delete(path *path)
{
	if (path == NULL)
		return EXIT_FAILURE;
	free(path->coordinates);
	free(path);

	return EXIT_SUCCESS;
}

/*!
* \fn path_reset(path *path)
* \brief set a path to a single value of 0
* \param[in] path the path to reset
* \return EXIT_SUCCESS if OK
*/
int path_reset(path *path)
{
	if (path == NULL)
		return EXIT_FAILURE;
	path->coordinates = (coord*)realloc(path->coordinates, 0);
	path->nb_coord = 0;

	return EXIT_SUCCESS;
}

/*!
* \fn path_add_node(path *path, coord newcoord)
* \brief add a node to the path
* \param[in] path the path to expand
* \param[in] the coordinate of the new pathpoint
* \return EXIT_SUCCESS if OK
*/
int path_add_node(path *path, coord newcoord)
{
	path->nb_coord++;
	path->coordinates = (coord*)realloc(path->coordinates, path->nb_coord*sizeof(coord));
	*(path->coordinates + path->nb_coord - 1) = newcoord;
	return path->nb_coord;
}

/*!
* \fn nodeAstar_set_pos(nodeAstar *nodeAstar, coord pos)
* \brief Set position of an astar node
* \param[in] nodeAstar the node to modify
* \param[in] the position
* \return EXIT_SUCCESS if OK
*/
int nodeAstar_set_pos(nodeAstar *nodeAstar, coord pos)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->pos = pos;
	return EXIT_SUCCESS;
}

/*!
* \fn nodeAstar_set_h(nodeAstar *nodeAstar, int h)
* \brief Set h value of an astar node
* \param[in] nodeAstar the node to modify
* \param[in] h the h value
* \return EXIT_SUCCESS if OK
*/
int nodeAstar_set_h(nodeAstar *nodeAstar, int h)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->h = h;
	return EXIT_SUCCESS;
}

/*!
* \fn nodeAstar_set_g(nodeAstar *nodeAstar, int g)
* \brief Set g value of an astar node
* \param[in] nodeAstar the node to modify
* \param[in] g the g value
* \return EXIT_SUCCESS if OK
*/
int nodeAstar_set_g(nodeAstar *nodeAstar, int g)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->g = g;
	return EXIT_SUCCESS;
}

/*!
* \fn nodeAstar_set_f(nodeAstar *nodeAstar, int f)
* \brief Set f value of an astar node
* \param[in] nodeAstar the node to modify
* \param[in] f the f value
* \return EXIT_SUCCESS if OK
*/
int nodeAstar_set_f(nodeAstar *nodeAstar, int f)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->f = f;
	return EXIT_SUCCESS;
}

/*!
* \fn coord nodeAstar_get_pos(nodeAstar *nodeAstar)
* \brief Get the pos of an astar node
* \param[in] nodeAstar the astar node
* \return the coordinates of the node
*/
coord nodeAstar_get_pos(nodeAstar *nodeAstar)
{
	return nodeAstar->pos;
}

/*!
* \fn int nodeAstar_get_h(nodeAstar *nodeAstar)
* \brief Get the h value of an astar node
* \param[in] nodeAstar the astar node
* \return the h value of the node
*/
int nodeAstar_get_h(nodeAstar *nodeAstar)
{
	return nodeAstar->h;
}

/*!
* \fn int nodeAstar_get_g(nodeAstar *nodeAstar)
* \brief Get the g value of an astar node
* \param[in] nodeAstar the astar node
* \return the g value of the node
*/
int nodeAstar_get_g(nodeAstar *nodeAstar)
{
	return nodeAstar->g;
}

/*!
* \fn int nodeAstar_get_f(nodeAstar *nodeAstar)
* \brief Get the f value of an astar node
* \param[in] nodeAstar the astar node
* \return the f value of the node
*/
int nodeAstar_get_f(nodeAstar *nodeAstar)
{
	return nodeAstar->f;
}

/*!
* \fn nodeAstar *nodeAstar_find_pos(astarList *l, coord pos)
* \brief Find an astar node in a astar nodelist giving his coordinate
* \param[in] l the pointer to the astarlist
* \param[in] pos the pos to search for
* \return A pointer to node if found, NULL else
*/
nodeAstar *nodeAstar_find_pos(astarList *l, coord pos)
{
	astarList_set_on_first(l);
	while (!astarList_is_out_of(l))
	{
		if (same_coord(astarList_get_current(l)->pos, pos))
			return astarList_get_current(l);
		astarList_next(l);
	}
	return NULL;
}

/*!
* \fn void update_neighbours(nodeAstar *n, coord end, store *st_source, int **nodeControl, astarList *opened, astarList *closed)
* \brief A big part of the algorithm, update neighbours of a node
* \param[in] nodeAstar *n
* \param[in] end the end position
* \param[in] *st_source the store (environement) to compute astar
* \param[in] **nodeControl control the state of each node(for perf)
* \param[in] *opened the opened nodelist
* \param[in] *closed the closed nodelist
*/
void update_neighbours(nodeAstar *n, coord end, store *st_source, int **nodeControl, astarList *opened, astarList *closed)
{
	//x and y variation for each 8 neighbours
	coord dxdy[] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { -1, 1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
	int astar_cost[] = { 10, 20, 30, 40, 50, 60, 70, 80, 500, MY_INFINITY };
	//int astar_cost[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, MY_INFINITY };
	int neighbour, neighbour_cost;
	nodeAstar *nodeNeighbour;
	for (neighbour = 0; neighbour < 8; neighbour++)
	{
		coord neighbourPos = add_coord(dxdy[neighbour], n->pos);
		//if there's no neighbour(out of the map)
		if (!is_in_square(neighbourPos, zero, st_source->size))
			continue;
		neighbour_cost = astar_cost[st_source->cartography[neighbourPos.x][neighbourPos.y]];
		neighbour_cost = neighbour_cost + (neighbour_cost*(neighbour >= 4));// / 10;// path in diag a bit more expensive
		//if the neighbour is an obstacle impassable
		if (neighbour_cost >= MY_INFINITY)
			continue;
		//if the neighbour is already in closed list
		if (nodeControl[neighbourPos.x][neighbourPos.y] == CLOSED_NODE)
			continue;

		//We can create the node
		nodeNeighbour = nodeAstar_new(neighbourPos, n);
		//g = cost of the parent from the start + cost from parent to child
		nodeAstar_set_g(nodeNeighbour, n->g + neighbour_cost);
		//h = distant to the end
		nodeAstar_set_h(nodeNeighbour, manhattan_distance(nodeNeighbour->pos, end));
		//f = g + h
		nodeAstar_set_f(nodeNeighbour, nodeNeighbour->g + nodeNeighbour->h);

		//searching for an existing node with this coord in the opened list
		nodeAstar *nodeFound = NULL;
		if (nodeControl[neighbourPos.x][neighbourPos.y] == OPENED_NODE)
			nodeFound = nodeAstar_find_pos(opened, neighbourPos);
		//if the neighbor is already in the opened list
		if (nodeFound != NULL)
		{
			//if the path is cheeper replace the old node by our neighbour with better path
			if (nodeNeighbour->f < nodeFound->f)
			{
				update_node(opened, nodeNeighbour, nodeFound);
			}
			else free(nodeNeighbour);
			//else do nothing
		}
		else
		{
			//add the new node to the opened node
			open_node(nodeControl, nodeNeighbour, opened);
		}
	}
	
}

/*!
* \fn nodeAstar *best_node(astarList *l)
* \brief get the best node in a list
* \param[in] *l the list to search in
* \return the best node of the list
*/
nodeAstar *best_node(astarList *l)
{
	return astarList_get_first(l);
}

/*!
* \fn int update_node(astarList *l, nodeAstar *nNew, nodeAstar *nOld)
* \brief replace a node in a list
* \param[in] *l the list the node is in
* \param[in] *nNew the new node
* \param[in] *nOld the node to replace
* \return EXIT_SUCCES if OK
*/
int update_node(astarList *l, nodeAstar *nNew, nodeAstar *nOld)
{
	if (nodeAstar_delete(astarList_delete_single(l, nOld)) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return astarList_insert_sort(l, nNew);
}

/*!
* \fn int open_node(int **nodeControl, nodeAstar *n, astarList *opened)
* \brief put a node in the opened list
* \param[in] **nodeControl the indicator table
* \param[in] *n the node to open
* \param[in] *opened the opened list
* \return EXIT_SUCCES if OK
*/
int open_node(int **nodeControl, nodeAstar *n, astarList *opened)
{
	int ret = astarList_insert_last(opened, n);
	if (ret == EXIT_SUCCESS)
	{
		int x = n->pos.x;
		int y = n->pos.y;
		nodeControl[x][y] = OPENED_NODE;
	}

	return ret;
}

/*!
* \fn int close_node(int **nodeControl, nodeAstar *n, astarList *opened, astarList *closed)
* \brief put a node in closed list
* \param[in] **nodeControl the indicator table
* \param[in] *n the node to close
* \param[in] *opened the ckosed list
* \param[in] *closed the closed list
* \return EXIT_SUCCES if OK
*/
int close_node(int **nodeControl, nodeAstar *n, astarList *opened, astarList *closed)
{
	if (astarList_delete_single(opened, n) == NULL)
		return EXIT_FAILURE;

	int ret = astarList_insert_last(closed, n);
	if (ret == EXIT_SUCCESS)
	{
		int x = n->pos.x;
		int y = n->pos.y;
		nodeControl[x][y] = CLOSED_NODE;
	}

	return ret;
}

/*!
* \fn int findpath(path * path, astarList *closed)
* \brief find the path after astar was computed
* \param[in] *path the path found by astar
* \param[in] *closed the closed list
* \return EXIT_SUCCES if OK
*/
int findpath(path * path, astarList *closed)
{
	if (closed == NULL)
		return -1;
	int pathLenght = 0;
	nodeAstar * currentNode = astarList_get_last(closed);

	//set path to NULL will only return the min length between start and end
	if (path == NULL)
	{
		while (currentNode != NULL)
		{
			currentNode = currentNode->parent;
			pathLenght++;
		}
	}
	else
	{
		path_reset(path);

		while (currentNode != NULL)
		{
			path_add_node(path, currentNode->pos);
			currentNode = currentNode->parent;
			pathLenght++;
		}
	}

	return pathLenght;
}

/*!
* \fn int astar(store *st_source, coord start, coord end, path *path)
* \brief main function of astar
* \param[in] *st_source the store (environement)
* \param[in] start the start point
* \param[in] end the end point
* \param[in] *path the path found
* \return the length of the path found
*/
int astar(store *st_source, coord start, coord end, path *path)
{
	/*--------------------------------------------------------*/
	/*******************variable declaration*******************/
	/*--------------------------------------------------------*/

	//here we create a map representing the state of each node of the astar
	//this save a lots of CPU while searching for an existing opened/closed node
	int ** nodeControl = (int**)calloc(st_source->size.x, sizeof(int*));
	for (int i = 0; i < st_source->size.x; i++)
	{
		*(nodeControl + i) = (int*)calloc(st_source->size.y, sizeof(int));
	}
	//opened and closed nodes list
	astarList *opened = astarList_new();
	astarList *closed = astarList_new();

	nodeAstar *current;

	/*--------------------------------------------------------*/
	/****************algorithm initialisation******************/
	/*--------------------------------------------------------*/

	//specific to our application, set the end point to a walkable point
	int endCost = st_source->cartography[end.x][end.y];
	st_source->cartography[end.x][end.y] = STRONG_COST;

	//close the first node(start)
	current = nodeAstar_new(start, NULL);
	open_node(nodeControl, current, opened);
	close_node(nodeControl, current, opened, closed);
	update_neighbours(current, end, st_source,nodeControl, opened, closed);

	/*--------------------------------------------------------*/
	/*************************algorithm************************/
	/*--------------------------------------------------------*/

	//while the current node isn't the last and the opened list isn't empty
	//note : for big area without issue, the program will calculate all the node
	//->need an update :)
	while (!(same_coord(current->pos, end)) && !astarList_is_empty(opened))
	{
		//found the best node
		current = best_node(opened);
		//add it to the closed path
		close_node(nodeControl, current, opened, closed);
		//update his neighbours
		update_neighbours(current, end, st_source,nodeControl, opened, closed);
	}

	//restore the costvalue of the endpoint
	st_source->cartography[end.x][end.y] = endCost;

	//test if a path was found
	if (astarList_is_empty(opened) && !(same_coord(current->pos, end)))
	{
		printf("Astar : No path found\n");
		astarList_delete(opened);
		astarList_delete(closed);
		return -1;
	}

	/*--------------------------------------------------------*/
	/****************creation of the path**********************/
	/*--------------------------------------------------------*/

	int ret = findpath(path, closed);

	/*--------------------------------------------------------*/
	/**********************free memory*************************/
	/*--------------------------------------------------------*/
	for (int i = 0; i < st_source->size.x; i++)
	{
		free(*(nodeControl + i));
	}
	free(nodeControl);
	astarList_delete(opened);
	astarList_delete(closed);

	return ret;
}


void testAstar(void)
{
	int magsizex = 50;
	int magsizey = 50;

	store * sttest = store_new(0, "Carrefour - rennes", magsizex, magsizey);

	store_add_new_section(sttest, 01, t_section, 1, 3, 40, 3);
	store_add_new_section(sttest, 02, t_section, 10, 18, 39, 3);
	store_add_new_section(sttest, 03, t_wall, 0, 1, 1, magsizey - 1);
	store_add_new_section(sttest, 04, t_wall, 1, magsizey - 1, magsizex - 1, 1);
	store_add_new_section(sttest, 06, t_wall, magsizex - 1, 0, 1, magsizey - 1);
	store_add_new_section(sttest, 05, t_wall, 0, 0, magsizex - 1, 1);

	Store_computeCartography(sttest, TRUE);
	store_print_carto(sttest);

	coord start;
	coord end;
	path *path = path_new();
	int i;

	printf("start : \nX :");
	scanf("%d", &(start.x));
	printf("Y :");
	scanf("%d", &(start.y));
	printf("end : \nX :");
	scanf("%d", &(end.x));
	printf("Y :");
	scanf("%d", &(end.y));

	astar(sttest, start, end, path);
	for (i = 0; i < path->nb_coord; i++)
		sttest->cartography[path->coordinates[i].x][path->coordinates[i].y] = 2;
	path_delete(path);

	store_print_carto(sttest);
	store_delete(sttest);

	printf("bloc alloue : %d\n", myCheck());
}