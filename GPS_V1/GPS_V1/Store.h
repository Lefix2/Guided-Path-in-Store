#ifndef STORE_H
#define STORE_H

#include "Common.h"

store * newStore(char * name, int size_x, int size_y);
store * initStore(store * sourceStore);

#endif // !STORE_H