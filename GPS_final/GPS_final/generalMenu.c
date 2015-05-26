#include "Common.h"
#include "Shopping.h"
#include "courses.h"
#include "generalMenu.h"
#include "go_shopping.h"
#include "tests.h"
#include "Store_IO_functions.h"

shopping * myShop;

void call_main_menu()
{
	gchar utf8_chain[MAX_ARRAY_OF_CHAR];
	GtkImage *WelcomeImg = gtk_image_new_from_file(".\\ressources\\Images\\mainMenu.png");

	/* Window Creation */
	GtkWidget *p_window = NULL;
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), p_window);
	
	/*The window contain a grid that contains all of our widgets*/
	GtkWidget * v_box = NULL;
	v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	gtk_container_add(GTK_CONTAINER(p_window), v_box);

	/*add a title*/
	GtkWidget *title;
	sprintf(utf8_chain, "<span face = \"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Guided Path in Store</b></span>");
	title = gtk_label_new(g_locale_from_utf8(utf8_chain,-1,NULL,NULL,NULL));
	gtk_label_set_use_markup(GTK_LABEL(title), TRUE);
	gtk_box_pack_start(GTK_BOX(v_box), WelcomeImg, TRUE, TRUE, 0);

	/*The first button is used to open the database to choose a store*/
	GtkWidget * p_button1 = NULL;

	p_button1 = gtk_button_new_with_label("Ouvrir un magasin");
	g_signal_connect(GTK_BUTTON(p_button1),	"button_press_event", G_CALLBACK(cb_store_selection), p_window);
	gtk_box_pack_start(GTK_BOX(v_box), p_button1, FALSE, FALSE, 0);

	/*The second button is used to create his list*/
	GtkWidget * p_button2 = NULL;

	p_button2 = gtk_button_new_with_label("Faire sa liste de course");
	g_signal_connect(GTK_BUTTON(p_button2), "button_press_event", G_CALLBACK(cb_make_list), p_window);
	gtk_box_pack_start(GTK_BOX(v_box), p_button2, FALSE, FALSE, 0);

	/*The third is to start the shopping*/
	GtkWidget * p_button3 = NULL;

	p_button3 = gtk_button_new_with_label("Demarrer ses courses");
	g_signal_connect(GTK_BUTTON(p_button3), "button_press_event", G_CALLBACK(cb_go_shopping), p_window);
	gtk_box_pack_start(GTK_BOX(v_box), p_button3, FALSE, FALSE, 0);

	/*We do the last settings to the window*/
	gtk_widget_show_all(p_window);
	gtk_window_set_title(GTK_WINDOW(p_window), "Guided Path in Store");

}

gboolean cb_quit(GtkWidget *p_widget, gpointer user_data){
	gtk_main_quit();
	return FALSE;
}

gboolean cb_store_selection(GtkWidget *p_widget, gpointer p_window){
	//store_selection_window();
	myShop = shopping_new(sqlite_new_store_from_database(".\\ressources\\projet.db"));//shopping_new(my_test_store_new());
	//gtk_widget_hide(p_window);
	return FALSE;
}

gboolean cb_make_list(GtkWidget *p_widget, gpointer p_window){
	//make_list();
	
	/*code test*/
	myShop->List = itemPointerList_new();

	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 0));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 1));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 2));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 3));
	itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 4));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 5));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 6));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 7));
	//itemPointerList_insert_sort(myShop->List, store_find_item_id(myShop->Store, 8));
	
	//gtk_widget_hide(GTK_WIDGET(p_window));
	return FALSE;
}

gboolean cb_go_shopping(GtkWidget *p_widget, gpointer p_window){
	go_shopping_window(myShop);
	//gtk_widget_destroy(GTK_WIDGET(p_window));
	return FALSE;
}