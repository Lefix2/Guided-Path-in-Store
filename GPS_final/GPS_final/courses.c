#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "Store.h"
#include "ItemList.h"
#include "Item.h"
#include "courses.h"
#include "common.h"
#include "Shopping.h"

GtkWidget *window;
generalmenu_struct *parent_menu;


int init_courses(generalmenu_struct *parent, shopping *myshop){
	parent_menu = parent;
	/*Widgets creation */
	GtkWidget *main_grid = NULL;
	GtkWidget *p_scrollbar = NULL;
	GtkWidget *p_shopping_list = NULL;

	shop_struct * p_shop_struct = (shop_struct*)malloc(sizeof(shop_struct));
	p_shop_struct->shopping = myshop;

	//creating a temporary list to make shopping
	p_shop_struct->tmp_list = itemPointerList_new();

	itemPointerList_set_on_first(myshop->List);
	while (!itemPointerList_is_out_of(myshop->List))
	{
		itemPointerList_insert_last(p_shop_struct->tmp_list, itemPointerList_get_current(myshop->List));
		itemPointerList_next(myshop->List);
	}
	
	/*Creation of the window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Guided Path in Store");

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(cb_course_quit), p_shop_struct);

	/*The window contain a grid that contains all of our widgets*/
	main_grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), main_grid);
	gtk_grid_set_column_spacing(GTK_GRID(main_grid), 0);
	gtk_grid_set_row_spacing(GTK_GRID(main_grid), 2);
	gtk_grid_set_column_homogeneous(GTK_GRID(main_grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(main_grid), FALSE);

	/*We create now a grid that contains the shopping list created by the user*/
	p_scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_grid_attach(GTK_GRID(main_grid), p_scrollbar, 0, 1, 1,4);

	p_shop_struct->list_grid = gtk_grid_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p_scrollbar), p_shop_struct->list_grid);
	
	/*We create now a notebook */
	p_shop_struct->notebook = notebook_new_from_shopping(p_shop_struct);

	gtk_grid_attach(GTK_GRID(main_grid), p_shop_struct->notebook, 1, 1, 4, 4);

	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(p_shop_struct->notebook), GTK_POS_LEFT);
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(p_shop_struct->notebook), TRUE);
	

	/*We create now the entry for the product research*/
	p_shop_struct->entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(main_grid), p_shop_struct->entry, 2, 0, 1, 1);
	gtk_entry_set_placeholder_text(GTK_ENTRY(p_shop_struct->entry), "Product name");
	gtk_entry_set_icon_from_stock(GTK_ENTRY(p_shop_struct->entry), GTK_ENTRY_ICON_PRIMARY, GTK_STOCK_FIND);

	g_signal_connect(G_OBJECT(p_shop_struct->entry), "activate", G_CALLBACK(cb_activate_search_bar), p_shop_struct);

	/*We create next to it a button to clear the search*/
	GtkWidget *p_search_clear_button;
	p_search_clear_button = gtk_button_new_from_stock(GTK_STOCK_STOP);
	gtk_grid_attach(GTK_GRID(main_grid), p_search_clear_button, 3, 0, 1, 1);
	g_signal_connect(G_OBJECT(p_search_clear_button), "clicked", G_CALLBACK(cb_search_clear_button), p_shop_struct);

	/* Creation of the ending button*/
	GtkWidget * ending_button = NULL;
	ending_button = gtk_button_new_with_label("Click here to end your list");
	gtk_grid_attach(GTK_GRID(main_grid), ending_button, 1, 5, 4, 1);
	g_signal_connect(G_OBJECT(ending_button), "clicked", G_CALLBACK(cb_end_list), p_shop_struct);
	

	GtkWidget *label2 = NULL, *label3 =NULL;
	char texte[20];
	sprintf(texte, "Your shopping list");
	label2 = gtk_label_new(texte);
	gtk_grid_attach(GTK_GRID(main_grid), label2, 0, 0, 1, 1);
	sprintf(texte, "Select products");
	label3 = gtk_label_new(texte);
	gtk_grid_attach(GTK_GRID(main_grid), label3, 1, 0, 1, 1);
	
	display_list(p_shop_struct);
	gtk_widget_show_all(window);

	return EXIT_SUCCESS;
}

/**
*\brief that function returns a notebook created from a store in parameters
*\param[in] a store
*\param[out] a notebook (GtkWidget)
*/
GtkWidget * notebook_new_from_shopping(shop_struct * p_shop_struct){

	char text[MAX_ARRAY_OF_CHAR];
	char *category_string = NULL;
	GtkWidget *p_notebook = gtk_notebook_new();
	GtkWidget *tab_label;
	GtkWidget *p_grid;
	GtkWidget *p_button;
	store * store = p_shop_struct->shopping->Store;

	itemPointerList_set_on_first(store_get_allocatedStock(store));

	while (!itemPointerList_is_out_of(store_get_allocatedStock(store))){
		category_string = store->category[item_get_category(store_get_allocatedStock(store)->current->i)];
		GtkWidget * found_child = grid_find_category(category_string, p_notebook);

		p_button = gtk_button_new_with_label(store_get_allocatedStock(store)->current->i->name);
		g_signal_connect(G_OBJECT(p_button), "clicked", G_CALLBACK(cb_shopping_list), p_shop_struct);

		if (found_child == NULL)
		{// if there is no notebook tab with the item label
			sprintf(text, category_string);
			tab_label = gtk_label_new(text);
			p_grid = gtk_grid_new();
			gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid, tab_label);
			gtk_grid_attach(GTK_GRID(p_grid), p_button, 0, 0, 1, 1);
		}
		else
		{
			gtk_grid_attach_next_to(GTK_GRID(found_child), p_button, NULL, GTK_POS_RIGHT, 1, 1);
		}
		itemPointerList_next(store_get_allocatedStock(store));
	}
	return p_notebook;
}
/**
*\brief Function that returns the number of the tab with the same name as category_name
*\param[out] returns -1 if there is no tab with the same name as category_name, the number of pages otherwise
*/ 
GtkWidget * grid_find_category(char * category_name, GtkWidget * p_notebook){
	GtkWidget * currentNotebookTab;
	GtkWidget * ret = NULL;
	int j=0;
	for (j; j < gtk_notebook_get_n_pages(GTK_NOTEBOOK(p_notebook)); j++){
		currentNotebookTab = gtk_notebook_get_nth_page(GTK_NOTEBOOK(p_notebook), j);
		if (g_strcmp0(gtk_label_get_label(GTK_LABEL(gtk_notebook_get_tab_label(GTK_NOTEBOOK(p_notebook), currentNotebookTab))), category_name) == 0){
			ret = currentNotebookTab;
		}
	}
	return ret;
}

/*callbacks*/


void cb_shopping_list(GtkWidget *p_widget, shop_struct *p_shop_struct){

	itemList * list = store_get_allocatedStock(shopping_get_store(p_shop_struct->shopping));
	itemList * tmp_list = p_shop_struct->tmp_list;
	item * found_item;
	gchar *b_label, *i_name;

	b_label = gtk_button_get_label(GTK_BUTTON(p_widget));

	itemPointerList_set_on_first(list);
	while (!itemPointerList_is_out_of(list))
	{
		i_name = item_get_name(itemPointerList_get_current(list));
		if (g_strcmp0(b_label, i_name) == 0)
		{
			found_item = itemPointerList_find(tmp_list, itemPointerList_get_current(list));
			if (found_item == NULL)
				itemPointerList_insert_last(tmp_list, itemPointerList_get_current(list));
			itemPointerList_get_current(list)->stock++;
		}
		itemPointerList_next(list);
	}
	display_list(p_shop_struct);
}

void display_list(shop_struct *p_shop_struct)
{
	itemList *tmp_list = p_shop_struct->tmp_list;
	gchar * i_name;
	item * current;
	int currentstock;
	GtkWidget * s_label, *p_label, *n_label;
	GtkWidget * spin_button;
	GtkWidget * list_grid = p_shop_struct->list_grid;
	int lines = 0;
	int i = 0;

	while (gtk_grid_get_child_at(list_grid, 0, lines) != NULL)
	{
		lines++;
	}

	for (i = 0; i < lines; i++)
	{
		gtk_widget_destroy(gtk_grid_get_child_at(list_grid, 0, i));
		gtk_widget_destroy(gtk_grid_get_child_at(list_grid, 1, i));
	}

	p_label = gtk_label_new("Produit");
	n_label = gtk_label_new("Quantite");
	gtk_grid_attach(GTK_GRID(list_grid), p_label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(list_grid), n_label, 1, 0, 1, 1);

	i = 1;
	itemPointerList_set_on_first(tmp_list);
	while (!itemPointerList_is_out_of(tmp_list))
	{
		current = itemPointerList_get_current(tmp_list);
		currentstock = item_get_stock(current);

		if (currentstock <= 0)
		{
			itemPointerList_delete_current(tmp_list);
		}
		else
		{
			i_name = item_get_name(current);
			s_label = gtk_label_new(i_name);

			spin_button = gtk_spin_button_new_with_range(0, 1000, 1);
			gtk_spin_button_set_value(spin_button, currentstock);
			g_signal_connect(GTK_SPIN_BUTTON(spin_button), "value-changed", cb_update_spin_button, current);

			gtk_grid_attach(GTK_GRID(list_grid), s_label, 0, i, 1, 1);
			gtk_grid_attach(GTK_GRID(list_grid), spin_button, 1, i, 1, 1);

			i++;
		}
		itemPointerList_next(tmp_list);
	}
	gtk_widget_show_all(list_grid);
}

gboolean cb_update_spin_button(GtkWidget *p_widget, gpointer *associated_item)
{
	item_set_stock((item*)associated_item, (int)gtk_spin_button_get_value(p_widget));
	return FALSE;
}

void cb_activate_search_bar(GtkWidget *p_entry, shop_struct *p_shop_struct)
{
	GtkWidget * p_button = NULL;
	GtkWidget * new_grid = NULL;
	GtkWidget * p_onglet = NULL;
	GtkWidget * p_grid = NULL;
	GtkWidget * notebook = p_shop_struct->notebook;

	gboolean searching_tab_exists = FALSE;
	gint i = 0;
	gint nbpages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook));
	gchar *sText;
	gchar * item_name;
	gchar text[MAX_ARRAY_OF_CHAR];

	itemList * a_stock = store_get_allocatedStock(shopping_get_store(p_shop_struct->shopping));


	/**Pour commencer, on teste si l'onglet de recherche a deja ete cree
	*/
	sprintf(text, "recherche");
	sText = gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), nbpages - 1));
	if (g_strcmp0(text, sText) == 0)
	{
		searching_tab_exists = TRUE;
	}

	/**
	*On teste maintenant si l'utilisateur n'a pas clear sa recherche :
	*Si c'est le cas, on détruit la dernière page du notebook
	*/
	sText = gtk_entry_get_text(GTK_ENTRY(p_entry));

	if (g_strcmp0(sText, "") == 0)
	{
		if (searching_tab_exists)
		{
			gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), nbpages - 1);
			nbpages--;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
	}
	else
	{
		if (searching_tab_exists)
			/*We destroy the existing tab*/
		{
			gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), nbpages - 1);
			nbpages--;
		}
		/*We create the last tab only activated when the user is searching*/
		printf("We create the last tab only activated when the user is searching\n");
		p_onglet = gtk_label_new(text);
		p_grid = gtk_grid_new();
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), p_grid, p_onglet);
		gtk_widget_show_all(notebook);
		nbpages++;


		/*On parcours la liste des items et on crée un button pour chacun de ceux qui correspondent*/
		itemPointerList_set_on_first(a_stock);
		while (!itemPointerList_is_out_of(a_stock))
		{
			item_name = (const gchar *)item_get_name(itemPointerList_get_current(a_stock));

			if (g_str_has_prefix(item_name, sText) != 0)
			{//The item matched with the research, we create a new button
				p_button = gtk_button_new_with_label(item_name);
				gtk_grid_attach(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), nbpages - 1)), p_button, 0, 0, 1, 1);
				g_signal_connect(G_OBJECT(p_button), "clicked", G_CALLBACK(cb_shopping_list), p_shop_struct);
			}
			itemPointerList_next(a_stock);
		}

		gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), nbpages - 1);
		gtk_widget_show_all(notebook);
	}
}

void cb_search_clear_button(GtkWidget *p_button, shop_struct *p_shop_struct){
	
	gint nbpages;
	gboolean searching_tab_exists = FALSE;
	char text[MAX_ARRAY_OF_CHAR];
	sprintf(text, "recherche");

	GtkWidget *notebook = p_shop_struct->notebook;

	nbpages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(notebook));

	if (g_strcmp0(text, gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), nbpages - 1))) == 0)
	{
		searching_tab_exists = TRUE;
	}

	if (searching_tab_exists)
		/*We destroy the existing tab*/
	{
		gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), nbpages - 1);
	}
	gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 0);
	gtk_entry_set_text(p_shop_struct->entry, "");
}

gboolean cb_course_quit(GtkWidget *p_button, shop_struct * p_shop_struct){


	gtk_widget_set_sensitive(parent_menu->main_window, TRUE);

	if (p_shop_struct->shopping->List->first != NULL)
		gtk_widget_set_sensitive(parent_menu->button_gosho, TRUE);
	else
		gtk_widget_set_sensitive(parent_menu->button_gosho, FALSE);

	gtk_widget_show_all(parent_menu->main_window);

	itemPointerList_delete(p_shop_struct->tmp_list);
	free(p_shop_struct);

	return FALSE;
}

gboolean cb_end_list(GtkWidget *p_button, shop_struct * p_shop_struct){

	display_list(p_shop_struct);

	itemList *tmp_list = p_shop_struct->tmp_list;
	itemList *list = shopping_get_list(p_shop_struct->shopping);

	itemPointerList_set_on_first(list);
	while (!itemPointerList_is_empty(list))
	{
		itemPointerList_delete_first(list);
	}

	itemPointerList_set_on_first(tmp_list);
	while (!itemPointerList_is_out_of(tmp_list))
	{
		itemPointerList_insert_last(list, itemPointerList_get_current(tmp_list));
		itemPointerList_next(tmp_list);
	}

	gtk_widget_destroy(window);
	return FALSE;
}