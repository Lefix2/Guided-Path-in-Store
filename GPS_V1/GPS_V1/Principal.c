#include <gtk/gtk.h>

/* on quitte l'application en fermant la fenêtre */
void on_window_closed(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{

	/* déclaration des variables */
	GtkWidget *window, *label, *box, *button;

	/* initialiser GTK+ */
	gtk_init(&argc, &argv);


	/* créer la fenêtre avec son titre */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Test GTK+3");

	/* créer les widgets */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	label = gtk_label_new("Salut !");
	button = gtk_button_new_with_label("Salut !");

	/* positionner les widgets */
	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);


	/* afficher la fenêtre */
	gtk_widget_show_all(window);

	/* boucle principale */
	gtk_main();


	return 0;
}