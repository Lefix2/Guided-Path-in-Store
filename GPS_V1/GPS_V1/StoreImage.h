#ifndef STOREIMAGE_H
#define STOREIMAGE_H

#include "Common.h"
#include <gtk\gtk.h>

GdkPixbuf *store_image_new_pixbuf_from_sprites(GdkPixbuf *sprites, gboolean has_alpha, int width, int height, int sprite);

#endif // !STOREIMAGE_H
