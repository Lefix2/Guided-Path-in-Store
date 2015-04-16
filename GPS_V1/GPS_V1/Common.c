#include "Common.h"

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