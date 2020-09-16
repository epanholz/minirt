/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 17:31:42 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/16 14:55:54 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_error(int mod)
{
	if (mod == INVAL)
		write(1, "Error\nInvalid map!", 19);
	if (mod == MALLOC)
		write(1, "Error\nMalloc failed!", 21);
	if (mod == READ)
		write(1, "Error\nRead failed!", 19);
	exit(1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return ((void *)b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = malloc(count * size);
	if (new)
		ft_bzero(new, count * size);
	return (new);
}

int		rgbt(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	dst = minirt->var.addr + (y * minirt->var.line_length + x
		* (minirt->var.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
