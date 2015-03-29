#include <gtk/gtk.h>

#include "Common.h"
#include "ItemList.h"
#include "Section.h"

#define MAIN_WINDOW_WIDTH 300
#define MAIN_WINDOW_HEIGHT 150
/* on quitte l'application en fermant la fenêtre */
void on_window_closed(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

gboolean changer_texte(GtkWidget *window, gpointer data)
{
	GtkWidget *label;
	gchar *txtSchema;

	testSect();
	txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#FF5500\" size=\"xx-large\"><b>On est des Ouf !</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_text(GTK_LABEL(data), txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(data), TRUE);
	g_free(txtSchema);
	gtk_widget_show_all(window);

	return FALSE;
}

int main(int argc, char *argv[])
{

	/* déclaration des variables */
	GtkWidget *window, *label, *v_box, *h_box, *button1, *button2, *button3;
	gchar *txtSchema = NULL;

	/* initialiser GTK+ */
	gtk_init(&argc, &argv);

	/* créer la fenêtre avec son titre */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Guided Path in Store");
	gtk_window_set_default_size(GTK_WINDOW(window), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "ressources\\caddie.jpg", NULL);

	/* créer les widgets */
	v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Petite superette</b></span>",-1,NULL,NULL,NULL);
	label = gtk_label_new(txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	g_free(txtSchema);
	button1 = gtk_button_new_with_label("Afficher les stocks");
	button2 = gtk_button_new_with_label("Test bouton 1");
	button3 = gtk_button_new_with_label("Test bouton 2");

	/* positionner les widgets */
	gtk_container_add(GTK_CONTAINER(window), h_box);

	gtk_box_pack_start(GTK_BOX(v_box), button1, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(v_box), button2, FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(v_box), button3, FALSE, FALSE, 10);

	gtk_box_pack_start(GTK_BOX(h_box), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(h_box), GTK_BOX(v_box), FALSE, FALSE, 0);

	/* connecter le bouton à une fonction de callback */
  g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(changer_texte), label);


	/* afficher la fenêtre */
	gtk_widget_show_all(window);

	/* boucle principale */
	gtk_main();


	return EXIT_SUCCESS;
}