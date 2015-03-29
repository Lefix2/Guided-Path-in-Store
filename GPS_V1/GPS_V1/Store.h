#ifndef STORE_H
#define STORE_H

#include "Common.h"

store * newStore(int id, char * name, int x_size, int y_size);
store * Store_init(store * st_source);
store Store_delete(store * st_source);

int Store_setId(store * st_source, int id);
int Store_setName(store * st_source, char * name);
int Store_setSize(store * st_source, int x_size, int y_size);

int Store_getId(store * st_source);
char * Store_getName(store * st_source);
int Store_getXSize(store * st_source);
int Store_getYSize(store * st_source);

int Store_computeCartography(store * st_source);

void testStore(void);

#endif //!STORE_H