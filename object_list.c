/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 20:20:42 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/15 20:31:26 by epanholz      ########   odam.nl         */
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

void	make_img_head(t_img_list **head)
{
	t_img_list *new_head;

	new_head = (t_img_list*)malloc(sizeof(t_img_list));
	if (new_head == NULL)
		ft_error(MALLOC);
	new_head->img_index = 0;
	new_head->img = NULL;
	new_head->addr = NULL;
	new_head->next = NULL;
	*head = new_head;
}

void	add_img(t_img_list **head, void	*image, char *address)
{
	static int		index;
	t_img_list		*newnode;
	t_img_list		*current;

	index++;
	newnode = (t_img_list*)malloc(sizeof(t_img_list));
	if (newnode == NULL)
		ft_error(MALLOC);
	newnode->img_index = index;
	newnode->img = image;
	newnode->addr = address;
	newnode->next = NULL;
	current = *head;
	if (current->img == NULL)
		*head = newnode;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}