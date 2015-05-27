#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#include "Store.h"
#include "ItemList.h"
#include "Item.h"
#include "courses.h"
#include "common.h"
#include "Shopping.h"


shopping_list * shopping_list_new()
{
	shopping_list * new_shopping_list;
	new_shopping_list = (shopping_list *)malloc(sizeof(shopping_list));

	new_shopping_list->shopping_itemlist = NULL;
	new_shopping_list->shopping_list_grid = NULL;

	return new_shopping_list;
}

store_notebook * store_notebook_new()
{
	store_notebook * new_sn;
	new_sn = (store_notebook *)malloc(sizeof(store_notebook));

	new_sn->notebook = NULL;
	new_sn->store = NULL;

	return new_sn;
}

grid_store_notebook * grid_store_notebook_new(){
	grid_store_notebook * new_gn;
	new_gn = (grid_store_notebook *)malloc(sizeof(grid_store_notebook));

	new_gn->notebook = NULL;
	new_gn->grid = NULL;
	new_gn->store = NULL;
	new_gn->user_list = NULL;

	return new_gn;
}

int init_courses(store * store_test, itemList * user_list){
	/*Widgets creation */
	GtkWidget *p_window = NULL;
	GtkWidget *p_table = NULL;
	GtkWidget *p_label = NULL;
	GtkWidget *p_scrollbar = NULL;
	GtkWidget *p_shopping_list = NULL;
	GtkWidget *p_notebook = NULL;

	shopping_list * s_list = NULL;
	s_list = shopping_list_new();
	s_list->shopping_itemlist = user_list;
	s_list->shopping_list_grid = p_shopping_list;

	char *categories[] = {"Fruits", "Numerique", "entretien", "boissons"};
	char *produits[] = { "pommes", "orange", "raisin", "poire" };

	
	
	/*Creation of the window*/
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	shopping * p_shopping = NULL;
	p_shopping = shopping_new(store_test);
	p_shopping->List = s_list->shopping_itemlist;
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_list_quit), p_shopping);

	/*The window contain a grid that contains all of our widgets*/
	p_table = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(p_window), p_table);

	p_scrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_grid_attach(GTK_GRID(p_table), p_scrollbar, 0, 2, 1,3);

	/*We create now a grid that contains the shopping list created by the user*/
	GtkWidget * label0 = NULL;
	GtkWidget * label1 = NULL;
	char text[20];
	p_shopping_list = gtk_grid_new();

	sprintf(text, "Product   ");//first title
	label0 = gtk_label_new(text);
	gtk_grid_attach(GTK_GRID(p_shopping_list), label0, 0, 0, 1, 1);

	sprintf(text, "Number");//second title
	label1 = gtk_label_new(text);
	gtk_grid_attach(GTK_GRID(p_shopping_list), label1, 1, 0, 1, 1);

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p_scrollbar), p_shopping_list);
	
	/*We create now a notebook */
	/*shopping_list * s_list = NULL;
	s_list = shopping_list_new();*/

	p_notebook = notebook_new_from_store(store_test);
	gtk_grid_attach(GTK_GRID(p_table), p_notebook, 1, 1, 4, 4);
	notebook_connect_button(p_notebook, s_list);

	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(p_notebook), GTK_POS_LEFT);
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(p_notebook), TRUE);
	

	/*We create now the entry for the product research*/
	GtkWidget *p_search_bar;
	p_search_bar = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(p_table), p_search_bar, 2, 0, 1, 1);
	gtk_entry_set_placeholder_text(GTK_ENTRY(p_search_bar), "Product name");
	gtk_entry_set_icon_from_stock(GTK_ENTRY(p_search_bar),GTK_ENTRY_ICON_PRIMARY,GTK_STOCK_FIND);
	
	grid_store_notebook *p_gsn = NULL;
	p_gsn = grid_store_notebook_new();
	p_gsn->notebook = p_notebook;
	p_gsn->store = store_test;
	p_gsn->grid = p_shopping_list;
	p_gsn->user_list = user_list;

	g_signal_connect(G_OBJECT(p_search_bar), "activate", G_CALLBACK(cb_activate_search_bar), p_gsn);

	/*We create next to it a button to clear the search*/
	GtkWidget *p_search_clear_button;
	p_search_clear_button = gtk_button_new_from_stock(GTK_STOCK_STOP);
	gtk_grid_attach(GTK_GRID(p_table), p_search_clear_button, 3, 0, 1, 1);
	g_signal_connect(G_OBJECT(p_search_clear_button), "clicked", G_CALLBACK(cb_search_clear_button), p_gsn);


	/*p_button[0] = gtk_button_new_with_label("pates");
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
	
	
	/*
	* Creation of every tab of the notebook
	*
	*/
	//char text[20];
	


	/*sprintf(text, "Fruits");
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
	*/
	

	




	


	/*
	*
	*
	*  Creation of the ending button*/
	GtkWidget * ending_button = NULL;
	ending_button = gtk_button_new_with_label("Click here to end your list");
	gtk_grid_attach(GTK_GRID(p_table), ending_button, 1, 5, 4, 1);
	g_signal_connect(G_OBJECT(ending_button), "clicked", G_CALLBACK(cb_end_list), p_window);




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
	gtk_grid_attach(GTK_GRID(p_table), label3, 1, 0, 1, 1);
	


	gtk_widget_show_all(p_window);
	gtk_grid_set_column_spacing(GTK_GRID(p_table), 10);
	gtk_grid_set_row_spacing(GTK_GRID(p_table), 2);
	gtk_grid_set_column_homogeneous(GTK_GRID(p_table), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(p_table), TRUE);
	gtk_window_set_title(GTK_WINDOW(p_window), "Guided Path in Store");


	return EXIT_SUCCESS;
}

/**
*\brief that function returns a notebook created from a store in parameters
*\param[in] a store
*\param[out] a notebook (GtkWidget)
*/
GtkWidget * notebook_new_from_store(store * store_test){
	GtkWidget *p_notebook = NULL;
	p_notebook = gtk_notebook_new();
	char text[20];
	char *category_string = NULL;
	GtkWidget *p_onglet[42];
	GtkWidget *p_grid[42];
	GtkWidget *p_button[256];
	int i = 0, j=0;

	itemPointerList_set_on_first(store_test->allocatedStock);
	while (!itemPointerList_is_out_of(store_test->allocatedStock)){
		category_string = store_test->category[item_get_category(store_test->allocatedStock->current->i)];
		int grid_category_number = grid_find_category(category_string, p_notebook);

		p_button[j] = gtk_button_new_with_label(store_test->allocatedStock->current->i->name);
		if (grid_category_number == -1)
		{// if there is no notebook tab with the item label
			sprintf(text, category_string);
			p_onglet[i] = gtk_label_new(text);
			p_grid[i] = gtk_grid_new();
			gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[i], p_onglet[i]);
			gtk_grid_attach(GTK_GRID(p_grid[i]), p_button[j], 0, 0, 1, 1);
			i++; // i is the tab max number
		}
		else
		{
			gtk_grid_attach_next_to(GTK_GRID(p_grid[grid_category_number]), p_button[j], NULL,GTK_POS_RIGHT, 1, 1);
		}
		j++; // j is the item number (in the itemList)
		itemPointerList_next(store_test->allocatedStock);
	}
	

	return p_notebook;
}
/**
*\brief Function that returns the number of the tab with the same name as category_name
*\param[out] returns -1 if there is no tab with the same name as category_name, the number of pages otherwise
*/ 
int grid_find_category(char * category_name, GtkWidget * p_notebook){
	int i = -1,j=0;
	for (j; j < gtk_notebook_get_n_pages(GTK_NOTEBOOK(p_notebook)); j++){
		if (g_strcmp0(gtk_label_get_label(GTK_LABEL(gtk_notebook_get_tab_label(GTK_NOTEBOOK(p_notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(p_notebook), j)))), category_name) == 0){
			i = j;
		}
	}
	return i;
}

/**
*
*
*\brief Connecte tous les boutons du notebook au callback cb_shopping_list
*/
void notebook_connect_button(GtkWidget * p_notebook, shopping_list * s_list){
	int i = 0,j;
	GtkWidget * p_button = NULL;
	for (i; i < gtk_notebook_get_n_pages(GTK_NOTEBOOK(p_notebook)); i++){ // i numéro de la page du notebook
		j = 0;
		p_button = gtk_grid_get_child_at(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(p_notebook), i)), j, 0);
		while (p_button != NULL){
			g_signal_connect(G_OBJECT(p_button), "clicked", G_CALLBACK(cb_shopping_list), s_list);
			printf("Selection du bouton avec le label : %s\nPage :%d\nNumero=%d\n", gtk_button_get_label(GTK_BUTTON(p_button)),i,j);
			j++;
			p_button = gtk_grid_get_child_at(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(p_notebook), i)), j, 0);
		}
	}
}

GtkWidget * new_menu(GtkWidget * p_table, GtkWidget * p_notebook){
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

}


/*callbacks*/


void cb_shopping_list(GtkWidget *p_widget, shopping_list * s_list){
	const gchar * text;
	text = gtk_button_get_label(GTK_BUTTON(p_widget));

	/*Test de la présence dans la liste*/
	int i = 0;
	while (gtk_grid_get_child_at(GTK_GRID(s_list->shopping_list_grid), 0, i + 1) != NULL){
		if (g_strcmp0(gtk_label_get_label(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(s_list->shopping_list_grid), 0, i + 1))), text) == 0)
		{
			int j;
			GtkWidget *spin_button = NULL;
			spin_button = gtk_grid_get_child_at(GTK_GRID(s_list->shopping_list_grid), 1, i + 1);
			j = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button));
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button), j + 1);
			printf("Increment du nombre de %s dans la liste (cb_shopping_list)\n", text);
			return;
		}
		i++;
	}
	printf("cb_shopping_list appelle cb_add_item\n");
	cb_add_item(p_widget, s_list);
}


void cb_activate_search_bar(GtkWidget *p_entry, grid_store_notebook *g_notebook)
{
	const gchar *sText;
	const gchar * item_name;
	char text[20];
	sprintf(text, "recherche");
	sText = gtk_entry_get_text(GTK_ENTRY(p_entry));

	GtkWidget * p_button = NULL;
	GtkWidget * new_grid = NULL;
	GtkWidget * p_onglet = NULL;
	GtkWidget * p_grid = NULL;
	shopping_list * p_shopping_list = NULL;
	p_shopping_list = shopping_list_new();
	p_shopping_list->shopping_itemlist = g_notebook->user_list;
	p_shopping_list->shopping_list_grid = g_notebook->grid;

	gboolean searching_tab_exists = FALSE;
	gboolean search_success = FALSE;
	int i = 0;
	gint nbpages;
	nbpages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(g_notebook->notebook));


	/**Pour commencer, on teste si l'onglet de recherche a deja ete cree
	*/
	printf("last tab label :\n");
	printf(gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(g_notebook->notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1)));
	printf("\n");
	if (g_strcmp0(text, gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(g_notebook->notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1))) == 0)
	{
		searching_tab_exists = TRUE;
	}


	/**
	*On teste maintenant si l'utilisateur n'a pas clear sa recherche :
	*Si c'est le cas, on détruit la dernière page du notebook
	*/
	if (g_strcmp0(sText, "") == 0)
	{
		printf("the user cleared his research\n");
		if (searching_tab_exists)
		{
			printf("trying to remove last page");
			gtk_notebook_remove_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1);
			nbpages--;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(g_notebook->notebook), 0);
	}
	else
	{
		if (searching_tab_exists)
			/*We destroy the existing tab*/
		{
			gtk_notebook_remove_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1);
			nbpages--;
		}
		/*We create the last tab only activated when the user is searching*/
		printf("We create the last tab only activated when the user is searching\n");
		p_onglet = gtk_label_new(text);
		p_grid = gtk_grid_new();
		gtk_notebook_append_page(GTK_NOTEBOOK(g_notebook->notebook), p_grid, p_onglet);
		gtk_widget_show_all(g_notebook->notebook);
		nbpages++;


		/*On parcours la liste des items et on crée un button pour chacun de ceux qui correspondent*/
		itemPointerList_set_on_first(g_notebook->store->allocatedStock);
		while (!itemPointerList_is_out_of(g_notebook->store->allocatedStock))
		{
			item_name = (const gchar *)item_get_name(g_notebook->store->allocatedStock->current->i);

			if (g_str_has_prefix(item_name, sText) != 0)
			{//The item matched with the research, we create a new button
				printf(item_name);
				printf("\n");
				p_button = gtk_button_new_with_label(item_name);
				gtk_grid_attach(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1)), p_button, 0, 0, 1, 1);
				g_signal_connect(G_OBJECT(p_button), "clicked", G_CALLBACK(cb_shopping_list), p_shopping_list);
				gtk_widget_show(p_button);
				search_success = TRUE;
			}
			itemPointerList_next(g_notebook->store->allocatedStock);
		}

		/**On teste si on a trouvé un item dans notre recherche
		*Si non, on crée un bouton comme quoi notre recherche a échouée*/
		if (!search_success)
		{
			sprintf(item_name, "Aucun item correspondant");
			p_button = gtk_button_new_with_label(item_name);
			gtk_grid_attach(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1)), p_button, 0, 0, 1, 1);
			gtk_widget_show(p_button);

		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(g_notebook->notebook), nbpages - 1);
	}
	free(p_shopping_list);


}

void cb_search_clear_button(GtkWidget *p_button, store_notebook *s_notebook){
	gboolean searching_tab_exists = FALSE;
	char text[20];
	sprintf(text, "recherche");
	gint nbpages;
	nbpages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(s_notebook->notebook));

	if (g_strcmp0(text, gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(s_notebook->notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1))) == 0)
	{
		searching_tab_exists = TRUE;
		printf("clear_button : searching tab exists\n");
	}

	if (searching_tab_exists)
		/*We destroy the existing tab*/
	{
		gtk_notebook_remove_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1);
	}
	gtk_notebook_set_current_page(GTK_NOTEBOOK(s_notebook->notebook), 0);
}


void cb_add_item(GtkWidget *p_widget, shopping_list * s_list){
	GtkWidget *p_new_label;
	GtkWidget *p_spin_button;
	const gchar * text;
	text = gtk_button_get_label(GTK_BUTTON(p_widget));

	item * n_item = item_new(0, fromage, text);
	itemPointerList_insert_first(s_list->shopping_itemlist, n_item);

	p_new_label = gtk_label_new(text);
	gtk_grid_insert_row(GTK_GRID(s_list->shopping_list_grid), 1);
	gtk_grid_attach(GTK_GRID(s_list->shopping_list_grid), p_new_label, 0, 1, 1, 1);


	p_spin_button = gtk_spin_button_new_with_range(1, 42, 1);
	gtk_grid_attach(GTK_GRID(s_list->shopping_list_grid), p_spin_button, 1, 1, 1, 1);
	gtk_widget_show(p_new_label);
	gtk_widget_show(p_spin_button);
	printf("ajout de %s a la liste (cb_add_item)\n", text);
}

void cb_end_list(GtkWidget *p_button, GtkWidget *p_window){
	//init_window();
	gtk_widget_destroy(GTK_WIDGET(p_window));
}

void cb_list_quit(GtkWidget *p_button, shopping * p_shopping){
	printf("cb_list_quit");
	itemPointerList_set_on_first(p_shopping->List);
	char * text;
	/*On parcours la liste pour remplir les items avec leur caractéristiques à partir de leur nom
	(oui je sais c'est moche mais on a plus le temps)*/
	while (!itemPointerList_is_out_of(p_shopping->List))
	{
		text = item_get_name(p_shopping->List->current->i);
		/*On parcours maintenant le shop pour trouver l'item correspondant :'(*/
		itemPointerList_set_on_first(p_shopping->Store->allocatedStock);
		while (!itemPointerList_is_out_of(p_shopping->Store->allocatedStock))
		{
			if (strcmp(text, item_get_name(p_shopping->Store->allocatedStock->current->i)) == 0)
			{
				p_shopping->List->current->i = p_shopping->Store->allocatedStock->current->i;
			}

			itemPointerList_next(p_shopping->Store->allocatedStock);
		}

		itemPointerList_next(p_shopping->List);
	}
}

static void open_file(const gchar *file_name, GtkTextView *p_text_view)
{
	g_return_if_fail(file_name && p_text_view);
	{
		gchar *contents = NULL;

		if (g_file_get_contents(file_name, &contents, NULL, NULL))
		{
			/* Copie de contents dans le GtkTextView */
		}
		else
		{
			print_warning("Impossible d'ouvrir le fichier %s\n", file_name);
		}
	}
}

//Function that opens the tab with the same label as the menu_item cliqued
void cb_open_tab(GtkWidget *p_menu_item, gpointer p_notebook){
	gint i = 0;
	const gchar *label;
	label = gtk_menu_item_get_label(GTK_MENU_ITEM(p_menu_item));
	for (i; i < gtk_notebook_get_n_pages(GTK_NOTEBOOK(p_notebook)); i++){
		if (g_strcmp0(gtk_label_get_label(GTK_LABEL(gtk_notebook_get_tab_label(GTK_NOTEBOOK(p_notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(p_notebook), i)))), label) == 0){
			gtk_notebook_set_current_page(GTK_NOTEBOOK(p_notebook), i);
			return;
		}
	}
	printf("WARNING : YOUR NOTEBOOKS TAB_LABEL AND MENU_ITEMS HAVE DIFFERENT NAMES");
}

