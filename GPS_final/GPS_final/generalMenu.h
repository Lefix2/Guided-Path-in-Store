#ifndef GENERALMENU_H
#define GENERALMENU_H

#include "Common.h"

typedef struct generalmenu_struct generalmenu_struct;
struct generalmenu_struct{

	shopping *myShop;

	GtkWidget * main_window;
	GtkWidget * button_selec;
	GtkWidget * button_makel;
	GtkWidget * button_gosho;
};

void call_main_menu(GtkApplication *app);
gboolean cb_quit(GtkWidget *p_widget, generalmenu_struct *main_menu);
gboolean cb_store_selection(GtkWidget *p_widget, generalmenu_struct *main_menu);
gboolean cb_make_list(GtkWidget *p_widget, generalmenu_struct *main_menu);
gboolean cb_go_shopping(GtkWidget *p_widget, gpointer *main_menu);

#endif // !GENERALMENU_H
