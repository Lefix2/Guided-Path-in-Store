#include <gtk/gtk.h>
#include <stdlib.h>

#include "callback.h"
#include "error.h"


int init_courses(){
	/*Widgets creation */
	GtkWidget *p_window = NULL;
	GtkWidget *p_grid[12];
	GtkWidget *p_table = NULL;
	GtkWidget *p_button[12];
	GtkWidget *p_label = NULL;
	GtkWidget *p_scrollbar = NULL;
	GtkWidget *p_shopping_list = NULL;
	GtkWidget *p_notebook = NULL;
	GtkWidget *p_onglet[12];

	char *categories[] = {"Fruits", "Numerique", "entretient", "boissons"};
	char *produits[] = { "pommes", "orange", "raisin", "poire" };

	
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);

	/*The window contain a grid that contains all of our widgets*/
	p_table = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p_window), p_table);

	p_notebook = gtk_notebook_new();
	gtk_grid_attach(GTK_GRID(p_table), p_notebook, 3, 1, 4, 4);

	p_scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_grid_attach(GTK_GRID(p_table), p_scrollbar, 0, 2, 2,3);

	/*We create now a grid contains the shopping list created by the user*/
	GtkWidget * label0 = NULL;
	GtkWidget * label1 = NULL;
	char text[20];
	p_shopping_list = gtk_grid_new();
	sprintf(text, "Product");
	label0 = gtk_label_new(text);
	sprintf(text, "Number");
	label1 = gtk_label_new(text);
	gtk_grid_attach(GTK_GRID(p_shopping_list), label0, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(p_shopping_list), label1, 1, 0, 1, 1);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p_scrollbar), p_shopping_list);


	

	p_button[0] = gtk_button_new_with_label("pates");
	g_signal_connect(G_OBJECT(p_button[0]), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
	p_button[1] = gtk_button_new_with_label("Fruit de la passion");
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
	

	/*Creation of every tab of the notebook*/
	//char text[20];

	sprintf(text, "Fruits");
	p_onglet[0] = gtk_label_new(text);
	p_grid[0] = gtk_grid_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook),p_grid[0], p_onglet[0]);
	gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[1], 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[9], 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[10], 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[11], 0, 3, 1, 1);

	sprintf(text, "Feculents");
	p_onglet[1] = gtk_label_new(text);
	p_grid[1] = gtk_grid_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[1], p_onglet[1]);
	gtk_grid_attach(GTK_GRID(p_grid[1]), p_button[0], 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[1]), p_button[7], 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[1]), p_button[8], 0, 2, 1, 1);

	sprintf(text, "Numerique");
	p_onglet[2] = gtk_label_new(text);
	p_grid[2] = gtk_grid_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[2], p_onglet[2]);

	sprintf(text, "Jardinage");
	p_onglet[3] = gtk_label_new(text);
	p_grid[3] = gtk_grid_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[3], p_onglet[3]);
	gtk_grid_attach(GTK_GRID(p_grid[3]), p_button[2], 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[3]), p_button[6], 0, 1, 1, 1);

	sprintf(text, "Entretien");
	p_onglet[4] = gtk_label_new(text);
	p_grid[4] = gtk_grid_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[4], p_onglet[4]);
	gtk_grid_attach(GTK_GRID(p_grid[4]), p_button[3], 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(p_grid[4]), p_button[5], 0, 1, 1, 1);
	
	sprintf(text, "Boisson");
	p_onglet[5] = gtk_label_new(text);
	p_grid[5] = gtk_grid_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[5], p_onglet[5]);
	gtk_grid_attach(GTK_GRID(p_grid[5]), p_button[4], 0, 0, 1, 1);

	

	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(p_notebook), GTK_POS_RIGHT);
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(p_notebook), FALSE);




	/*****Creation of the menu*/
	GtkWidget *p_menu_bar = NULL;
	p_menu_bar = gtk_menu_bar_new();

	GtkWidget *p_menu = NULL;
	p_menu = gtk_menu_new();

	/*Creation of the categories*/
	GtkWidget *p_menu_item[6];
	p_menu_item[0] = gtk_image_menu_item_new_with_label("Fruits");
	p_menu_item[1] = gtk_image_menu_item_new_with_label("Feculents");
	p_menu_item[2] = gtk_image_menu_item_new_with_label("Numerique");
	p_menu_item[3] = gtk_image_menu_item_new_with_label("Jardinage");
	p_menu_item[4] = gtk_image_menu_item_new_with_label("Entretien");
	p_menu_item[5] = gtk_image_menu_item_new_with_label("Boisson");
	//gtk_image_menu_item_set_image(p_menu_item, GTK_IMAGE_);
	int i = 0;
	for (i; i < 6; i++){
		g_signal_connect(G_OBJECT(p_menu_item[i]), "activate", G_CALLBACK(cb_open_tab), p_notebook);
	}
	/*Addition of these categories to the menu*/
	i = 0;
	for (i; i < 6; i++){
		gtk_menu_shell_append(GTK_MENU_SHELL(p_menu), p_menu_item[i]);
	}


	/*Creation of a box that will contain the menu, and go into the menubar*/
	GtkWidget *p_menu_link = NULL;
	p_menu_link = gtk_menu_item_new_with_label("Categories");

	/*Association with the menu*/
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(p_menu_link), p_menu);

	/*And finally add the linker to the menu_bar*/
	gtk_menu_shell_append(GTK_MENU_SHELL(p_menu_bar), p_menu_link);

	gtk_grid_attach(GTK_GRID(p_table), p_menu_bar, 6, 0, 1, 1);


	


	/*for (k; k < 3; k++){
		j = 0;
		for (j; j < 4; j++){
			gtk_grid_attach(GTK_GRID(p_table), p_button[(k*4) + j], j+4, k+1, 1, 1);

		}
	}*/
	

	GtkWidget *label2 = NULL, *label3 =NULL;
	char texte[20];
	sprintf(texte, "Your shopping list");
	label2 = gtk_label_new(texte);
	gtk_grid_attach(GTK_GRID(p_table), label2, 0, 0, 1, 1);
	sprintf(texte, "Select products");
	label3 = gtk_label_new(texte);
	gtk_grid_attach(GTK_GRID(p_table), label3, 4, 0, 1, 1);
	


	gtk_widget_show_all(p_window);
	gtk_grid_set_column_spacing(GTK_GRID(p_table), 10);
	gtk_grid_set_row_spacing(GTK_GRID(p_table), 2);
	gtk_grid_set_column_homogeneous(GTK_GRID(p_table), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(p_table), TRUE);
	gtk_window_set_title(GTK_WINDOW(p_window), "Guided Path in Store");
	return EXIT_SUCCESS;
}
