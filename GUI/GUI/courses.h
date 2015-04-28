#ifndef COURSES_H
#define COURSES_H

#include <gtk/gtk.h>
#include "common.h"


int init_courses(store * store_test);
GtkWidget * notebook_new_from_store(store * store_test);
int grid_find_category(char * category_name, GtkWidget * p_notebook);
void notebook_connect_button(GtkWidget * p_notebook, GtkWidget * p_shopping_list);


#endif //!COURSES_H

/*
sprintf(text, "Fruits");
p_onglet[0] = gtk_label_new(text);
p_grid[0] = gtk_grid_new();
gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook),p_grid[0], p_onglet[0]);
gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[1], 0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[9], 0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[10], 0, 2, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[0]), p_button[11], 0, 3, 1, 1);

sprintf(text, "Feculents");
p_onglet[1] = gtk_label_new(text);
p_grid[1] = gtk_grid_new();
gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[1], p_onglet[1]);
gtk_grid_attach(GTK_GRID(p_grid[1]), p_button[0], 0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[1]), p_button[7], 0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[1]), p_button[8], 0, 2, 1, 1);

sprintf(text, "Numerique");
p_onglet[2] = gtk_label_new(text);
p_grid[2] = gtk_grid_new();
gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[2], p_onglet[2]);

sprintf(text, "Jardinage");
p_onglet[3] = gtk_label_new(text);
p_grid[3] = gtk_grid_new();
gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[3], p_onglet[3]);
gtk_grid_attach(GTK_GRID(p_grid[3]), p_button[2], 0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[3]), p_button[6], 0, 1, 1, 1);

sprintf(text, "Entretien");
p_onglet[4] = gtk_label_new(text);
p_grid[4] = gtk_grid_new();
gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[4], p_onglet[4]);
gtk_grid_attach(GTK_GRID(p_grid[4]), p_button[3], 0, 0, 1, 1);
gtk_grid_attach(GTK_GRID(p_grid[4]), p_button[5], 0, 1, 1, 1);

sprintf(text, "Boisson");
p_onglet[5] = gtk_label_new(text);
p_grid[5] = gtk_grid_new();
gtk_notebook_append_page(GTK_NOTEBOOK(p_notebook), p_grid[5], p_onglet[5]);
gtk_grid_attach(GTK_GRID(p_grid[5]), p_button[4], 0, 0, 1, 1);



gtk_notebook_set_tab_pos(GTK_NOTEBOOK(p_notebook), GTK_POS_RIGHT);
gtk_notebook_set_show_tabs(GTK_NOTEBOOK(p_notebook), FALSE);

*/