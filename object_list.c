/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 20:20:42 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/10 20:08:52 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Need to keep track of where your list starts. 
// HEAD 
// check if there is a node, else iterate through it, until you find an empty -> next
// Then keep adding nodes to list. 
// add objects to your list, and make sure to specify them.
// dont use the head when iterate through the list

void	make_head(t_object_list **head)
{
	t_object_list *new_head;

	new_head = (t_object_list*)malloc(sizeof(t_object_list));
	if (new_head == NULL)
		ft_error(MALLOC);
	new_head->object_type = 0;
	new_head->scene_object = NULL;
	new_head->next = NULL;
	*head = new_head;
}

void	add_object(t_object_list **head, int type, void *scene)
{
	t_object_list	*newnode;
	t_object_list	*current;

	newnode = (t_object_list*)malloc(sizeof(t_object_list));
	if (newnode == NULL)
		ft_error(MALLOC);
	newnode->object_type = type;
	newnode->scene_object = scene;
	newnode->next = NULL;
	current = *head;
	if (current->scene_object == NULL)
		*head = newnode;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
	printf("[OBJ TYPE: %d]\n", newnode->object_type);
}




