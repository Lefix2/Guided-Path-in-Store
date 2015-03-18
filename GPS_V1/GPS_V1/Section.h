#ifndef SECTION_H
#define SECTION_H

#include "Common.h"
#include "Item.h"

section * newSection(int id, type s_type);
int addItemToSection(section s_source, item i_source);

#endif