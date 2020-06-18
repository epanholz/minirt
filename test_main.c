/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/10 20:04:00 by pani_zino     ########   odam.nl         */
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

int	main()
{
	t_minirt	minirt;
	int			fd;
	char		*buff;

	minirt.scene.res = 0;
	minirt.scene.a_light = 0;
	buff = NULL;
	fd = open("scene.rt", O_RDONLY);
	buff = read_file(fd, buff);
	check_map(buff, &minirt);

	// minirt.var.mlx = mlx_init();
	// minirt.var.win = mlx_new_window(minirt.var.mlx, minirt.scene.r1, minirt.scene.r2, "Scene Window");
	// mlx_string_put(minirt.var.mlx, minirt.var.win, 40, 40, 0xffd1f7, "Hi Angi! <3");
	// mlx_hook(minirt.var.win, 17, 0L, close_button, &minirt);
	// mlx_hook(minirt.var.win, 2, 1L<<0, close_key, &minirt);
	// mlx_loop(minirt.var.win);

	return (0);
}