#include "callback.h"


void cb_quit(GtkWidget *p_widget, gpointer user_data){
	/*C'est ici qu'on lib�rera la m�moire allou�e, qu'on fermera les fichiers, etc...*/
	gtk_main_quit();
}

void cb_store_selection(GtkWidget *p_widget, gpointer p_window){
	store_selection_window();
	gtk_widget_destroy(GTK_WIDGET(p_window));
}