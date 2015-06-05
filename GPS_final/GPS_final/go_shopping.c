/*!
* \file  go_shopping.c
* \brief Call properly an window shopping
* \author GPS team
* \date 13/12/2014
*
* Contain prototype of itemList
*/
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
	merchant_optimise_shopping(myShop);
	merchant_connect_paths(myShop);

	init_map(p_window, myShop);
}