/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 17:45:39 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/29 21:33:02 by epanholz      ########   odam.nl         */
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

int		print_key(int keycode, t_var *var)
{
	if (keycode == 53)
	{
    	mlx_destroy_window(var->mlx, var->win);
		exit(1);
	}
	printf("KEY: %d\n", keycode);
	return (0);
}

int		print_mouse_klick(int x, int y, int z)
{
	printf("MOUSE: %d,%d,%d\n", x, y, z);
	return(0);
}

int		print_mouse_pos(int x, int y)
{
	printf("MOUSE: %d,%d\n", x, y);
	return(0);
}

int		print_mouse(int x, int y, t_var *var)
{
	mlx_pixel_put(var->mlx, var->win, x, y, rgbt(0,255,182,193));
	return(0);
}

int 	enter_window(void)
{
	printf("Hi!\n");
	return (0);
}

int 	leave_window(void)
{
	printf("Bye!\n");
	return (0);
}

int     main(void)
{
	t_var 	var;

    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, 640, 480, "Hey Panini!");
	mlx_hook(var.win, 17, 0L, close_button, &var);
	// mlx_hook(var.win, 2, 1L<<0, close_key, &var);
	//mlx_hook(var.win, 4, 1L<<2, print_mouse_klick, &var);
	mlx_hook(var.win, 2, 1L<<0, print_key, &var);
	//mlx_hook(var.win, 6, 0L, print_mouse_pos, &var);
    mlx_loop(var.mlx);
}    	