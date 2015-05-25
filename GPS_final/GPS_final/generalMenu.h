#ifndef GENERALMENU_H
#define GENERALMENU_H

void call_main_menu();
gboolean cb_quit(GtkWidget *p_widget, gpointer user_data);
gboolean cb_store_selection(GtkWidget *p_widget, gpointer p_window);
gboolean cb_make_list(GtkWidget *p_widget, gpointer p_window);
gboolean cb_go_shopping(GtkWidget *p_widget, gpointer p_window);

#endif // !GENERALMENU_H
