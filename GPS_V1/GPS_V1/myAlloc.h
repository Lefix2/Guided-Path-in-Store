/*!
 * \file  myAlloc.h
 * \brief The header file used to manage a personalized dynamic memory management.
 * \author EII
 * \date 16/12/2013
 * It redefines the malloc and free function.
*/

#ifndef MYALLOC_H
#define MYALLOC_H


/*! \def MAX_FICHIER
* \brief The maximal size of a filename
*/
#define MAX_FICHIER 256

#ifdef MEMCHECK

#define malloc(x) myMalloc((x), __FILE__, __FUNCTION__, __LINE__)
#define calloc(x,y) myCalloc((x),(y), __FILE__, __FUNCTION__, __LINE__)
#define free(x) myFree((x), __FILE__, __FUNCTION__, __LINE__)

#endif

void* myMalloc(unsigned int size, char* file,  char * func, int line);
void myFree ( void* block, char* file,  char * func, int line);
int myCheck();

#endif
