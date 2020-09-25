/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 21:09:16 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/25 13:41:33 by pani_zino     ########   odam.nl         */
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
	current = *head;
	if (current->img == NULL)
		*current = (t_img_list){index, image, address, NULL};
	else
	{
		newnode = (t_img_list*)malloc(sizeof(t_img_list));
		if (newnode == NULL)
			ft_error(MALLOC);
		*newnode = (t_img_list){index, image, address, NULL};
		while (current->next != NULL)
			current = current->next;
		current->next = newnode;
	}
}

void	delete_img_list(t_img_list **head)
{
	t_img_list *current;
	t_img_list *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void	create_images(t_minirt *minirt)
{
	int		i;
	void	*temp_img;
	char	*temp_addr;

	i = 0;
	while (i < minirt->scene.camera)
	{
		temp_img = mlx_new_image(minirt->mlx.mlx,
			minirt->scene.res_x, minirt->scene.res_y);
		temp_addr = mlx_get_data_addr(temp_img, &minirt->mlx.bits_per_pixel,
			&minirt->mlx.line_length, &minirt->mlx.endian);
		add_img(&minirt->list.i_head, temp_img, temp_addr);
		i++;
	}
}
