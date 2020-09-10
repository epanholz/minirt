/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 22:20:12 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/10 11:37:07 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		change_image(int keycode, t_minirt *minirt)
{
	static int 	index;
	t_img_list	*current;

	if (keycode == 53)
	{
		//mlx_destroy_image(minirt->var.mlx, minirt->var.img);
    	mlx_destroy_window(minirt->var.mlx , minirt->var.win);
		exit(0);
	}

	if (keycode == 124)
	{
		index++;
		current = minirt->var.i_head;
		while(current)
		{
			if (current->img_index == index)
				mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, current->img, 0, 0);
			current = current->next;
		}
	}
	if (index == minirt->scene.camera)
		index = 0;
	return (0);
}

int		close_key(int keycode, t_minirt *minirt)
{
	if (keycode == 53)
	{
		//mlx_destroy_image(minirt->var.mlx, minirt->var.img);
    	mlx_destroy_window(minirt->var.mlx , minirt->var.win);
		exit(0);
	}
	return (0);
}

int		close_button(void)
{
	exit(0);
	return (0);
}
