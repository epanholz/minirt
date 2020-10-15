/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:22:04 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/15 15:37:22 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rgbt(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	dst = minirt->mlx.addr + (y * minirt->mlx.line_length + x
		* (minirt->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_delay(void)
{
	int	c;
	int	d;

	c = 0;
	d = 0;
	while (c <= 238609293)
	{
		while (d <= 238609293)
			d++;
		c++;
	}
}
