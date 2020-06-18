/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   circle.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 17:32:11 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/05 17:11:02 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_var {
        void    *mlx;
        void    *win;
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
		exit(1);
	}
	return (0);
}

int		close_button(void)
{
	exit(1);
	return (0);
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
    var.win= mlx_new_window(var.mlx, 300, 300, "Hey Panini!");
    mlx_pixel_put(var.mlx, var.win, xc+x, yc+y, 0xffd1f7);;
    mlx_pixel_put(var.mlx, var.win, xc+x, yc-y, 0xffd1f7); 
    mlx_pixel_put(var.mlx, var.win, xc+y, yc+x, 0xffd1f7);
    mlx_pixel_put(var.mlx, var.win, xc-y, yc-x, 0xffd1f7);
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
        mlx_pixel_put(var.mlx, var.win, xc+x, yc+y, 0xffd1f7);
    	mlx_pixel_put(var.mlx, var.win, xc-x, yc+y, 0xffd1f7);
    	mlx_pixel_put(var.mlx, var.win, xc+x, yc-y, 0xffd1f7); 
    	mlx_pixel_put(var.mlx, var.win, xc-x, yc-y, 0xffd1f7);
    	mlx_pixel_put(var.mlx, var.win, xc+y, yc+x, 0xffd1f7);
    	mlx_pixel_put(var.mlx, var.win, xc-y, yc+x, 0xffd1f7);
    	mlx_pixel_put(var.mlx, var.win, xc+y, yc-x, 0xffd1f7);
    	mlx_pixel_put(var.mlx, var.win, xc-y, yc-x, 0xffd1f7);
    } 
	mlx_hook(var.win, 17, 0L, close_button, &var);
	mlx_hook(var.win, 2, 1L<<0, close_key, &var);
    mlx_loop(var.mlx);
}    