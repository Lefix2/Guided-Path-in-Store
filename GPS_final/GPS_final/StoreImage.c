#include <math.h>

#include "StoreImage.h"
#include "Item.h"
#include "ItemList.h"
#include "Section.h"
#include "SectionList.h"
#include "Store.h"
#include "Shopping.h"

typedef enum spriteOrientation{
	middle, topLeftCorner, topRightCorner, botRightCorner, botLeftCorner, top, right, bot, left, singleVert, singleHor, singleUp, singleRight, singleDown, singleLeft
}spriteOrientation;

GdkPixbuf *store_image_new_pixbuf_from_store(store *src)
{
	int x, y;

	int width = store_get_x_size(src);
	int height = store_get_y_size(src);
	GdkPixbuf *sprites = store_get_sprites(src);
	GdkPixbuf *newGdkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, gdk_pixbuf_get_bits_per_sample(sprites), width * SPRITE_RES, height * SPRITE_RES);

	GdkPixbuf *floor;
	srand(1);
	for (y = 0; y < height; y ++)
	{
		for (x = 0; x < width; x ++)
		{
			floor = store_image_new_pixbuf_from_sprites(sprites, FALSE, SPRITE_RES, SPRITE_RES, middle + (rand() % SPRITE_PER_LINE) + t_floor*SPRITE_PER_LINE);
			store_image_merge_pixbuf(floor, newGdkPixbuf, x*SPRITE_RES, y*SPRITE_RES);
			g_object_unref(floor);
		}
	}
	
	section *currentSection;
	sectionList *sections = store_get_allocatedSections(src);
	GdkPixbuf *currentSectionPixbuf;

	//création du pixbuf
	sectionPointerList_set_on_first(sections);
	while (!sectionPointerList_is_out_of(sections))
	{
		currentSection = sectionPointerList_get_current(sections);

		x = section_get_pos(currentSection).x;
		y = section_get_pos(currentSection).y;

		currentSectionPixbuf = store_image_new_pixbuf_from_section(currentSection, sprites);
		store_image_merge_pixbuf(currentSectionPixbuf, newGdkPixbuf, x*SPRITE_RES, y*SPRITE_RES);

		g_object_unref(currentSectionPixbuf);
		sectionPointerList_next(sections);
	}

	return newGdkPixbuf;
}

GdkPixbuf *store_image_new_pixbuf_from_section(section *src, GdkPixbuf *sprites)
{
	int x, y;
	int width = section_get_size(src).x;
	int height = section_get_size(src).y;

	guint32 color;

	GdkPixbuf *newGdkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, gdk_pixbuf_get_bits_per_sample(sprites), width * SPRITE_RES, height * SPRITE_RES);
	gdk_pixbuf_fill(newGdkPixbuf, 0x00000000);
	GdkPixbuf *actualSprite;

	spriteOrientation actualSpriteOrientation;
	type actualSpriteType = section_get_type(src);
	
	if (width == 1)
	{
		x = 0;
		for (y = 0; y < height; y++)
		{
			if (y == 0)
				actualSpriteOrientation = singleUp;
			else if (y == height - 1)
				actualSpriteOrientation = singleDown;
			else
				actualSpriteOrientation = singleVert;

			actualSprite = store_image_new_pixbuf_from_sprites(sprites, TRUE, SPRITE_RES, SPRITE_RES, actualSpriteOrientation + actualSpriteType*SPRITE_PER_LINE);
			store_image_merge_pixbuf(actualSprite, newGdkPixbuf, x*SPRITE_RES, y*SPRITE_RES);

			g_object_unref(actualSprite);
		}
	}
	else if (height == 1)
	{
		y = 0;
		for (x = 0; x < width; x++)
		{
			if (x == 0)
				actualSpriteOrientation = singleLeft;
			else if (x == width - 1)
				actualSpriteOrientation = singleRight;
			else
				actualSpriteOrientation = singleHor;

			actualSprite = store_image_new_pixbuf_from_sprites(sprites, TRUE, SPRITE_RES, SPRITE_RES, actualSpriteOrientation + actualSpriteType*SPRITE_PER_LINE);
			store_image_merge_pixbuf(actualSprite, newGdkPixbuf, x*SPRITE_RES, y*SPRITE_RES);

			g_object_unref(actualSprite);
		}
	}
	else
	{
		for (y = 0; y < height; y++)
		{
			for (x = 0; x < width; x++)
			{
				if (y == 0)
				{
					if (x == 0)
						actualSpriteOrientation = topLeftCorner;
					else if (x == width - 1)
						actualSpriteOrientation = topRightCorner;
					else
						actualSpriteOrientation = top;
				}
				else if (y == height - 1)
				{
					if (x == 0)
						actualSpriteOrientation = botLeftCorner;
					else if (x == width - 1)
						actualSpriteOrientation = botRightCorner;
					else
						actualSpriteOrientation = bot;
				}
				else
				{
					if (x == 0)
						actualSpriteOrientation = left;
					else if (x == width - 1)
						actualSpriteOrientation = right;
					else
						actualSpriteOrientation = middle;
				}

				actualSprite = store_image_new_pixbuf_from_sprites(sprites, TRUE, SPRITE_RES, SPRITE_RES, actualSpriteOrientation + actualSpriteType*SPRITE_PER_LINE);
				store_image_merge_pixbuf(actualSprite, newGdkPixbuf, x*SPRITE_RES, y*SPRITE_RES);

				g_object_unref(actualSprite);
			}
		}
	}
	return newGdkPixbuf;
}

GdkPixbuf *store_image_new_pixbuf_from_sprites(GdkPixbuf *sprites, gboolean has_alpha, int width, int height, int sprite)
{
	int h_sprite = gdk_pixbuf_get_width(sprites) / width;
	int v_sprite = gdk_pixbuf_get_height(sprites) / height;

	int x_sprite_pos = sprite % h_sprite;
	int y_sprite_pos = sprite / h_sprite;

	int bitPerSample = gdk_pixbuf_get_bits_per_sample(sprites);

	GdkPixbuf *newGdkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, bitPerSample, width, height);
	gdk_pixbuf_fill(newGdkPixbuf, 0x00000000);
	gdk_pixbuf_composite(sprites, newGdkPixbuf, 0, 0, width, height,- x_sprite_pos*width,- y_sprite_pos*height, 1, 1, GDK_INTERP_NEAREST, 255);

	return newGdkPixbuf;
}

void store_image_merge_pixbuf(GdkPixbuf *src, GdkPixbuf *dest, int dest_x, int dest_y)
{
	int width = gdk_pixbuf_get_width(src);
	int height = gdk_pixbuf_get_height(src);

	gdk_pixbuf_composite(src, dest, dest_x, dest_y, width, height, dest_x, dest_y, 1, 1, GDK_INTERP_NEAREST, 255);
}

int store_image_draw_path(cairo_t *cr, path *pathToDraw)
{
	if (pathToDraw == NULL)
		return EXIT_FAILURE;
	int i;
	double r = (rand() % 10) / 10.0;
	double v = (rand() % 10) / 10.0;
	double b = (rand() % 10) / 10.0;
	cairo_set_source_rgba(cr, r, v, b, 0.6);
	cairo_set_line_width(cr, 10);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
	cairo_move_to(cr, pathToDraw->coordinates->x*SPRITE_RES + SPRITE_RES / 2, pathToDraw->coordinates->y*SPRITE_RES + SPRITE_RES / 2);
	for (i = 1; i < pathToDraw->nb_coord; i++)
	{
		cairo_line_to(cr, (pathToDraw->coordinates + i)->x*SPRITE_RES + SPRITE_RES / 2, (pathToDraw->coordinates + i)->y*SPRITE_RES + SPRITE_RES / 2);
	}
	cairo_stroke(cr);
	return EXIT_SUCCESS;
}

int store_image_draw_shopping(cairo_t *cr, shopping *shopping)
{
	if (shopping == NULL)
		return EXIT_FAILURE;
	int i = 1;
	char number[MAX_ARRAY_OF_CHAR];
	itemList *list = shopping->List;

	itemPointerList_set_on_first(list);
	while (!itemPointerList_is_out_of(list))
	{
		store_image_draw_path(cr, item_get_pathTo(itemPointerList_get_current(list)));
		int x = itemPointerList_get_current(list)->posInSec.x + itemPointerList_get_current(list)->section->pos.x;
		int y = itemPointerList_get_current(list)->posInSec.y + itemPointerList_get_current(list)->section->pos.y;

		cairo_set_source_rgba(cr, 0.9, 0.1, 0.2, 1.0);
		cairo_arc(cr, (x+0.25)*SPRITE_RES, (y)*SPRITE_RES, 10, 0, 2 * M_PI);
		cairo_fill(cr);

		cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
		cairo_select_font_face(cr, "Georgia",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr, 15);
		cairo_move_to(cr, (x)*SPRITE_RES, (y+0.125)*SPRITE_RES);
		sprintf(number, "%d", i);
		cairo_show_text(cr, number);
		itemPointerList_next(list);
		i++;
	}
	store_image_draw_path(cr, item_get_pathTo(shopping->end));
}