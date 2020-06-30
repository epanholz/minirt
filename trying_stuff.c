/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trying_stuff.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/27 14:55:06 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/27 17:24:22 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_var {
        void    *mlx;
        void    *win;
		void	*img;
		char    *addr;
    	int     bits_per_pixel;
    	int     line_length;
    	int     endian;
}               t_var;


int		rgbt(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		close_key(int keycode, t_var *var)
{
	if (keycode == 53)
	{
    	mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_image(var->mlx, var->img);
		exit(0);
	}
	return (0);
}

int		close_button(t_var *var)
{
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_image(var->mlx, var->img);
	exit(0);
	return (0);
}

void            my_mlx_pixel_put(t_var *var, int x, int y, int color)
{
    char    *dst;

    dst = var->addr + (y * var->line_length + x * (var->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     main(void)
{
	t_var 	var;
	int image_width = 256;
	int image_height = 256;
	int r = 0;
	int g = 0;
	int b = 0;
	int x = 255;
	int y = 0;
	
    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, image_width, image_height, "teeest");
	mlx_key_hook(var.win, close_key, &var);
	mlx_hook(var.win, 17, 0L, close_button, &var);
	var.img = mlx_new_image(var.mlx, image_width, image_height);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length, &var.endian);

	while (x >= 0)
	{
		while (y < image_width)
		{
			if (r < 255)
				r++;
			my_mlx_pixel_put(&var, x, y, rgbt(0,r,g,b));
			y++;
		}
		y = 0;
		r = 0;
		x--;
	}
	mlx_put_image_to_window(var.mlx, var.win, var.img, 0, 0);
    mlx_loop(var.mlx);
}    	