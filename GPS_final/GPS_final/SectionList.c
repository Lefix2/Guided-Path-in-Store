/*!
* \file  sectionList.c
* \brief Defines new chained list structures
* \author GPS team
* \date 13/12/2014
*/

#include "sectionList.h"
#include "Section.h"
#include "ItemList.h"

/*!
* \fn nodesectionList * nodesectionPointerList_new(section *i, nodesectionList *n);
* \brief Create a new sectionList node
* \param[in] *i the section contained in the node
* \param[in] *n the parent nodesectionList
* \return the new allocated node
*/
nodeSectionList * nodeSectionPointerList_new(section * s, nodeSectionList *n)
{
	nodeSectionList * newn;
	newn = (nodeSectionList*)malloc(sizeof(nodeSectionList));

	newn->sectionPointerList_next = n;
	newn->s = s;

	return newn;
}

/*!
* \fn sectionList * sectionPointerList_new(void)
* \brief Create a new sectionPointerList
* \return the new allocated sectionList
*/
sectionList * sectionPointerList_new(void)
{
	sectionList * newl;
	newl = (sectionList *)malloc(sizeof(sectionList));
	sectionPointerList_init(newl);

	return newl;
}


/*!
* \fn int sectionPointerList_delete(sectionList * l)
* \brief Delete an sectionPointerList
* \param[in] *l pointer to the sectionList
* \return EXIT_SUCCES if OK
*/
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

/*!
* \fn void sectionPointerList_init(sectionList * l)
* \brief Initializes all sectionList parameters to NULL
* \param[in] *l the sectionList to initialize
*/
void sectionPointerList_init(sectionList * l)
{
	l->first = l->last = l->current = NULL;
}


/*!
* \fn int sectionPointerList_is_empty(sectionList * l)
* \brief Tells the user if the list is empty or not
* \param[in] *l the sectionList
* \return 1 if the list is empty, 0 otherwise
*/
int sectionPointerList_is_empty(sectionList * l)
{
	return l->first == NULL;
}

/*!
* \fn void sectionPointerList_is_on_first(sectionList * l)
* \brief Tells the user if the list current cursor is on the first section
* \param[in] *l the sectionList
* \return 1 if the list is on the first section, 0 otherwise
*/
int sectionPointerList_is_on_first(sectionList * l)
{
	return l->current == l->first;
}

/*!
* \fn void sectionPointerList_is_on_last(sectionList * l)
* \brief Tells the user if the list current cursor is on the last section
* \param[in] *l the sectionList
* \return 1 if the list is on the last section, 0 otherwise
*/
int sectionPointerList_is_on_last(sectionList * l)
{
	return l->current == l->last;
}

/*!
* \fn void sectionPointerList_is_out_of(sectionList * l)
* \brief Tells the user if the list current cursor is out of the list
* \param[in] *l the sectionList
* \return 1 if the list cursor is out of the list, 0 otherwise
*/
int sectionPointerList_is_out_of(sectionList * l)
{
	return l->current == NULL;
}


/*!
* \fn void sectionPointerList_set_on_first(sectionList * l)
* \brief Set the current cursor of the list on the first section
* \param[in] *l the sectionList
*/
void sectionPointerList_set_on_first(sectionList * l)
{
	l->current = l->first;
}


/*!
* \fn void sectionPointerList_set_on_last(sectionList * l)
* \brief Set the current cursor of the list on the last section
* \param[in] *l the sectionList
*/
void sectionPointerList_set_on_last(sectionList * l)
{
	l->current = l->last;
}


/*!
* \fn void sectionPointerList_next(sectionList * l)
* \brief Set the current cursor of the list on the next section
* \param[in] *l the sectionList
*/
void sectionPointerList_next(sectionList * l)
{
	l->current = l->current->sectionPointerList_next;
}


/*!
* \fn void sectionPointerList_print(sectionList * l, gboolean minimal)
* \brief Prints the content of the sectionPointerList
* \param[in] *l the sectionList
* \param[in] minimal prints the list in a minimal way if set at true
*/
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


/*!
* \fn int sectionPointerList_insert_first(sectionList * l, section * i)
* \brief Insert the section i at the beginning of in the sectionList l
* \param[in] *l the list the node is in
* \param[in] *i the section to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn int sectionPointerList_insert_last(sectionList * l, section * i)
* \brief Insert the section i at the end of the sectionList l
* \param[in] *l the list the node is in
* \param[in] *i the section to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn int sectionPointerList_insert_before_current(sectionList * l, section * i)
* \brief Insert the section i in the sectionList l just before the current cursor
* \param[in] *l the list the node is in
* \param[in] *i the section to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn int sectionPointerList_insert_after_current(sectionList * l, section * i)
* \brief Insert the section i in the sectionList l just after the current cursor
* \param[in] *l the list the node is in
* \param[in] *i the section to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn int sectionPointerList_insert_sort(sectionList * l, section * i)
* \brief Insert the section i in the sectionList l sorted by id
* \param[in] *l the list the node is in
* \param[in] *i the section to insert
* \return EXIT_SUCCES if OK EXIT_FAILURE otherwise
*/
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


/*!
* \fn section * sectionPointerList_delete_first(sectionList * l)
* \brief deletes the first section in the sectionList and free the memory
* \param[in] *l the sectionList
* \return the section deleted
*/
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


/*!
* \fn section * sectionPointerList_delete_last(sectionList * l)
* \brief deletes the last section in the sectionList and free the memory
* \param[in] *l the sectionList
* \return the section deleted
*/
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


/*!
* \fn section * sectionPointerList_delete_current(sectionList * l)
* \brief deletes the current section in the sectionList and free the memory
* \param[in] *l the sectionList
* \return the section deleted
*/
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


/*!
* \fn section * sectionPointerList_delete_single(sectionList * l, section * i)
* \brief deletes the section i in the sectionList and free the memory
* \param[in] *l the sectionList
* \param[in] *i the section
* \return the section deleted
*/
section * sectionPointerList_delete_single(sectionList * l, section * s)
{
	section * tmp = sectionPointerList_find(l, s);
	if(tmp != NULL)
		sectionPointerList_delete_current(l);
	return tmp;
}


/*!
* \fn section * sectionPointerList_get_current(sectionList * l)
* \brief Get the current section of the sectionList
* \param[in] *l the sectionList
* \return the current section of the sectionList
*/
section * sectionPointerList_get_current(sectionList * l)
{
	return l->current->s;
}


/*!
* \fn section * sectionPointerList_find(sectionList * l, section * i)
* \brief Get the section i of the sectionList
* \param[in] *l the sectionList
* \param[in] *i the section to search
* \return the section i if contained in the sectionList
*/
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


/*!
* \fn section * sectionPointerList_find(sectionList * l, int id)
* \brief Get the section with the id id of the sectionList
* \param[in] *l the sectionList
* \param[in] id the if of the section to search
* \return the section with the id id if contained in the sectionList
*/
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