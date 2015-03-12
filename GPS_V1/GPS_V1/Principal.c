#include <gtk/gtk.h>
#include "common.h"

#define MAIN_WINDOW_WIDTH 300
#define MAIN_WINDOW_HEIGHT 150
/* on quitte l'application en fermant la fffffffffffffenêtre */
void on_window_closed(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

void changer_texte(GtkWidget *window, gpointer data)
{
	GtkWidget *label;
	gchar *txtSchema;

	txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#FF5500\" size=\"xx-large\"><b>Coucou Clémence!</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_text(GTK_LABEL(data), txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(data), TRUE);
	g_free(txtSchema);
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{

	/* déclaration des variables */
	GtkWidget *window, *label, *box, *button;
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
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Super schéma</b></span>",-1,NULL,NULL,NULL);
	label = gtk_label_new(txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	g_free(txtSchema);
	button = gtk_button_new_with_label("Calculer l'itineraire");

	/* positionner les widgets */
	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	/* connecter le bouton à une fonction de callback */
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(changer_texte), label);


	/* afficher la fenêtre */
	gtk_widget_show_all(window);

	/* boucle principale */
	gtk_main();


	return EXIT_SUCCESS;
}

