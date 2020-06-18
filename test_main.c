/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/18 16:58:40 by epanholz      ########   odam.nl         */
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

int		rgbt(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int	main()
{
	t_minirt	minirt;
	int			fd;
	char		*buff;

	minirt.scene.res = 0;
	minirt.scene.ambient_light = 0;
	minirt.scene.camera = 0;

	buff = NULL;
	fd = open("scene.rt", O_RDONLY);
	buff = read_file(fd, buff);
	check_map(buff, &minirt);

	// minirt.var.mlx = mlx_init();
	// minirt.var.win = mlx_new_window(minirt.var.mlx, minirt.scene.res_x, minirt.scene.res_y, "Scene Window");
	// mlx_string_put(minirt.var.mlx, minirt.var.win, 200, 250, rgbt(0, minirt.scene.l_r, minirt.scene.l_g, minirt.scene.l_b), "A LIGHT COLOR");
	// mlx_hook(minirt.var.win, 17, 0L, close_button, &minirt);
	// mlx_hook(minirt.var.win, 2, 1L<<0, close_key, &minirt);
	// mlx_loop(minirt.var.mlx);

 // gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit test_main.c read_file.c get_scene.c check_scene_utils.c object_list.c check_scene.c

	return (0);
}