#include <math.h>

#include "StoreImage.h"
#include "Section.h"
#include "SectionList.h"
#include "Store.h"

typedef enum spriteOrientation{
	middle, topLeftCorner, topRightCorner, botRightCorner, botLeftCorner, top, right, bot, left, singleVert, singleHor, singleUp, singleRight, singleDown, singleLeft
}spriteOrientation;

GdkPixbuf *store_image_new_pixbuf_from_store(store *src, GdkPixbuf *sprites)
{/*
	int x, y;

	int width = store_get_x_size(src);
	int height = store_get_y_size(src);

	GdkPixbuf *newGdkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, gdk_pixbuf_get_bits_per_sample(sprites), width * SPRITE_RES, height * SPRITE_RES);

	GdkPixbuf *floor;
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
	sectionPointerList_set_on_first(sections);
	GdkPixbuf *currentSectionPixbuf;
	while (!sectionPointerList_is_out_of(sections))
	{
		currentSection = getcurrent(sections);

		x = Section_getXPos(currentSection);
		y = Section_getYPos(currentSection);

		currentSectionPixbuf = store_image_new_pixbuf_from_section(currentSection, sprites);
		store_image_merge_pixbuf(currentSectionPixbuf, newGdkPixbuf, x*SPRITE_RES, y*SPRITE_RES);
		sectionPointerList_next(sections);
	}

	return newGdkPixbuf;*/
}

GdkPixbuf *store_image_new_pixbuf_from_section(section *src, GdkPixbuf *sprites)
{
	int x, y;
	int width = Section_getXSize(src);
	int height = Section_getYSize(src);

	guint32 color;

	GdkPixbuf *newGdkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, gdk_pixbuf_get_bits_per_sample(sprites), width * SPRITE_RES, height * SPRITE_RES);
	gdk_pixbuf_fill(newGdkPixbuf, 0x00000000);
	GdkPixbuf *actualSprite;

	spriteOrientation actualSpriteOrientation;
	type actualSpriteType = Section_getType(src);
	
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