#include "jules.h"

int init_window(){
	GtkWidget *p_window = NULL;
	GtkWidget *p_window2 = NULL;
	GtkWidget *p_main_box = NULL;
	GtkWidget *close_button = NULL;
	GtkWidget *print_button = NULL;
	GtkWidget *p_text_view = NULL;
	GtkWidget *p_button_box = NULL;
	GtkWidget *p_open_button = NULL;

	

	/* Window Creation */
	p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	p_window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(cb_quit), NULL);
	g_signal_connect(G_OBJECT(p_window2), "destroy", G_CALLBACK(cb_quit), NULL);

	/*Creation of a box containing the widgets*/
	p_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	p_button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
	gtk_container_add(GTK_CONTAINER(p_window), p_main_box);

	/* Let's add two buttons to the box */
	close_button = gtk_button_new_from_stock(GTK_STOCK_CLEAR);
	print_button = gtk_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
	p_open_button = gtk_button_new_from_stock(GTK_STOCK_OPEN);
	g_signal_connect(G_OBJECT(close_button), "enter", G_CALLBACK(cb_quit), NULL); // Et on connecte le clic à la fermeture de la fenetre
	g_signal_connect(G_OBJECT(p_open_button), "clicked", G_CALLBACK(cb_open), p_text_view);
	gtk_box_pack_start(GTK_BOX(p_main_box), p_button_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(p_button_box), close_button, FALSE, FALSE, 0); // On le met dans un conteneur, ici la fenetre
	gtk_box_pack_start(GTK_BOX(p_button_box), print_button, FALSE, FALSE, 0);
	gtk_button_set_relief(GTK_BUTTON(print_button), GTK_RELIEF_NONE);
	gtk_button_set_label(GTK_BUTTON(close_button), "ATTENTION NE PAS SURVOLER");

	/*Creation of a Widget to edit text*/
	p_text_view = gtk_text_view_new();
	gtk_box_pack_start(GTK_BOX(p_main_box), p_text_view, TRUE, TRUE, 0);

	/* Window display */
	gtk_widget_show(p_window);
	//gtk_widget_show(p_main_box); // or gtk_widget_show_all
	//gtk_widget_show(close_button);
	gtk_widget_show_all(p_main_box);
	//gtk_window_maximize(GTK_WINDOW(p_window));
	gtk_window_set_title(GTK_WINDOW(p_window), "Guided Path in Store");
	gtk_window_set_title(GTK_WINDOW(p_window2), "Liste de courses");

	return EXIT_SUCCESS;
}

int main(int argc, char **argv){
	/* GTK Initialisation */
	gtk_init(&argc, &argv);
	itemList * user_list = NULL;
	user_list = itemPointerList_new();
	store * store_test = NULL;
	store_test = testStore();

	init_courses(store_test, user_list);
	
	/* Main loop start */
	gtk_main();

	itemPointerList_print(user_list, FALSE);
	system("pause");
	return EXIT_SUCCESS;
}




