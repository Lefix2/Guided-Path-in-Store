#include "Common.h"
#include "Item.h"
#include "ItemList.h"
#include "Section.h"
#include "Store.h"
#include "Astar.h"
#include "Shopping.h"
#include "merchant.h"
#include "StoreImage.h"
#include "map.h"
#include "generalMenu.h"

#define MAIN_WINDOW_WIDTH 300
#define MAIN_WINDOW_HEIGHT 150

#define M_PI 3.1415

GtkWidget *drawing_area;
GtkWidget *window;


/* on quitte l'application en fermant la fenêtre */
void on_window_closed(GtkWidget *window, gpointer data)
{
	gtk_widget_destroy(window);
	gtk_widget_set_sensitive(data, TRUE);
}

gboolean changer_texte(GtkWidget *window, gpointer data)
{
	gchar *txtSchema;
	gchar utf8_chain[MAX_ARRAY_OF_CHAR];

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
	int x, y, sx, sy, id;
	printf("Rentreze x, y, size x, size y , id:\n");
	scanf("%d", &x); scanf("%d", &y); scanf("%d", &sx); scanf("%d", &sy); scanf("%d", &id);
	store_add_new_section(((shopping*)data)->Store, id, t_section, x, y, sx, sy);
	merchant_optimise_shopping((shopping*)data);
	gtk_widget_queue_draw(drawing_area);
	return FALSE;
}

gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{

	guint width, height, i;
	GdkRGBA color;
	GdkPixbuf *store_pixbuf = store_image_new_pixbuf_from_store(((shopping*)data)->Store);

	gdk_cairo_set_source_pixbuf(cr, store_pixbuf, 0, 0);
	width = gdk_pixbuf_get_width(store_pixbuf);
	height = gdk_pixbuf_get_height(store_pixbuf);
	cairo_rectangle(cr, 0, 0, width, height);

	cairo_fill(cr);

	store_image_draw_shopping(cr, (shopping*)data);

	return FALSE;
}

void init_map(GtkWidget *p_window, shopping *shopping)
{
	/* déclaration des variables */
	GtkWidget *label, *h_box, *b_box, *v_box, *button, *button1, *button2, *button3, *button4, *button5;
	gchar *txtSchema, *utfstring = NULL;

	/* créer la fenêtre avec son titre */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Guided Path in Store");
	gtk_window_set_default_size(GTK_WINDOW(window), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 500);
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "ressources\\Images\\caddie.jpg", NULL);
	//gtk_window_set_keep_above(window, TRUE);

	/* créer les widgets */
	h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	b_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	txtSchema = (char*)calloc(MAX_ARRAY_OF_CHAR, sizeof(char));

	sprintf(txtSchema, "<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>%s</b></span>", store_get_name(shopping_get_store(shopping)));
	utfstring = g_locale_to_utf8(txtSchema, -1, NULL, NULL, NULL);
	label = gtk_label_new(utfstring);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);

	free(txtSchema);
	g_free(utfstring);
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
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_closed), p_window);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(changer_texte), label);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(button1_callback), NULL);
	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(button2_callback), NULL);
	g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(button3_callback), NULL);
	g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(button4_callback), NULL);

	GtkImage *imtest = gtk_image_new();
	GtkWidget *event_box = gtk_event_box_new();
	GtkWidget *scrollmenuV = gtk_scrolled_window_new(NULL, NULL);
	
	//set dfault sprites
	store_set_sprites(shopping->Store, gdk_pixbuf_new_from_file(".\\ressources\\images\\sprites.png", NULL));
	drawing_area = gtk_drawing_area_new();

	gtk_box_pack_start(GTK_BOX(v_box), scrollmenuV, TRUE, TRUE, 0);

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollmenuV), drawing_area);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw_callback), shopping);
	g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(button5_callback), shopping);

	/* afficher la fenêtre */
	gtk_widget_show_all(window);

	return EXIT_SUCCESS;
}