/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/03 12:41:39 by epanholz      ########   odam.nl         */
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

void            my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
    char    *dst;

    dst = minirt->var.addr + (y * minirt->var.line_length + x * (minirt->var.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


int	main()
{
	t_minirt	minirt;
	int			fd;
	char		*buff;
	// t_vec3 		vec;
	// t_vec3 		norm_vec;

	minirt.scene.res = 0;
	minirt.scene.ambient_light = 0;
	minirt.scene.camera = 0;

	// vec.x = 3;
	// vec.y = -4;
	// vec.z = 0;
	// norm_vec = vec_normalize(&vec, sqrt(vectorDot(&vec, &vec)));
	// printf("norm vec %0.1f %0.1f %0.1f\n", norm_vec.x, norm_vec.y, norm_vec.z);

	buff = NULL;
	fd = open("scene.rt", O_RDONLY);
	buff = read_file(fd, buff);
	check_map(buff, &minirt);

	minirt.var.mlx = mlx_init();
	minirt.var.win = mlx_new_window(minirt.var.mlx, minirt.scene.res_x, minirt.scene.res_y, "Scene Window");
	minirt.var.img = mlx_new_image(minirt.var.mlx, minirt.scene.res_x, minirt.scene.res_y);
	minirt.var.addr = mlx_get_data_addr(minirt.var.img, &minirt.var.bits_per_pixel, &minirt.var.line_length, &minirt.var.endian);
	my_mlx_pixel_put(&minirt, 500, 500, rgbt(0,255,182,193));
	mlx_put_image_to_window(minirt.var.mlx, minirt.var.win, minirt.var.img, 0, 0);
	mlx_hook(minirt.var.win, 17, 0L, close_button, &minirt);
	mlx_key_hook(minirt.var.win, close_key, &minirt);
	mlx_loop(minirt.var.mlx);

 // gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit test_main.c read_file.c get_scene.c check_scene_utils.c object_list.c check_scene.c

	return (0);
}