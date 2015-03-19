#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"

char* item_category[] = { "none", "fromage", "pain", "legumes vert" };

void Item_printHeader(boolean print_all)
{
	char* header[] = { "----------------------------------------------------------------------------",
					   "|     name     |      id      |   category   |     cost     |  section id  |"};
	int i;
	for (i = 0; i < 2; i++)
	{
		printf("%s\n", header[i]);
	}
	if (print_all)
		printf("%s\n", header[0]);
}

void Item_print(item * i_source)
{
	printf("| %12s | %12d | %12s | %11.2fE | %12d |\n", i_source->name, i_source->id, item_category[i_source->category],i_source->cost, i_source->i_section->id);
}