#include "StoreImage.h"

GdkPixbuf *store_image_new_pixbuf_from_sprites(GdkPixbuf *sprites, gboolean has_alpha, int width, int height, int sprite)
{
	int h_sprite = gdk_pixbuf_get_width(sprites) / width;
	int v_sprite = gdk_pixbuf_get_height(sprites) / height;

	int x_sprite_pos = sprite % h_sprite;
	int y_sprite_pos = sprite / h_sprite;

	GdkPixbuf *newGdkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, gdk_pixbuf_get_bits_per_sample(sprites), width, height);
	gdk_pixbuf_composite(sprites, newGdkPixbuf, 0, 0, width, height, x_sprite_pos, y_sprite_pos, 1, 1, GDK_INTERP_NEAREST, 255);

	return newGdkPixbuf;
}