/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 20:20:42 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/31 20:39:45 by pani_zino     ########   odam.nl         */
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

void	remove_object_node(t_object_list **head, int type)
{
	t_object_list *temp;
	t_object_list *prev;

	temp = *head;
	if (temp != NULL && temp->object_type == type)
	{
		*head = temp->next;
		//free(temp);
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
	//free(temp);
}

void delete_object_list(t_object_list **head)
{ 
   /* deref head_ref to get the real head */
   t_object_list* current = *head; 
   t_object_list* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       free(current); 
       current = next; 
   } 
    
   /* deref head_ref to affect the real head back 
      in the caller. */
   *head = NULL; 
}

void delete_cam_list(t_camera_list **head)
{ 
   /* deref head_ref to get the real head */
   t_camera_list* current = *head; 
   t_camera_list* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       free(current); 
       current = next; 
   } 
    
   /* deref head_ref to affect the real head back 
      in the caller. */
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