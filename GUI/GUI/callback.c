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
	gtk_box_pack_end(GTK_BOX(box), p_new_label, FALSE, FALSE, 0);
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
