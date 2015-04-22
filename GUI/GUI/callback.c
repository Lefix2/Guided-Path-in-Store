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

void cb_shopping_list(GtkWidget *p_widget, gpointer box){
	GtkWidget *p_new_label;
	const gchar * text;
	text = gtk_button_get_label(GTK_BUTTON(p_widget));
	p_new_label = gtk_button_new_with_label(text);
	gtk_box_pack_start(GTK_BOX(box), p_new_label, FALSE, FALSE, 0);
	gtk_widget_show(p_new_label);
	printf("ajout de %s a la liste\n", text);
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
