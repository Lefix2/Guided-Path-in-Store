#ifndef SECTION_H
#define SECTION_H

#include "Common.h"



void testSect(void);
section * newSection(int id, type s_type);
section * Section_init(section * s_source);
int Section_isEmpty(section * s_source);

int Section_setId(section * s_source, int id);
int Section_setType(section * s_source, type s_type);
int Section_setPos(section * s_source, int x_pos, int y_pos);
int Section_setSize(section * s_source, int x_size, int y_size);

int Section_getId(section * s_source);
type Section_getType(section * s_source);
int Section_getXPos(section * s_source);
int Section_getYPos(section * s_source);
int Section_getXSize(section * s_source);
int Section_getYSize(section * s_source);
int Section_getNbItems(section * s_source);

int Section_addItem(section * s_source, item * i_source);
int Section_removeItem(item * i_source);

void Section_print(section * s_source);

#endif