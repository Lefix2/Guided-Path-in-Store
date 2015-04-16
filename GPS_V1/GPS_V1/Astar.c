#include "Astar.h"
#include "AstarList.h"
#include "Store.h"


nodeAstar * nodeAstar_new(coord pos, nodeAstar *parent)
{
	nodeAstar *newn = (nodeAstar*)malloc(sizeof(nodeAstar));

	newn->pos = pos;
	newn->h = 0;
	newn->g = 0;
	newn->f = 0;
	newn->parent = parent;

	return newn;
}

int nodeAstar_delete(nodeAstar * nodeAstar)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	free(nodeAstar);
	return EXIT_SUCCESS;
}

int nodeAstar_set_pos(nodeAstar *nodeAstar, coord pos)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->pos = pos;
	return EXIT_SUCCESS;
}

int nodeAstar_set_h(nodeAstar *nodeAstar, int h)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->h = h;
	return EXIT_SUCCESS;
}

int nodeAstar_set_g(nodeAstar *nodeAstar, int g)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->g = g;
	return EXIT_SUCCESS;
}

int nodeAstar_set_f(nodeAstar *nodeAstar, int f)
{
	if (nodeAstar == NULL)
		return EXIT_FAILURE;
	nodeAstar->f = f;
	return EXIT_SUCCESS;
}

coord nodeAstar_get_pos(nodeAstar *nodeAstar)
{
	return nodeAstar->pos;
}

int nodeAstar_get_h(nodeAstar *nodeAstar)
{
	return nodeAstar->h;
}

int nodeAstar_get_g(nodeAstar *nodeAstar)
{
	return nodeAstar->g;
}

int nodeAstar_get_f(nodeAstar *nodeAstar)
{
	return nodeAstar->f;
}

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

void update_neighbours(nodeAstar *n,coord end ,store *st_source, astarList *opened, astarList *closed)
{
	//x and y variation for each 8 neighbours
	coord dxdy[] = { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 } };
	int neighbour;
	nodeAstar *nodeNeighbour;
	for (neighbour = 0; neighbour < 8; neighbour++)
	{
		coord neighbourPos = add_coord(dxdy[neighbour], n->pos);
		//if there's no neighbour(ou of the map)
		if (!is_in_square(neighbourPos, zero, st_source->size))
			continue;
		//if the neighbour is an obstacle impassable
		if (st_source->cartography[neighbourPos.x][neighbourPos.y] == 1)
			continue;
		//if the neighbour is already in closed list
		if (nodeAstar_find_pos(closed, neighbourPos) != NULL)
			continue;

		//We can create the node
		nodeNeighbour = nodeAstar_new(neighbourPos, n);
		//g = cost of the parent from the start + cost from parent to child
		nodeAstar_set_g(nodeNeighbour, n->g + GENERAL_COST);
		//h = distant to the end
		nodeAstar_set_h(nodeNeighbour, manhattan_distance(nodeNeighbour->pos, end));
		//f = g + h
		nodeAstar_set_f(nodeNeighbour, nodeNeighbour->g + nodeNeighbour->h);

		//searching for an existing node with this coord in the opened list
		nodeAstar *nodeFound = nodeAstar_find_pos(opened, neighbourPos);
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
			//open_node(nodeNeighbour, opened);
			astarList_insert_sort(opened, nodeNeighbour);
		}
	}
	
}

nodeAstar *best_node(astarList *l)
{

	return astarList_get_first(l);
}

int update_node(astarList *l, nodeAstar *nNew, nodeAstar *nOld)
{
	if (nodeAstar_delete(astarList_delete_single(l, nOld)) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return astarList_insert_sort(l, nNew);
}

int open_node(nodeAstar *n, astarList *opened)
{
	return astarList_insert_sort(opened, n);
}

int close_node(nodeAstar *n, astarList *opened, astarList *closed)
{
	if (astarList_delete_single(opened, n) == NULL)
		return EXIT_FAILURE;
	return astarList_insert_last(closed, n);
}

int findpath(coord **coordonates, astarList *closed)
{
	nodeAstar * currentNode = astarList_get_last(closed);
	*coordonates = (coord**)malloc(0);
	int nb = 0;
	while (currentNode != NULL)
	{
		nb++;
		*coordonates = (coord*)realloc(*coordonates, nb*sizeof(coord));
		*(*coordonates + nb-1) = currentNode->pos;
		currentNode = currentNode->parent;
	}
	return nb;
}

int astar(store *st_source, coord start, coord end, coord **path)
{
	astarList *opened = astarList_new();
	astarList *closed = astarList_new();

	nodeAstar *current;
	current = nodeAstar_new(start, NULL);
	open_node(current, opened);
	close_node(current, opened, closed);
	update_neighbours(current, end, st_source, opened, closed);

	//while the current node isn't the last and the opened list isn't empty
	//note : for big area without issue, the program will calculate all the node
	//->need an update :)
	while (!(same_coord(current->pos, end)) && !astarList_is_empty(opened))
	{
		//found the best node
		current = best_node(opened);
		//add it to the closed path
		close_node(current, opened, closed);
		//update his neighbours
		update_neighbours(current, end, st_source, opened, closed);
	}
	if (astarList_is_empty(opened))
	{
		printf("Astar : No path found\n");
		return 0;
	}
	int nbNodes = findpath(path, closed);

	astarList_delete(opened);
	astarList_delete(closed);

	return nbNodes;
}