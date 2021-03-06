/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:35 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/21 17:00:39 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_image(t_minirt *minirt)
{
	static int	index;
	t_img_list	*current;

	current = minirt->list.i_head;
	if (index == (minirt->scene.camera + 1))
		index = 1;
	if (index == 0)
	{
		if (current->next)
		{
			current = current->next;
			mlx_put_image_to_window(minirt->mlx.mlx, minirt->mlx.win,
				current->img, 0, 0);
			index = 3;
			return ;
		}
	}
	while (current)
	{
		if (current->img_index == index)
			mlx_put_image_to_window(minirt->mlx.mlx, minirt->mlx.win,
				current->img, 0, 0);
		current = current->next;
	}
	index++;
}

int		key_hook(int keycode, t_minirt *minirt)
{
	t_img_list *current;
	t_img_list *next;

	if (keycode == 53)
	{
		current = minirt->list.i_head;
		while (current != NULL)
		{
			next = current->next;
			mlx_destroy_image(minirt->mlx.mlx, current->img);
			current = next;
		}
		mlx_destroy_window(minirt->mlx.mlx, minirt->mlx.win);
		exit(0);
	}
	if (keycode == 124)
		change_image(minirt);
	return (0);
}

int		close_button(t_minirt *minirt)
{
	t_img_list *current;
	t_img_list *next;

	current = minirt->list.i_head;
	while (current != NULL)
	{
		next = current->next;
		mlx_destroy_image(minirt->mlx.mlx, current->img);
		current = next;
	}
	mlx_destroy_window(minirt->mlx.mlx, minirt->mlx.win);
	exit(0);
	return (0);
}
