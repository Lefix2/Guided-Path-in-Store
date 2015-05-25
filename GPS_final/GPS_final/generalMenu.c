#include "Common.h"
#include "generalMenu.h"

shopping * my_shopping;

void call_main_menu()
{
	
	/* Window Creation */
	GtkWidget *p_window = NULL;
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), p_window);
	
	/*The window contain a grid that contains all of our widgets*/
	GtkWidget * p_table = NULL;
	p_table = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p_window), p_table);

	/*The first button is used to open the database to choose a store*/
	GtkWidget * p_label = NULL;
	GtkWidget * p_event_box = NULL;
	gchar *txtSchema;
	gchar utf8_chain[256];

	p_event_box = gtk_event_box_new();
	sprintf(utf8_chain, "<span face=\"Verdana\" foreground=\"#%02X%02X%02X\" size=\"xx-large\"><b>Choisissez \nvotre magasin</b></span>", rand() % (0xFF), rand() % (0xFF), rand() % (0xFF));
	txtSchema = g_locale_to_utf8(utf8_chain, -1, NULL, NULL, NULL);
	p_label = gtk_label_new(txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(p_label), TRUE);
	g_signal_connect(G_OBJECT(p_event_box),
		"button_press_event",
		G_CALLBACK(cb_store_selection),
		p_window);
	gtk_container_add(GTK_CONTAINER(p_event_box), p_label);
	gtk_grid_attach(GTK_GRID(p_table), p_event_box, 0, 0, 1, 1);

	/*We do the last settings to the window*/
	gtk_widget_show_all(p_window);
	gtk_window_set_title(GTK_WINDOW(p_window), "Guided Path in Store");

}

void cb_quit(GtkWidget *p_widget, gpointer user_data){
	gtk_main_quit();
}

void cb_store_selection(GtkWidget *p_widget, gpointer p_window){
	//store_selection_window();
	gtk_widget_destroy(GTK_WIDGET(p_window));
}