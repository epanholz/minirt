/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/07 19:23:08 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// int		rgbt(int t, int r, int g, int b)
// {
// 	return(t << 24 | r << 16 | g << 8 | b);
// }

// void            my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
// {
//     char    *dst;

//     dst = minirt->var.addr + (y * minirt->var.line_length + x * (minirt->var.bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

int	main(int ac, char **av)
{
	t_minirt	*minirt;
	int			fd;
	char		*buff;

	minirt = (t_minirt*)malloc(sizeof(t_minirt));
	minirt->scene.res = 0;
	minirt->scene.save = 0;
	minirt->scene.ambient_light = 0;
	minirt->scene.camera = 0;
	minirt->var.c_head = NULL;
	minirt->var.o_head = NULL;
	minirt->var.i_head = NULL;
	minirt->var.l_head = NULL;
	buff = NULL;
	
	if (ac == 3 || ac == 2)
	{
		if (ac == 3)
		{
			if (check_save(av[2]) == 1)
			{
				printf("Error\nWrong second argument!\n");
				return (0);
			}
			minirt->scene.save = 1;
			printf("\nsaving ..\n\n");
		}
		fd = open(av[1], O_RDONLY);
		buff = read_file(fd, buff);
		check_map(buff, minirt);
		free(minirt);
		free(buff);
	}
	else 
		printf("\nError\nWrong input duh ..\n\n");

	// minirt->var.mlx = mlx_init();
	// minirt->var.win = mlx_new_window(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y, "Scene Window");
	// minirt->var.img = mlx_new_image(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y);
	// minirt->var.addr = mlx_get_data_addr(minirt->var.img, &minirt->var.bits_per_pixel, &minirt->var.line_length, &minirt->var.endian);
	// my_mlx_pixel_put(minirt, 500, 500, rgbt(0,255,182,193));
	// mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, minirt->var.img, 0, 0);
	// mlx_hook(minirt->var.win, 17, 0L, close_button, minirt);
	// mlx_key_hook(minirt->var.win, close_key, minirt);
	// mlx_loop(minirt->var.mlx);

 	// gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit test_main.c read_file.c get_scene.c check_scene_utils.c object_list.c check_scene.c

	return (0);
}