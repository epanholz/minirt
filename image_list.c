/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 21:09:16 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/16 14:53:06 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	add_img(t_img_list **head, void *image, char *address)
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

void	create_images(t_minirt *minirt)
{
	int		i;
	void	*temp_img;
	char	*temp_addr;

	i = 0;
	while (i < minirt->scene.camera)
	{
		temp_img = mlx_new_image(minirt->var.mlx,
			minirt->scene.res_x, minirt->scene.res_y);
		temp_addr = mlx_get_data_addr(temp_img, &minirt->var.bits_per_pixel,
			&minirt->var.line_length, &minirt->var.endian);
		add_img(&minirt->var.i_head, temp_img, temp_addr);
		i++;
	}
}