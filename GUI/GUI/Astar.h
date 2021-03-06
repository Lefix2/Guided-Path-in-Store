#ifndef ASTAR_H
#define ASTAR_H

#include "Common.h"

/*!<this is the cost to go  to another node (*/
#define GENERAL_COST 10

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

int nodeAstar_set_pos(nodeAstar *nodeAstar, coord pos);
int nodeAstar_set_h(nodeAstar *nodeAstar, int h);
int nodeAstar_set_g(nodeAstar *nodeAstar, int g);
int nodeAstar_set_f(nodeAstar *nodeAstar, int f);

coord nodeAstar_get_pos(nodeAstar *nodeAstar);
int nodeAstar_get_h(nodeAstar *nodeAstar);
int nodeAstar_get_g(nodeAstar *nodeAstar);
int nodeAstar_get_f(nodeAstar *nodeAstar);

nodeAstar *nodeAstar_find_pos(astarList *l, coord pos);

void update_neighbours(nodeAstar *n, coord end, store *st_source, astarList *opened, astarList *closed);
nodeAstar *best_node(astarList *l);
int update_node(astarList *l, nodeAstar *nNew, nodeAstar *nOld);
int open_node(nodeAstar *n, astarList *opened);
int close_node(nodeAstar *n, astarList *opened, astarList *closed);
int findpath(coord *coordonates, astarList *closed);
int astar(store *st_source, coord start, coord end, coord *path);

void testAstar(void);

#endif // !ASTAR_H
