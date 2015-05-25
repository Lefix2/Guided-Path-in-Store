#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "common.h"
#include "courses.h"
#include "ItemList.h"
#include "Store.h"
#include "Item.h"
#include "jules.h"

void cb_open(GtkWidget *p_widget, gpointer user_data);
void cb_quit(GtkWidget *p_widget, gpointer user_data);
void cb_shopping_list(GtkWidget *p_widget, shopping_list * s_list);
void cb_add_item(GtkWidget *p_widget, gpointer grid);
void cb_activate_search_bar(GtkWidget *p_entry, store_notebook * s_notebook);
void cb_search_clear_button(GtkWidget *p_button, store_notebook *s_notebook);
void cb_open_tab(GtkWidget *p_widget, gpointer user_data);
void cb_end_list(GtkWidget *p_button, store_notebook *s_notebook);
static void open_file(const gchar *file_name, GtkTextView *p_text_view);

#endif /* not CALLBACK_H */