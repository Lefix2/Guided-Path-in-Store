#ifndef ASTAR_H
#define ASTAR_H

#include "Common.h"

/*Chaque case du jeu est représentée par un objet noeud qui contient :
         - sa position dans la grille
         - son cout G : distance entre elle et son ascendant + cout G de son
           ascendant
         - son cout H : distance entre elle et le noeud final
         - son cout F : somme de G et H
		 - son parent
		*/
typedef struct nodeAstar nodeAstar;
struct nodeAstar
{
	coord pos;	 /*!< position in graph*/

	int g;		/*!<cost since start*/
	int h;		/*!<cost to end*/
	int f;		/*!<total cost g+h*/

	nodeAstar * parent;
};


#endif // !ASTAR_H
