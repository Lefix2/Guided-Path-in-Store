#include <gtk/gtk.h>

#include "Common.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"

#define MAIN_WINDOW_WIDTH 300
#define MAIN_WINDOW_HEIGHT 150
/* on quitte l'application en fermant la fenêtre */
void on_window_closed(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

gboolean changer_texte(GtkWidget *window, gpointer data)
{
	gchar *txtSchema;
	gchar utf8_chain[256];

	sprintf(utf8_chain, "<span face=\"Verdana\" foreground=\"#%02X%02X%02X\" size=\"xx-large\"><b>Console cleared</b></span>", rand() % (0xFF), rand() % (0xFF), rand() % (0xFF));
	txtSchema = g_locale_to_utf8(utf8_chain, -1, NULL, NULL, NULL);
	gtk_label_set_text(GTK_LABEL(data), txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(data), TRUE);
	g_free(txtSchema);
	gtk_widget_show_all(window);
	system("cls");

	return FALSE;
}

gboolean button1_callback(GtkWidget *window, gpointer data)
{
	testItem();
	return FALSE;
}

gboolean button2_callback(GtkWidget *window, gpointer data)
{
	testSect();
	return FALSE;
}

gboolean button3_callback(GtkWidget *window, gpointer data)
{
	testStore();
	return FALSE;
}

gboolean button4_callback(GtkWidget *window, gpointer data)
{
	testAstar();
	return FALSE;
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	guint width, height;
	GdkRGBA color;

	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);
	cairo_rectangle(cr, 10, 10, width / 2.0, height / 2.0);

	/*cairo_arc(cr,
		width / 2.0, height / 2.0,
		MIN(width, height) / 2.0,
		0, 2 * G_PI);*/

	gtk_style_context_get_color(gtk_widget_get_style_context(widget),
		0,
		&color);
	gdk_cairo_set_source_rgba(cr, &color);

	cairo_fill(cr);

	return FALSE;
}

int main(int argc, char *argv[])
{

	/* déclaration des variables */
	GtkWidget *window, *label, *v_box, *h_box,*button, *button1, *button2, *button3, *button4, *drawArea;
	gchar *txtSchema = NULL;

	/* initialiser GTK+ */
	gtk_init(&argc, &argv);

	/* créer la fenêtre avec son titre */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Guided Path in Store");
	gtk_window_set_default_size(GTK_WINDOW(window), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "ressources\\caddie.jpg", NULL);

	/* créer les widgets */
	v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Petite superette</b></span>",-1,NULL,NULL,NULL);
	label = gtk_label_new(txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	g_free(txtSchema);
	button = gtk_button_new_with_label("Pimp my text");
	button1 = gtk_button_new_with_label("Test Item");
	button2 = gtk_button_new_with_label("Test Section");
	button3 = gtk_button_new_with_label("Test Store");
	button4 = gtk_button_new_with_label("Test Astar");

	drawArea = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawArea, 50, 50);

	/* positionner les widgets */
	gtk_container_add(GTK_CONTAINER(window), h_box);

	gtk_box_pack_start(GTK_BOX(v_box), button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_box), button1, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_box), button2, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_box), button3, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(v_box), button4, FALSE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(h_box), drawArea, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(h_box), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(h_box),v_box, FALSE, FALSE, 0);

	/* connecter le bouton à une fonction de callback */
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(changer_texte), label);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(button1_callback), NULL);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(button2_callback), NULL);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(button3_callback), NULL);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(button4_callback), NULL);
	g_signal_connect(G_OBJECT(drawArea), "draw",G_CALLBACK(draw_callback), NULL);


	/* afficher la fenêtre */
	gtk_widget_show_all(window);

	/* boucle principale */
	gtk_main();


	return EXIT_SUCCESS;
}
