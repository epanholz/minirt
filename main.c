/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 18:51:27 by epanholz       #+#    #+#                */
/*   Updated: 2020/03/05 18:57:18 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

check map -> make struct 
proper scene file check? is it needed
check how to work with image

struct

identifier : square / plane/ cylinder
values : float x, float y, float z
next *

 */

#include "minirt.h"

int		ft_close(int keycode, t_minirt *minirt)
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

int		check_save(char *str)
{
	const char cmp[] = "--save";
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != cmp[i])
			return(1);
		i++;
	}
	if (i <= 5)
		return(1);
	return(0);
}

int	main(int ac, char **av)
{
	t_minirt	minirt;
	int			fd;
	char		*buff;


	minirt.scene.r1 = 0;
	minirt.scene.r2 = 0;
	minirt.scene.res = 0;

	buff = NULL;
	if (ac == 3)
	{
		if (check_save(av[2]) == 0)
			printf("save\n");
		else
			printf("Error\nWrong second argument!\n");
		return(0);
	}
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error\nInvalid File!\n");
			return (0);
		}
		buff = read_file(fd, buff);
		check_map(buff, &minirt);
		// minirt.var.mlx = mlx_init();
		// minirt.var.win = mlx_new_window(minirt.var.mlx, minirt.scene.r1, minirt.scene.r2, "Hey Panini!");
		// mlx_hook(minirt.var.win, 2, 1L<<0, ft_close, &minirt);
		// mlx_hook(minirt.var.win, 17, 0L, close_button, &minirt);
		// mlx_loop(minirt.var.mlx);
	}
	if (ac == 1)
		printf("Error\nPlease enter a valid map file!");
	return (0);
}