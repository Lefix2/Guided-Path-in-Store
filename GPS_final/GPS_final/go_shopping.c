#include "Common.h"

#include "go_shopping.h"

#include "Item.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"
#include "Shopping.h"
#include "merchant.h"
#include "StoreImage.h"
#include "map.h"

void go_shopping_window(shopping *myShop)
{
	init_map(myShop);

	merchant_optimise_shopping(myShop);
}