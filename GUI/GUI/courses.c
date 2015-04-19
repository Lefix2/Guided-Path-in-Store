#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"
#include "error.h"

int init_courses(){
	/*Widgets creation */
	GtkWidget *p_window = NULL;
	GtkWidget *p_table = NULL;
	GtkWidget *p_button[12];
	GtkWidget *p_label = NULL;
	GtkWidget *p_scrollbar = NULL;
	GtkWidget *p_shopping_list = NULL;

	
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);

	p_table = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p_window), p_table);

	p_scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_grid_attach(GTK_GRID(p_table), p_scrollbar, 1, 1, 2, 3);

	p_shopping_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p_scrollbar), p_shopping_list);




	p_button[0] = gtk_button_new_with_label("poireaux");
	g_signal_connect(G_OBJECT(p_button[0]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[1] = gtk_button_new_with_label("lait");
	g_signal_connect(G_OBJECT(p_button[1]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[2] = gtk_button_new_with_label("alcool");
	g_signal_connect(G_OBJECT(p_button[2]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[3] = gtk_button_new_with_label("jus de fruit");
	g_signal_connect(G_OBJECT(p_button[3]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[4] = gtk_button_new_with_label("gateaux aperitifs");
	g_signal_connect(G_OBJECT(p_button[4]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[5] = gtk_button_new_with_label("cookies");
	g_signal_connect(G_OBJECT(p_button[5]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[6] = gtk_button_new_with_label("pates");
	g_signal_connect(G_OBJECT(p_button[6]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[7] = gtk_button_new_with_label("riz");
	g_signal_connect(G_OBJECT(p_button[7]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[8] = gtk_button_new_with_label("puree");
	g_signal_connect(G_OBJECT(p_button[8]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[9] = gtk_button_new_with_label("pomme");
	g_signal_connect(G_OBJECT(p_button[9]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[10] = gtk_button_new_with_label("banane");
	g_signal_connect(G_OBJECT(p_button[10]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[11] = gtk_button_new_with_label("kiwi");
	g_signal_connect(G_OBJECT(p_button[11]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	
	
	int j = 0, k = 0, r = 0, c = 0;
	for (r; r < 4; r++){
		gtk_grid_insert_row(GTK_GRID(p_table), 0);
	}
	for (c; c < 8; c++){
		gtk_grid_insert_column(GTK_GRID(p_table), 0);
	}
	for (k; k < 3; k++){
		j = 0;
		for (j; j < 4; j++){
			gtk_grid_attach(GTK_GRID(p_table), p_button[(k*4) + j], j+4, k+1, 1, 1);

		}
	}


	GtkWidget *label1 = NULL, *label2 =NULL;
	char texte[20];
	sprintf(texte, "Your shopping list");
	label1 = gtk_label_new(texte);
	gtk_grid_attach(GTK_GRID(p_table), label1, 1, 0, 1, 1);
	sprintf(texte, "Select products");
	label2 = gtk_label_new(texte);
	gtk_grid_attach(GTK_GRID(p_table), label2, 4, 0, 1, 1);
	


	gtk_widget_show_all(p_window);
	gtk_grid_set_column_spacing(GTK_GRID(p_table), 10);
	gtk_grid_set_row_spacing(GTK_GRID(p_table), 2);
	gtk_grid_set_column_homogeneous(GTK_GRID(p_table), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(p_table), TRUE);
	gtk_window_set_title(GTK_WINDOW(p_window), "Liste de courses");
	return EXIT_SUCCESS;
}
