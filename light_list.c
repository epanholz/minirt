/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:21:13 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:21:14 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	make_light_head(t_light_list **head)
{
	t_light_list *new_head;

	new_head = (t_light_list*)malloc(sizeof(t_light_list));
	if (new_head == NULL)
		ft_error(MALLOC);
	new_head->light_index = 0;
	new_head->light = NULL;
	new_head->next = NULL;
	*head = new_head;
}

void	add_light(t_light_list **head, t_light *light)
{
	static int		index;
	t_light_list	*newnode;
	t_light_list	*current;

	index++;
	current = *head;
	if (current->light == NULL)
		*current = (t_light_list){index, light, NULL};
	else
	{
		newnode = (t_light_list*)malloc(sizeof(t_light_list));
		if (newnode == NULL)
			ft_error(MALLOC);
		*newnode = (t_light_list){index, light, NULL};
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

void	delete_light_list(t_light_list **head)
{
	t_light_list *current;
	t_light_list *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}
