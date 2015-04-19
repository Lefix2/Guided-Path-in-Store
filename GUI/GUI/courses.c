#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "error.h"

int init_courses(){
	/*Widgets creation */
	GtkWidget *p_window = NULL;
	GtkWidget *p_table = NULL;
	GtkWidget *p_button[12] =NULL;
	GtkWidget *p_label = NULL;

	
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);

	p_table = Gtk_table_new(5, 4, TRUE);
	int i = 0;
	int j, k = 1;
	for (i; i < 11; i++){
		p_button[i] = gtk_button_new_from_stock(GTK_STOCK_DIRECTORY);
	}
	for (i; i < 3; i++){
		for (j; j < 4; j++){
			gtk_table_attach(GTK_TABLE(p_table), p_button[k + 4 * j], k, k, j, j, GTK_EXPAND, GTK_EXPAND, 0, 0);
		}
	}

	//txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Petite superette</b></span>", -1, NULL, NULL, NULL);
	//label = gtk_label_new(txtSchema);


	gtk_widget_show_all(p_window);
	g_window_set_title(GTK_WINDOW(p_window), "Liste de courses");
	return EXIT_SUCCESS;
}
