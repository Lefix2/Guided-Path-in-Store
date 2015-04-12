#include <stdlib.h>
#include <gtk/gtk.h>


void cb_quit(GtkWidget *, gpointer);

int main(int argc, char **argv){
	GtkWidget *p_window = NULL;
	GtkWidget *p_main_box = NULL;
	GtkWidget *close_button = NULL; 

	/* GTK Initialisation */
	gtk_init(&argc,&argv);
	
	/* Window Creation */
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);

	/*Creation of a box containing the widgets*/
	p_main_box = gtk_box_new(FALSE, 0); 
	gtk_container_add(GTK_CONTAINER(p_window), p_main_box);

	/* Let's add a button to the box */
	close_button = gtk_button_new_from_stock(GTK_STOCK_CLEAR);
	g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(cb_quit), NULL); // Et on connecte le clic à la fermeture de la fenetre
	gtk_box_pack_start(GTK_BOX(p_main_box), close_button, FALSE, FALSE, 0); // On le met dans un conteneur, ici la fenetre


	/* Window display */
	gtk_widget_show(p_window);
	gtk_widget_show(p_main_box); // or gtk_widget_show_all
	gtk_widget_show(close_button);

	/* Main loop start */
	gtk_main();

	return EXIT_SUCCESS;
}


void cb_quit(GtkWidget *p_widget, gpointer user_data){
	/*C'est ici qu'on libérera la mémoire allouée, qu'on fermera les fichiers, etc...*/
	gtk_main_quit();
}