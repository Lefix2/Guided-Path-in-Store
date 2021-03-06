/*!
* \file  generalMenu.c
* \brief functions to displain the main menu
* \author GPS team
* \date 13/12/2014
*/
#include "Common.h"
#include "Shopping.h"
#include "courses.h"
#include "generalMenu.h"
#include "SelectFile.h"
#include "go_shopping.h"
#include "tests.h"
#include "Store_IO_functions.h"

/*!
* \fn void call_main_menu(GtkApplication *app)
* \brief call gtk elements to display menu
* \param[in] app the gtk application associed
* \return the new allocated node
*/
void call_main_menu(GtkApplication *app)
{
	generalmenu_struct *main_menu;

	main_menu = g_new(generalmenu_struct, 1);
	GtkImage *WelcomeImg = gtk_image_new_from_file(".\\ressources\\Images\\mainMenu.png");

	main_menu->myShop = shopping_new();

	/* Window Creation */
	main_menu->main_window = gtk_application_window_new(app);

	gtk_window_set_position(GTK_WINDOW(main_menu->main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(main_menu->main_window), "Guided Path in Store");
	gtk_window_set_resizable(main_menu->main_window, FALSE);
	gtk_window_set_icon_from_file(GTK_WINDOW(main_menu->main_window), "ressources\\Images\\icon.png", NULL);
	g_signal_connect(G_OBJECT(main_menu->main_window), "destroy", G_CALLBACK(cb_quit), main_menu);
	
	/*The window contain a grid that contains all of our widgets*/
	GtkWidget * v_box = NULL;
	v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	gtk_container_add(GTK_CONTAINER(main_menu->main_window), v_box);

	/*add a title*/
	gtk_box_pack_start(GTK_BOX(v_box), WelcomeImg, TRUE, TRUE, 0);

	/*The first button is used to open the database to choose a store*/
	main_menu->button_selec = gtk_button_new_with_label("Ouvrir un magasin");
	g_signal_connect(GTK_BUTTON(main_menu->button_selec), "clicked", G_CALLBACK(cb_store_selection), main_menu);
	gtk_box_pack_start(GTK_BOX(v_box), main_menu->button_selec, FALSE, FALSE, 0);

	/*The second button is used to create his list*/
	main_menu->button_makel = gtk_button_new_with_label("Faire sa liste de course");
	g_signal_connect(GTK_BUTTON(main_menu->button_makel), "clicked", G_CALLBACK(cb_make_list), main_menu);
	gtk_box_pack_start(GTK_BOX(v_box), main_menu->button_makel, FALSE, FALSE, 0);
	gtk_widget_set_sensitive(main_menu->button_makel, FALSE);

	/*The third is to start the shopping*/
	main_menu->button_gosho = gtk_button_new_with_label("Demarrer ses courses");
	g_signal_connect(GTK_BUTTON(main_menu->button_gosho), "clicked", G_CALLBACK(cb_go_shopping), main_menu);
	gtk_box_pack_start(GTK_BOX(v_box), main_menu->button_gosho, FALSE, FALSE, 0);
	gtk_widget_set_sensitive(main_menu->button_gosho, FALSE);


	/*We do the last settings to the window*/
	gtk_widget_show_all(main_menu->main_window);

}

/*!
* \fn gboolean cb_quit(GtkWidget *p_widget, generalmenu_struct *main_menu)
* \brief callback to quit main menu and application
* \param[in] p_widget callback widget
* \param[in] main_menu the main menu structure
* \return FALSE
*/
gboolean cb_quit(GtkWidget *p_widget, generalmenu_struct *main_menu){
	gtk_main_quit();
	shopping_delete(main_menu->myShop);
	g_free(main_menu);
	printf("Allocated blocs : %d\n", myCheck());
	return FALSE;
}

/*!
* \fn gboolean cb_store_selection(GtkWidget *p_widget, generalmenu_struct *main_menu)
* \brief callback to select a file
* \param[in] p_widget callback widget
* \param[in] main_menu the main menu structure
* \return FALSE
*/
gboolean cb_store_selection(GtkWidget *p_widget, generalmenu_struct *main_menu){

	select_file(main_menu->main_window, main_menu->myShop);
	if (main_menu->myShop->Store != NULL)
		gtk_widget_set_sensitive(main_menu->button_makel, TRUE);
	else
	{
		gtk_widget_set_sensitive(main_menu->button_makel, FALSE);
	}

	if (main_menu->myShop->List->first != NULL)
		gtk_widget_set_sensitive(main_menu->button_gosho, TRUE);
	else
		gtk_widget_set_sensitive(main_menu->button_gosho, FALSE);

	return FALSE;
}

/*!
* \fn gboolean cb_make_list(GtkWidget *p_widget, generalmenu_struct *main_menu)
* \brief callback to call the shopping list menu
* \param[in] p_widget callback widget
* \param[in] main_menu the main menu structure
* \return FALSE
*/
gboolean cb_make_list(GtkWidget *p_widget, generalmenu_struct *main_menu){

	gtk_widget_set_sensitive(main_menu->main_window, FALSE);
	init_courses(main_menu, main_menu->myShop);

	return FALSE;
}

/*!
* \fn gboolean cb_go_shopping(GtkWidget *p_widget, generalmenu_struct *main_menu)
* \brief callback to call the shopping display menu
* \param[in] p_widget callback widget
* \param[in] main_menu the main menu structure
* \return FALSE
*/
gboolean cb_go_shopping(GtkWidget *p_widget, generalmenu_struct *main_menu){
	gtk_widget_set_sensitive(main_menu->main_window, FALSE);
	go_shopping_window(main_menu->main_window, main_menu->myShop);
	return FALSE;
}
