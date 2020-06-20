/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   circle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:32:11 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/20 17:25:53 by epanholz      ########   odam.nl         */
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
	int xc = 150;
	int yc = 150;
	int r = 100;
	int x = 0;
	int y = r; 
    int d = 3 - 2 * r; 

    var.mlx = mlx_init();
    var.win= mlx_new_window(var.mlx, 300, 300, "Ciiircleee!");
	mlx_key_hook(var.win, close_key, &var);
	mlx_hook(var.win, 17, 0L, close_button, &var);
	var.img = mlx_new_image(var.mlx, 300, 300);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length, &var.endian);
    my_mlx_pixel_put(&var, xc+x, yc+y, rgbt(0,255,182,193));
    my_mlx_pixel_put(&var, xc+x, yc-y, rgbt(0,255,182,193)); 
    my_mlx_pixel_put(&var, xc+y, yc+x, rgbt(0,255,182,193));
    my_mlx_pixel_put(&var, xc-y, yc-x, rgbt(0,255,182,193));
    while (y >= x) 
    { 
        x++; 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        my_mlx_pixel_put(&var, xc+x, yc+y, rgbt(0,255,182,193));
    	my_mlx_pixel_put(&var, xc-x, yc+y, rgbt(0,255,182,193));
    	my_mlx_pixel_put(&var, xc+x, yc-y, rgbt(0,255,182,193)); 
    	my_mlx_pixel_put(&var, xc-x, yc-y, rgbt(0,255,182,193));
    	my_mlx_pixel_put(&var, xc+y, yc+x, rgbt(0,255,182,193));
    	my_mlx_pixel_put(&var, xc-y, yc+x, rgbt(0,255,182,193));
    	my_mlx_pixel_put(&var, xc+y, yc-x, rgbt(0,255,182,193));
    	my_mlx_pixel_put(&var, xc-y, yc-x, rgbt(0,255,182,193));
    } 
	mlx_put_image_to_window(var.mlx, var.win, var.img, 0, 0);
    mlx_loop(var.mlx);
}    