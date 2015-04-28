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

