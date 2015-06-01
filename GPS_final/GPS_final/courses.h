#ifndef COURSES_H
#define COURSES_H

#include <gtk/gtk.h>
#include "common.h"
#include "generalMenu.h"


/*
*\struct shop_struct
*\brief structure containing makelist content
*/

typedef struct shop_struct shop_struct;
struct shop_struct{

	itemList *tmp_list;
	shopping *shopping;

	GtkWidget *list_grid;
	GtkWidget *notebook;
	GtkWidget *entry;
};

int init_courses(generalmenu_struct *parent, shopping *myshop);
GtkWidget * notebook_new_from_shopping(shop_struct * p_shop_struct);
GtkWidget * grid_find_category(char * category_name, GtkWidget * p_notebook);
void cb_shopping_list(GtkWidget *p_widget, shop_struct *p_shop_struct);
void display_list(shop_struct *p_shop_struct);
gboolean cb_update_spin_button(GtkWidget *p_widget, gpointer *associated_item);
void cb_activate_search_bar(GtkWidget *p_entry, shop_struct *p_shop_struct);
void cb_search_clear_button(GtkWidget *p_button, shop_struct *p_shop_struct);
gboolean cb_course_quit(GtkWidget *p_button, shop_struct * p_shop_struct);
gboolean cb_end_list(GtkWidget *p_button, shop_struct * p_shop_struct);

#endif //!COURSES_H