/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 16:08:35 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/05 17:00:29 by pani_zino     ########   odam.nl         */
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
	int 	i;
	int 	j;

	i = 50;
	j = 150;
    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, 200, 200, "Hey Zino!");
	while (i < 150 && j > 50)
	{
		mlx_pixel_put(var.mlx, var.win, 50, i, rgbt(0,255,182,193));
		mlx_pixel_put(var.mlx, var.win, i, 50, rgbt(0,255,182,193));
		mlx_pixel_put(var.mlx, var.win, 150, j, rgbt(0,255,182,193));
		mlx_pixel_put(var.mlx, var.win, j, 150, rgbt(0,255,182,193));
		i++;
		j--;
	}
	mlx_string_put(var.mlx, var.win, 40, 40, 0xffd1f7, "LOOK ZINO");
	mlx_hook(var.win, 17, 0L, close_button, &var);
	mlx_hook(var.win, 2, 1L<<0, close_key, &var);
    mlx_loop(var.mlx);
}    	