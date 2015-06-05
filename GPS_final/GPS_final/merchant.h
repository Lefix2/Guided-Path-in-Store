/*!
* \file  merchant.h
* \brief Header of merchant.c
* \author GPS team
* \date 13/12/2014
*
* Contain prototype of itemList
*/

#ifndef MERCHANT_H
#define MERCHANT_H

#include "Common.h"

int merchant_optimise_shopping(shopping *shopping);

int* merchant_find_path(int nbr, int **pathlen, int *bestfx);

int merchant_connect_paths(shopping *shopping);
void merchant_init_population(int nbr, int **pathlen, int **path);
void merchant_evaluate(int nbr, int **pathlen, int **path, int *fx, int maxpath);
void merchant_selection(int *fx, int posmin[2], int posmax[2]);
void merchant_crossover(int nbr, int posmin[2], int **path, int **child);
void merchant_insert(int nbr, int **child, int posmax[2], int **path);
void merchant_mutation(int nbr, int **child);
int merchant_find_longest(int nbr, int **pathlen);

void merchant_print_paths(int nbr, int **paths);

#endif // !MERCHANT_H
