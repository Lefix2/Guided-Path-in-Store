/*!
* \file  generalMenu.h
* \brief Header of generalMenu.c
* \author GPS team
* \date 13/12/2014
*
* Contain prototype of itemList
*/
#ifndef GENERALMENU_H
#define GENERALMENU_H

#include "Common.h"

/**
* \struct generalmenu_struct
* \brief Structure for the menu
*/
typedef struct generalmenu_struct generalmenu_struct;
struct generalmenu_struct{

	shopping *myShop;			/*!< pointer to a shop */

	GtkWidget * main_window;	/*!< the window */
	GtkWidget * button_selec;	/*!< the selection button */
	GtkWidget * button_makel;	/*!< the making list button */
	GtkWidget * button_gosho;	/*!< the shopping button */
};

void call_main_menu(GtkApplication *app);
gboolean cb_quit(GtkWidget *p_widget, generalmenu_struct *main_menu);
gboolean cb_store_selection(GtkWidget *p_widget, generalmenu_struct *main_menu);
gboolean cb_make_list(GtkWidget *p_widget, generalmenu_struct *main_menu);
gboolean cb_go_shopping(GtkWidget *p_widget, gpointer *main_menu);

#endif // !GENERALMENU_H
