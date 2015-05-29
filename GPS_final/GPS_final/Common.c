#include "Common.h"
#include <math.h>

gboolean same_coord(coord p1, coord p2)
{
	return(p1.x == p2.x && p1.y == p2.y);
}

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

gboolean is_in_square(coord p, coord sqrBase, coord sqrSize)
{
	return(betwn(sqrBase.x, p.x, sqrBase.x + sqrSize.x - 1, TRUE) && betwn(sqrBase.y, p.y, sqrBase.y + sqrSize.y - 1, TRUE));
}

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

coord add_coord(coord c1, coord c2)
{
	coord newcoord;
	newcoord.x = c1.x + c2.x;
	newcoord.y = c1.y + c2.y;
	return newcoord;
}

int manhattan_distance(coord p1, coord p2)
{
	return (abs(p1.x - p2.x) + abs(p1.y - p2.y));
}

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

void free_double_int_pointer(int **pt, int size1, int size2)
{
	int i;

	for (i = 0; i < size1; i++)
	{
		free(*(pt + i));
	}
	free(pt);
}

void free_double_char_pointer(char **pt, int size1, int size2)
{
	int i;

	for (i = 0; i < size1; i++)
	{
		free(*(pt + i));
	}
	free(pt);
}

void rotab(int *tab, int size)
{
	int i, tmp = tab[size - 1];

	for (i = size - 1; i > 0; i--)
		tab[i] = tab[i - 1];

	tab[0] = tmp;
}

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