/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 20:20:42 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/16 14:49:52 by pani_zino     ########   odam.nl         */
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
}

void	remove_object_node(t_object_list **head, int type)
{
	t_object_list *temp;
	t_object_list *prev;

	temp = *head;
	if (temp != NULL && temp->object_type == type)
	{
		*head = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && temp->object_type != type)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
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
