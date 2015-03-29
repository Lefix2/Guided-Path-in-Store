/*!
 * \file  myAlloc.c
 * \brief The code file used to manage a personalized dynamic memory management.
 * \author EII
 * \date 16/12/2013
 * It redefines the malloc and free functions.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "MyAlloc.h"

int nb_block = 0;

/*!
 * \fn  void* myMalloc(unsigned int size, char* file,  char * func, int line)
 * \brief Redefines the malloc function behavior
 * In addition of the memory allocation, this function increases the counter
 * of allocated blocks.
 * \param[in] size the size of the block to be allocated
 * \param[in] file the file name where the memory allocation is required
 * \param[in] func the function name where the memory allocation is required
 * \param[in] line the line number where the memory allocation is required
 * \return void * the address of the allocated block
*/
void* myMalloc(unsigned int size, char* file,  char * func, int line)
{
	void * allocated_block;

	allocated_block = malloc ( size );

	if (allocated_block != NULL)
	{

        nb_block ++;
        printf("In file %s,\n\t function %s,\n\t\t line %d :\n\t\t\t allocated block at memory address: %p\n",file,func,line,allocated_block);
	}

    /*
    printList(&l);
    printf("**** ending myAlloc\n");
    */
	return allocated_block;
}

/*!
 * \fn  void myFree(void* block, char* file,  char * func, int line)
 * \brief Redefines the free function behavior
 * In addition of the memory deallocation, this function decreases the counter
 * of allocated blocks.
 * \param[in] block the address of the block to be deallocated
 * \param[in] file the file name where the memory deallocation is required
 * \param[in] func the function name where the memory deallocation is required
 * \param[in] line the line number where the memory deallocation is required
*/
void myFree(void* block, char* file,  char * func, int line)
{

    if(block != NULL)
    {
        nb_block --;
        free(block);
        printf("In file %s,\n\t function %s,\n\t\t line %d :\n\t\t\t freed block at memory address: %p\n",file, func, line, block);
    }
}
/*!
 * \fn  int myCheck()
 * \brief Check if every allocated block has been freed
 * It relies on the counter of allocated blocks
 * \return int the number of allocated blocks
*/
int myCheck()
{
    return nb_block;
}

