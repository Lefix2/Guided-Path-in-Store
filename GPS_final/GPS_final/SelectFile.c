#include <gtk\gtk.h>

#include "Common.h"
#include "Shopping.h"
#include "Store.h"
#include "ItemList.h"
#include "SelectFile.h"

void select_file(GtkWidget * parent, shopping * myShop)
{
	int nb_category;
	char **categories = NULL;
	char *path = NULL;
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new("Ouvrir un magasin", parent, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		path = gtk_file_chooser_get_filename(chooser);

		shopping_set_store(myShop, sqlite_new_store_from_database(path));
		categories = sqlite_get_category(path, &nb_category);
		store_set_categories(myShop->Store, nb_category, categories);

		//free the List
		itemPointerList_set_on_first(myShop->List);
		while (!itemPointerList_is_out_of(myShop->List))
		{
			itemPointerList_delete_first(myShop->List);
		}
	}
	else
	{
		printf("Warning : no file choosen, keeping last state\n");
	}

	gtk_widget_destroy(dialog);
	
}