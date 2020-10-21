/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:21:41 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/21 17:00:16 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	make_obj_head(t_object_list **head)
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

	current = *head;
	if (current->scene_object == NULL)
		*current = (t_object_list){type, scene, NULL};
	else
	{
		newnode = (t_object_list*)malloc(sizeof(t_object_list));
		if (newnode == NULL)
			ft_error(MALLOC);
		*newnode = (t_object_list){type, scene, NULL};
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

void	delete_object_list(t_object_list **head)
{
	t_object_list *current;
	t_object_list *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}
