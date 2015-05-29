#include <gtk\gtk.h>

#include "Common.h"
#include "Shopping.h"
#include "SelectFile.h"

void select_file(shopping * myShop)
{
	int nb_category;
	char **categories = NULL;
	char *path = NULL;
	GtkWidget *dialog, *window;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	dialog = gtk_file_chooser_dialog_new("Ouvrir un magasin", window, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		path = gtk_file_chooser_get_filename(chooser);
	}

	gtk_widget_destroy(dialog);
	shopping_set_store(myShop, sqlite_new_store_from_database(path));
	categories = sqlite_get_category(path, &nb_category);
	store_set_categories(myShop->Store, nb_category, categories);
	g_free(path);
}