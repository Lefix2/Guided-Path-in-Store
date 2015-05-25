#ifndef MAP_H
#define MAP_H

void on_window_closed(GtkWidget *window, gpointer data);
gboolean changer_texte(GtkWidget *window, gpointer data);

gboolean button1_callback(GtkWidget *window, gpointer data);
gboolean button2_callback(GtkWidget *window, gpointer data);
gboolean button3_callback(GtkWidget *window, gpointer data);
gboolean button4_callback(GtkWidget *window, gpointer data);
gboolean button5_callback(GtkWidget *window, gpointer data);

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data);

void init_map(shopping *shopping);

#endif // !MAP_H
