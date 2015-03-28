#include "Common.h"

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

gboolean onBorder(int x, int y, int x_min, int x_max, int y_min, int y_max)
{
	if (betwn(x_min, x, x_max-1, TRUE) && (y == y_min || y == y_max-1))
		return TRUE;
	if (betwn(y_min, y, y_max-1, TRUE) && (x == x_min || x == x_max-1))
		return TRUE;
	return FALSE;
}