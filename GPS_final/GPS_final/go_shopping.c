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

void go_shopping_window(GtkWidget *p_window, shopping *myShop)
{
	init_map(p_window, myShop);

	merchant_optimise_shopping(myShop);
	merchant_connect_paths(myShop);
}