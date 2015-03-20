#include "Common.h"

boolean betwn(int a, int x, int b, boolean equal)
{
	switch (equal)
	{
	case true :
		if (x >= a && x <= b)
			return true;
		break;
	case false :
		if (x > a && x < b)
			return true;
		break;
	}
	return false;
}

boolean onBorder(int x, int y, int x_min, int x_max, int y_min, int y_max)
{
	if (betwn(x_min, x, x_max, true) && (y == y_min || y == y_max))
		return true;
	if (betwn(y_min, y, y_max, true) && (x == x_min || x == x_max))
		return true;
	return false;
}