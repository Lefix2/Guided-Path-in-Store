#include "Common.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"
#include "StoreImage.h"

#define MAIN_WINDOW_WIDTH 300
#define MAIN_WINDOW_HEIGHT 150

#define M_PI 3.1415

GtkWidget *drawing_area;

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

gboolean button5_callback(GtkWidget *window, gpointer data)
{
	store_add_section((store*)data, 15, t_section, 30, 3, 5, 3);
	gtk_widget_queue_draw(drawing_area);
	return FALSE;
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	
	guint width, height;
	GdkRGBA color;
	GdkPixbuf *store_pixbuf = store_image_new_pixbuf_from_store(data);

	gdk_cairo_set_source_pixbuf(cr, store_pixbuf, 0, 0);
	width = gdk_pixbuf_get_width(store_pixbuf);
	height = gdk_pixbuf_get_height(store_pixbuf);
	cairo_rectangle(cr, 0, 0, width, height);
	
	cairo_fill(cr);

	return FALSE;
}

int main(int argc, char *argv[])
{

	/* déclaration des variables */
	GtkWidget *window, *label, *h_box, *b_box, *v_box,*button, *button1, *button2, *button3, *button4, *button5;
	gchar *txtSchema = NULL;

	/* initialiser GTK+ */
	gtk_init(&argc, &argv);

	/* créer la fenêtre avec son titre */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Guided Path in Store");
	gtk_window_set_default_size(GTK_WINDOW(window), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "ressources\\caddie.jpg", NULL);

	/* créer les widgets */
	h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	b_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	txtSchema = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Petite superette</b></span>",-1,NULL,NULL,NULL);
	label = gtk_label_new(txtSchema);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
	g_free(txtSchema);
	button = gtk_button_new_with_label("Pimp my text");
	button1 = gtk_button_new_with_label("Test Item");
	button2 = gtk_button_new_with_label("Test Section");
	button3 = gtk_button_new_with_label("Test Store");
	button4 = gtk_button_new_with_label("Test Astar");
	button5 = gtk_button_new_with_label("Test Cairo");

	/* positionner les widgets */
	gtk_box_pack_start(GTK_BOX(h_box), b_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(h_box), v_box, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), h_box);

	gtk_box_pack_start(GTK_BOX(b_box), button, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(b_box), button1, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(b_box), button2, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(b_box), button3, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(b_box), button4, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(b_box), button5, FALSE, FALSE, 5);

	gtk_box_pack_start(GTK_BOX(v_box), label, FALSE, FALSE, 0);

	/* connecter le bouton à une fonction de callback */
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), NULL);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(changer_texte), label);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(button1_callback), NULL);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(button2_callback), NULL);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(button3_callback), NULL);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(button4_callback), NULL);


	GdkPixbuf *sprites;
	GtkImage *imtest = gtk_image_new();
	GError **error = NULL;
	GtkWidget *event_box = gtk_event_box_new();
	GtkWidget *scrollmenuV = gtk_scrolled_window_new(NULL, NULL);;
	drawing_area = gtk_drawing_area_new();

	//gtk_container_add(GTK_CONTAINER(event_box), scrollmenuV);
	//gtk_scrolled_window_add_with_viewport(scrollmenuV, imtest);
	sprites = gdk_pixbuf_new_from_file("sprites.png", error);
	gtk_box_pack_start(GTK_BOX(v_box), scrollmenuV, TRUE, TRUE, 0);
	
	int magsizex = 40;
	int magsizey = 40;

	store * sttest = store_new(0, "Carrefour - rennes", magsizex, magsizey);

	store_set_sprites(sttest, sprites);

	store_add_section(sttest, 1, t_wall, 0, 1, 1, magsizey - 1);
	store_add_section(sttest, 2, t_wall, 1, magsizey - 1, magsizex - 1, 1);
	store_add_section(sttest, 3, t_wall, magsizex - 1, 0, 1, magsizey - 1);
	store_add_section(sttest, 4, t_wall, 0, 0, magsizex - 1, 1);

	store_add_section(sttest, 5, t_promo, 3, 3, 15, 2);
	store_add_section(sttest, 6, t_section, 3, 6, 15, 2);
	store_add_section(sttest, 7, t_section, 3, 9, 15, 2);
	store_add_section(sttest, 8, t_section, 3, 12, 15, 2);
	store_add_section(sttest, 9, t_section, 3, 15, 15, 2);
	store_add_section(sttest, 10, t_section, 3, 18, 15, 2);
	store_add_section(sttest, 11, t_section, 3, 21, 11, 11);
	store_add_section(sttest, 12, t_section, 15, 21, 1, 11);
	store_add_section(sttest, 13, t_checkout, 3, 32, 10, 3);
	store_add_section(sttest, 14, t_entrance, 15, 35, 10, 3);


	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollmenuV), drawing_area);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), sttest);
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(button5_callback), sttest);

	/* afficher la fenêtre */
	gtk_widget_show_all(window);

	/* boucle principale */
	gtk_main();


	return EXIT_SUCCESS;
}
