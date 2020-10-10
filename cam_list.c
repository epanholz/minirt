/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cam_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:19:55 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:19:57 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	delete_cam_list(t_camera_list **head)
{
	t_camera_list *new;
	t_camera_list *temp;

	new = *head;
	while (new != NULL)
	{
		temp = new;
		new = new->next;
		free(temp);
	}
	*head = NULL;
}

void	make_cam_head(t_camera_list **head)
{
	t_camera_list *new_head;

	new_head = (t_camera_list*)malloc(sizeof(t_camera_list));
	if (new_head == NULL)
		ft_error(MALLOC);
	new_head->cam_index = 0;
	new_head->cam = NULL;
	new_head->next = NULL;
	*head = new_head;
}

void	add_cam(t_camera_list **head, t_cam *cam)
{
	static int		index;
	t_camera_list	*newnode;
	t_camera_list	*current;

	index++;
	current = *head;
	if (current->cam == NULL)
		*current = (t_camera_list){index, cam, NULL};
	else
	{
		newnode = (t_camera_list*)malloc(sizeof(t_camera_list));
		if (newnode == NULL)
			ft_error(MALLOC);
		*newnode = (t_camera_list){index, cam, NULL};
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

t_cam	*return_cam(t_minirt *minirt, int index)
{
	t_cam			*cam;
	t_camera_list	*current;

	current = minirt->list.c_head;
	while (current)
	{
		if (current->cam_index == index)
		{
			cam = current->cam;
			return (cam);
		}
		current = current->next;
	}
	return (NULL);
}
