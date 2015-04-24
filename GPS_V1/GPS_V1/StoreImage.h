#ifndef STOREIMAGE_H
#define STOREIMAGE_H

#include "Common.h"
#include <gtk\gtk.h>

#define SPRITE_RES 20

#define SPRITE_PER_LINE 15

GdkPixbuf *store_image_new_pixbuf_from_store(store *src, GdkPixbuf *sprites);
GdkPixbuf *store_image_new_pixbuf_from_section(section *src, GdkPixbuf *sprites);
GdkPixbuf *store_image_new_pixbuf_from_sprites(GdkPixbuf *sprites, gboolean has_alpha, int width, int height, int sprite);
void store_image_merge_pixbuf(GdkPixbuf *src, GdkPixbuf *dest, int dest_x, int dest_y);
#endif // !STOREIMAGE_H
