/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cam_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 15:42:27 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/21 15:45:32 by pani_zino     ########   odam.nl         */
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

	current = minirt->var.c_head;
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
