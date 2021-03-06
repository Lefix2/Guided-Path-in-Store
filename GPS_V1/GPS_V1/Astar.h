/**
* \file Astar.h
* \brief Header Astar.c
* \author GPSTeam
* \date 29/03/2015
*
* Contain prototypes of astar
*
*/

#ifndef ASTAR_H
#define ASTAR_H

#include "Common.h"

/*!<All costs to go  to another node*/
#define MY_INFINITY 9999
#define GENERAL_COST 0
#define MEDIUM_COST 5
#define STRONG_COST 8
#define INFINITY_COST 9

/*!<states for astar nodes*/
#define UNTRET_NODE 0 //untreated
#define OPENED_NODE 1 //treated but still opened
#define CLOSED_NODE 2 //closed

/**
* \struct nodeAstar
* \brief node representing a path point
*/
struct nodeAstar
{
	coord pos;				/*!< position in graph*/

	int g;					/*!<cost since start*/
	int h;					/*!<cost to end*/
	int f;					/*!<total cost g+h*/

	nodeAstar * parent;		/*!<parent node in path*/
};

typedef struct nodeAstarList nodeAstarList;
struct nodeAstarList
{
	nodeAstar * a;
	nodeAstarList * next;
};

nodeAstar * nodeAstar_new(coord pos, nodeAstar *parent);
int nodeAstar_delete(nodeAstar * nodeAstar);
path * path_new();
int path_delete(path *path);
int path_reset(path *path);
int path_add_node(path *path, coord newcoord);

int nodeAstar_set_pos(nodeAstar *nodeAstar, coord pos);
int nodeAstar_set_h(nodeAstar *nodeAstar, int h);
int nodeAstar_set_g(nodeAstar *nodeAstar, int g);
int nodeAstar_set_f(nodeAstar *nodeAstar, int f);

coord nodeAstar_get_pos(nodeAstar *nodeAstar);
int nodeAstar_get_h(nodeAstar *nodeAstar);
int nodeAstar_get_g(nodeAstar *nodeAstar);
int nodeAstar_get_f(nodeAstar *nodeAstar);

nodeAstar *nodeAstar_find_pos(astarList *l, coord pos);

void update_neighbours(nodeAstar *n, coord end, store *st_source, int **nodeControl, astarList *opened, astarList *closed);
nodeAstar *best_node(astarList *l);
int update_node(astarList *l, nodeAstar *nNew, nodeAstar *nOld);
int open_node(int **nodeControl, nodeAstar *n, astarList *opened);
int close_node(int **nodeControl, nodeAstar *n, astarList *opened, astarList *closed);
int findpath(path *path, astarList *closed);
int astar(store *st_source, coord start, coord end, path *path);

void testAstar(void);

#endif // !ASTAR_H
