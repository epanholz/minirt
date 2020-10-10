/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:16 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:20:18 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_error(int mod)
{
	if (mod == INVAL)
		write(1, "\nError\nInvalid map!\n\n", 22);
	if (mod == MALLOC)
		write(1, "\nError\nMalloc failed!\n\n", 24);
	if (mod == READ)
		write(1, "\nError\nRead failed!\n\n", 22);
	if (mod == WRITE)
		write(1, "\nError\nBitmap write failed!\n\n", 30);
	if (mod == OPEN)
		write(1, "\nError\nOpen failed!\n\n", 22);
	if (mod == RT)
		write(1, "\nError\nThat's not an .rt file!\n\n", 33);
	if (mod == ARG)
		write(1, "\nError\nWrong second argument!\n\n", 32);
	if (mod == INPUT)
		write(1, "\nError\nWrong input!\n\n", 22);
	exit(1);
}
