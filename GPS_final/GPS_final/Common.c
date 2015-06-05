/*!
* \file  Common.c
* \brief functions for the entire project
* \author GPS team
* \date 13/12/2014
*/

#include "Common.h"
#include <math.h>

/*!
* \fn gboolean same_coord(coord p1, coord p2)
* \brief return if two points have the same coord
* \param[in] *p1 the first point
* \param[in] *p2 the second point
* \return true if the coordinates are the same, flase otherwise
*/
gboolean same_coord(coord p1, coord p2)
{
	return(p1.x == p2.x && p1.y == p2.y);
}

/*!
* \fn gboolean betwn(int a, int x, int b, gboolean equal)
* \brief return if a value is between two others
* \param[in] a the min value
* \param[in] x the value to test
* \param[in] b the max value
* \param[in] equal set to true if x can be equal to a or b
* \return true if x is between a or b, false otherwise
*/
gboolean betwn(int a, int x, int b, gboolean equal)
{
	switch (equal)
	{
	case TRUE :
		if (x >= a && x <= b)
			return TRUE;
		break;
	case FALSE :
		if (x > a && x < b)
			return TRUE;
		break;
	}
	return FALSE;
}

/*!
* \fn gboolean is_in_square(coord p, coord sqrBase, coord sqrSize)
* \brief say if a point is in a square
* \param[in] p the point to test
* \param[in] sqrBase the base of the square
* \param[in] sqrSize the size of the square
* \return true if p is in the sqrBase to sqrSize square, false otherwise
*/
gboolean is_in_square(coord p, coord sqrBase, coord sqrSize)
{
	return(betwn(sqrBase.x, p.x, sqrBase.x + sqrSize.x - 1, TRUE) && betwn(sqrBase.y, p.y, sqrBase.y + sqrSize.y - 1, TRUE));
}

/*!
* \fn gboolean on_border(coord pos, coord sqrBase, coord sqrSize, int borderSize)
* \brief say if a point is on a squares' borders
* \param[in] p the point to test
* \param[in] sqrBase the base of the square
* \param[in] sqrSize the size of the square
* \param[in] borderSize the size of the border we want to test in sqr
* \return true if p is in the sqrBase to sqrSize square's borders, false otherwise
*/
gboolean on_border(coord pos, coord sqrBase, coord sqrSize, int borderSize)
{
	//if the square only have border
	if ((sqrSize.x <= 2 || sqrSize.y <= 2) && borderSize > 0)
		return is_in_square(pos, sqrBase, sqrSize);
	//else
	coord excludeBase = sqrBase;
	excludeBase.x += borderSize;
	excludeBase.y += borderSize;
	coord excludeSize = sqrSize;
	excludeSize.x -= borderSize*2;
	excludeSize.y -= borderSize*2;

	return(is_in_square(pos, sqrBase, sqrSize) && !is_in_square(pos, excludeBase, excludeSize));
}

/*!
* \fn coord add_coord(coord c1, coord c2)
* \brief add x and y of to point
* \param[in] c1 the first point
* \param[in] c2 the second point
* \return the resulting point
*/
coord add_coord(coord c1, coord c2)
{
	coord newcoord;
	newcoord.x = c1.x + c2.x;
	newcoord.y = c1.y + c2.y;
	return newcoord;
}

/*!
* \fn int manhattan_distance(coord p1, coord p2)
* \brief compute manhattan distance between two points
* \param[in] p1 the first point
* \param[in] p2 the second point
* \return the manhattan distance
*/
int manhattan_distance(coord p1, coord p2)
{
	return (abs(p1.x - p2.x) + abs(p1.y - p2.y));
}

/*!
* \fn int **alloc_double_int_pointer(int size1, int size2)
* \brief allocate memory for a double pointer of int
* \param[in] size1 the size of **int allocation
* \param[in] size2 the size of *int allocation
* \return the new allocated double pointer
*/
int **alloc_double_int_pointer(int size1, int size2)
{
	int i;
	int **ret = (int**)calloc(size1, sizeof(int*));
	if (ret == NULL)
		return ret;

	for (i = 0; i < size1; i++)
	{
		*(ret + i) = (int*)calloc(size2, sizeof(int));
	}
	return ret;
}

/*!
* \fn char **alloc_double_char_pointer(int size1, int size2)
* \brief allocate memory for a double pointer of char
* \param[in] size1 the size of **char allocation
* \param[in] size2 the size of *char allocation
* \return the new allocated double pointer
*/
char **alloc_double_char_pointer(int size1, int size2)
{
	int i;
	char **ret = (char**)calloc(size1, sizeof(char*));
	if (ret == NULL)
		return ret;

	for (i = 0; i < size1; i++)
	{
		*(ret + i) = (char*)calloc(size2, sizeof(char));
	}
	return ret;
}

/*!
* \fn void free_double_int_pointer(int **pt, int size1, int size2)
* \brief free memory for a double pointer of char
* \param[in] pt the pointer to free
* \param[in] size1 the size of **int allocation
* \param[in] size2 the size of *int allocation
*/
void free_double_int_pointer(int **pt, int size1, int size2)
{
	int i;

	for (i = 0; i < size1; i++)
	{
		free(*(pt + i));
	}
	free(pt);
}

/*!
* \fn void free_double_char_pointer(char **pt, int size1, int size2)
* \brief free memory for a double pointer of char
* \param[in] pt the pointer to free
* \param[in] size1 the size of **char allocation
* \param[in] size2 the size of *char allocation
*/
void free_double_char_pointer(char **pt, int size1, int size2)
{
	int i;

	for (i = 0; i < size1; i++)
	{
		free(*(pt + i));
	}
	free(pt);
}

/*!
* \fn void rotab(int *tab, int size)
* \brief rotate the content of a tab of one step
* \param[in] tab pointer to the first element of the tab
* \param[in] size the tab size
*/
void rotab(int *tab, int size)
{
	int i, tmp = tab[size - 1];

	for (i = size - 1; i > 0; i--)
		tab[i] = tab[i - 1];

	tab[0] = tmp;
}

/*!
* \fn void mirrortab(int *tab, int size)
* \brief mirror the content of a tab
* \param[in] tab pointer to the first element of the tab
* \param[in] size the tab size
*/
void mirrortab(int *tab, int size)
{
	int i, tmp;

	for (i = 0; i < size / 2; i++)
	{
		tmp = tab[i];
		tab[i] = tab[size - 1 - i];
		tab[size - 1 - i] = tmp;
	}
}