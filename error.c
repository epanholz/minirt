/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:16 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/21 15:55:38 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_error(int mod)
{
	if (mod == INVAL)
		write(1, "\033[1;38;5;168m\nError\nInvalid map!\n\n\033[0m", 39);
	if (mod == MALLOC)
		write(1, "\033[1;38;5;168m\nError\nMalloc failed!\n\n\033[0m", 41);
	if (mod == READ)
		write(1, "\033[1;38;5;168m\nError\nRead failed!\n\n\033[0m", 39);
	if (mod == WRITE)
		write(1, "\033[1;38;5;168m\nError\nBitmap write failed!\n\n\033[0m", 47);
	if (mod == OPEN)
		write(1, "\033[1;38;5;168m\nError\nOpen failed!\n\n\033[0m", 39);
	if (mod == RT)
		write(1, "\033[1;38;5;168m\nError\nThat's not an .rt file!\n\n\033[0m", 50);
	if (mod == ARG)
		write(1, "\033[1;38;5;168m\nError\nWrong second argument!\n\n\033[0m", 49);
	if (mod == INPUT)
		write(1, "\033[1;38;5;168m\nError\nWrong input!\n\n\033[0m", 39);
	exit(1);
}
