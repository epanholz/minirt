/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:50:17 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/16 14:50:48 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	delete_cam_list(t_camera_list **head)
{
	t_camera_list *current;
	t_camera_list *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
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

void	add_camera(t_camera_list **head, t_cam *cam)
{
	static int		index;
	t_camera_list	*newnode;
	t_camera_list	*current;

	index++;
	newnode = (t_camera_list*)malloc(sizeof(t_camera_list));
	if (newnode == NULL)
		ft_error(MALLOC);
	newnode->cam_index = index;
	newnode->cam = cam;
	newnode->next = NULL;
	current = *head;
	if (current->cam == NULL)
		*head = newnode;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

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
	newnode = (t_light_list*)malloc(sizeof(t_light_list));
	if (newnode == NULL)
		ft_error(MALLOC);
	newnode->light_index = index;
	newnode->light = light;
	newnode->next = NULL;
	current = *head;
	if (current->light == NULL)
		*head = newnode;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}
