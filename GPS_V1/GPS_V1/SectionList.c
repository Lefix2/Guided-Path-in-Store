#include "sectionList.h"
#include "Section.h"
#include "ItemList.h"

nodeSectionList * nodeSectionPointerList_new(section * s, nodeSectionList *n)
{
	nodeSectionList * newn;
	newn = (nodeSectionList*)malloc(sizeof(nodeSectionList));

	newn->sectionPointerList_next = n;
	newn->s = s;

	return newn;
}

sectionList * sectionPointerList_new(void)
{
	sectionList * newl;
	newl = (sectionList *)malloc(sizeof(sectionList));
	sectionPointerList_init(newl);

	return newl;
}

int sectionPointerList_delete(sectionList * l)
{
	if (l == NULL)
		return EXIT_FAILURE;
	while (!sectionPointerList_is_empty(l))
	{
		sectionPointerList_delete_first(l);
	}
	free(l);
	return EXIT_SUCCESS;
}

void sectionPointerList_init(sectionList * l)
{
	l->first = l->last = l->current = NULL;
}

int sectionPointerList_is_empty(sectionList * l)
{
	return l->first == NULL;
}

int sectionPointerList_is_on_first(sectionList * l)
{
	return l->current == l->first;
}

int sectionPointerList_is_on_last(sectionList * l)
{
	return l->current == l->last;
}

int sectionPointerList_is_out_of(sectionList * l)
{
	return l->current == NULL;
}

void sectionPointerList_set_on_first(sectionList * l)
{
	l->current = l->first;
}

void sectionPointerList_set_on_last(sectionList * l)
{
	l->current = l->last;
}

void sectionPointerList_next(sectionList * l)
{
	l->current = l->current->sectionPointerList_next;
}

void sectionPointerList_print(sectionList * l)
{
	char* header[] = { ".--------------------------------------------------------------------------.",
					   "|  id  |      type      | items in stock |     size x     |     size y     |" };
	int i;
	section * tmp;

	if (sectionPointerList_is_empty(l)){
		printf("empty section\n");
	}
	else{
		printf("\n");
		sectionPointerList_set_on_first(l);

		for (i = 0; i < 2; i++)
		{
			printf("%s\n", header[i]);
		}
		printf("%s\n", header[0]);

		while (!sectionPointerList_is_out_of(l))
		{
			tmp = l->current->s;
			printf("| %4d | %14s | %14d | %14d | %14d |\n",section_get_id(tmp),
														   section_get_type_string(tmp),
														   section_get_nb_items(tmp),
														   section_get_size(tmp).x,
														   section_get_size(tmp).y
			);
			if (tmp->s_type == t_section)
				itemPointerList_print(tmp->stock, TRUE);
			printf("%s\n", header[0]);
			sectionPointerList_next(l);
		}
		printf("\n");
	}

}

int sectionPointerList_insert_first(sectionList * l, section * s)
{
	nodeSectionList* n = nodeSectionPointerList_new(s, l->first);
	if (n == NULL)
		return EXIT_FAILURE;

	if (sectionPointerList_is_empty(l))
	{
		l->last = l->current = n;
	}
	l->first = n;
	return EXIT_SUCCESS;
}

int sectionPointerList_insert_last(sectionList * l, section * s)
{
	nodeSectionList* n = nodeSectionPointerList_new(s, NULL);
	if (n == NULL)
		return EXIT_FAILURE;

	if (sectionPointerList_is_empty(l))
	{
		l->first = l->current = n;
	}
	else
		l->last->sectionPointerList_next = n;
	l->last = n;
	return EXIT_SUCCESS;
}

int sectionPointerList_insert_before_current(sectionList * l, section * s)
{
	if (sectionPointerList_is_empty(l) || sectionPointerList_is_on_first(l))
	{
		return sectionPointerList_insert_first(l, s);
	}
	else if (sectionPointerList_is_out_of(l))
	{
		printf("error: trying to write out of th sectionlist!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeSectionList* n = nodeSectionPointerList_new(s, l->current);
		nodeSectionList* tmp = l->current;
		sectionPointerList_set_on_first(l);
		while (l->current->sectionPointerList_next != tmp)
		{
			sectionPointerList_next(l);
		}
		l->current->sectionPointerList_next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int sectionPointerList_insert_after_current(sectionList * l, section * s)
{

	if (sectionPointerList_is_empty(l))
	{
		return sectionPointerList_insert_first(l, s);
	}
	else if (sectionPointerList_is_out_of(l))
	{
		printf("error: trying to write out of the sectionList!");
		return EXIT_FAILURE;
	}
	else
	{
		nodeSectionList* n = nodeSectionPointerList_new(s, l->current->sectionPointerList_next);
		l->current->sectionPointerList_next = n;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int sectionPointerList_insert_sort(sectionList * l, section * s)
{
	nodeSectionList * tmp = l->current;
	if (sectionPointerList_is_empty(l))
	{
		return sectionPointerList_insert_first(l, s);
	}

	sectionPointerList_set_on_first(l);

	do
	{
		if (l->current->s->id <= s->id)
			sectionPointerList_next(l);
		else
		{
			sectionPointerList_insert_before_current(l, s);
			sectionPointerList_set_on_first(l);
			break;
		}
	} while (!sectionPointerList_is_out_of(l));
	if (sectionPointerList_is_out_of(l))
		sectionPointerList_insert_last(l, s);

	l->current = tmp;
	return EXIT_SUCCESS;
}

section * sectionPointerList_delete_first(sectionList * l)
{
	if (sectionPointerList_is_empty(l)){
		printf("error: trying to delete node in an sectionPointerList_is_empty sectionList in %s\n", __FUNCTION__);
		return NULL;
	}

	else{
		nodeSectionList * n = l->first;
		section * ret = n->s;
		l->first = n->sectionPointerList_next;
		if (l->first == NULL)
			sectionPointerList_init(l);
		sectionPointerList_set_on_first(l);
		free((void*)n);
		return ret;
	}
	return NULL;
}

section * sectionPointerList_delete_last(sectionList * l)
{
	if (sectionPointerList_is_empty(l)){						//no node
		printf("error: trying to delete node in an empty sectionList in %s\n", __FUNCTION__);
		return NULL;
	}
	else if (l->first == l->last)		//only one node
	{
		return sectionPointerList_delete_first(l);
	}
	else{											//at least 2 nodes
		nodeSectionList* n = l->last;
		section * ret = n->s;
		sectionPointerList_set_on_first(l);
		while (l->current->sectionPointerList_next != n)
		{
			sectionPointerList_next(l);
		}
		l->last = l->current;
		l->last->sectionPointerList_next = NULL;
		free((void*)n);
		return ret;
	}
	return NULL;
}

section * sectionPointerList_delete_current(sectionList * l)
{
	if (sectionPointerList_is_empty(l)){
		printf("error: trying to delete node in an empty sectionList in %s\n", __FUNCTION__);
		return NULL;
	}
	if (sectionPointerList_is_on_first(l))
	{
		return sectionPointerList_delete_first(l);
	}
	else if (sectionPointerList_is_on_last(l))
	{
		return sectionPointerList_delete_last(l);
	}
	else
	{
		nodeSectionList* n = l->current;
		section * ret = n->s;
		sectionPointerList_set_on_first(l);
		while (l->current->sectionPointerList_next != n)
		{
			sectionPointerList_next(l);
		}
		l->current->sectionPointerList_next = n->sectionPointerList_next;

		free((void*)n);
		return ret;
	}
	return NULL;
}

section * sectionPointerList_delete_single(sectionList * l, section * s)
{
	section * tmp = sectionPointerList_find(l, s);
	if(tmp != NULL)
		sectionPointerList_delete_current(l);
	return tmp;
}

section * getcurrent(sectionList * l)
{
	return l->current->s;
}

section * sectionPointerList_find(sectionList * l, section * s)
{
	sectionPointerList_set_on_first(l);
	while (l->current != NULL)
	{
		if (l->current->s == s)
			return l->current->s;
		sectionPointerList_next(l);
	}
	return NULL;
}

section * sectionPointerList_find_id(sectionList * l, int id)
{
	sectionPointerList_set_on_first(l);
	while (l->current != NULL)
	{
		if (l->current->s->id == id)
			return l->current->s;
		sectionPointerList_next(l);
	}
	return NULL;
}