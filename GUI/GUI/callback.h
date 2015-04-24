#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void cb_open(GtkWidget *p_widget, gpointer user_data);
void cb_quit(GtkWidget *p_widget, gpointer user_data);
void cb_shopping_list(GtkWidget *p_widget, gpointer box);
void cb_open_tab(GtkWidget *p_widget, gpointer user_data);
static void open_file(const gchar *file_name, GtkTextView *p_text_view);

#endif /* not CALLBACK_H */