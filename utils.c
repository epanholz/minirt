/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 17:31:42 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/15 20:58:21 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		close_key(int keycode, t_minirt *minirt)
{
	if (keycode == 53)
	{
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

int		rgbt(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
    char    *dst;

    dst = minirt->var.addr + (y * minirt->var.line_length + x * (minirt->var.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// int		close_key(int keycode, t_minirt *minirt)
// {
// // FOR THE IMAGE CHANGE
// //KEY: 123
// //KEY: 124
// }
