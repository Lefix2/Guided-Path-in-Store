#include "callback.h"
#define DEFAULT_FILE "jules.c"


void cb_open(GtkWidget *p_widget, gpointer user_data)
{
	open_file(DEFAULT_FILE, GTK_TEXT_VIEW(user_data));

	/* Parametre inutilise */
	(void)p_widget;
}

void cb_quit(GtkWidget *p_widget, gpointer user_data){
	/*C'est ici qu'on libérera la mémoire allouée, qu'on fermera les fichiers, etc...*/
	gtk_main_quit();
}

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
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button),j+1);
			printf("Incrementation du nombre de %s dans la liste (cb_shopping_list)\n", text);
			return;
		}
		i++;
	}
	printf("cb_shopping_list appelle cb_add_item\n");
	cb_add_item(p_widget, s_list);
	i++;
}


void cb_activate_search_bar(GtkWidget *p_entry, store_notebook *s_notebook)
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

	gboolean searching_tab_exist = FALSE;
	gboolean search_success = FALSE;
	int i = 0;
	gint nbpages;
	nbpages = gtk_notebook_get_n_pages(GTK_NOTEBOOK(s_notebook->notebook));


	/**Pour commencer, on teste si l'onglet de recherche a deja ete cree
	*/
	printf("last tab label :\n");
	printf(gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(s_notebook->notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1)));
	printf("\n");
	if (g_strcmp0(text, gtk_notebook_get_tab_label_text(GTK_NOTEBOOK(s_notebook->notebook), gtk_notebook_get_nth_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1))) == 0)
	{ 
		searching_tab_exist = TRUE;
	}


	/**
	*On teste maintenant si l'utilisateur n'a pas clear sa recherche :
	*Si c'est le cas, on détruit la dernière page du notebook
	*/
	if (g_strcmp0(sText,"")==0)
	{
		printf("the user cleared his research\n");
		if (searching_tab_exist)
		{
			printf("trying to remove last page");
			gtk_notebook_remove_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1);
			nbpages--;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(s_notebook->notebook), 0); 
	}
	else
	{
		if (searching_tab_exist)
			/*We destroy the existing tab*/
		{
			gtk_notebook_remove_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1);
			nbpages--;
		}
		/*We create the last tab only activated when the user is searching*/
		printf("We create the last tab only activated when the user is searching\n");
		p_onglet = gtk_label_new(text);
		p_grid = gtk_grid_new();
		gtk_notebook_append_page(GTK_NOTEBOOK(s_notebook->notebook), p_grid, p_onglet);
		gtk_widget_show_all(s_notebook->notebook);
		nbpages++;


		/*On parcours la liste des items et on crée un button pour chacun de ceux qui correspondent*/
		itemPointerList_set_on_first(s_notebook->store->allocatedStock);
		while (!itemPointerList_is_out_of(s_notebook->store->allocatedStock))
		{
			item_name = (const gchar *)item_get_name(s_notebook->store->allocatedStock->current->i);

			if (g_str_has_prefix(item_name, sText) != 0)
			{//The item matched with the research, we create a new button
				printf(item_name);
				printf("\n");
				p_button = gtk_button_new_with_label(item_name);
				gtk_grid_attach(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1)), p_button, 0, 0, 1, 1);
				gtk_widget_show(p_button);
				search_success = TRUE;
			}
			itemPointerList_next(s_notebook->store->allocatedStock);
		}

		/**On teste si on a trouvé un item dans notre recherche
		*Si non, on crée un bouton comme quoi notre recherche a échouée*/
		if (!search_success)
		{
			sprintf(item_name, "Aucun item correspondant");
			p_button = gtk_button_new_with_label(item_name);
			gtk_grid_attach(GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1)), p_button, 0, 0, 1, 1);
			gtk_widget_show(p_button);

		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(s_notebook->notebook), nbpages - 1);
	}

	
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

