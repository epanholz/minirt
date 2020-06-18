/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 16:08:35 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/18 17:32:39 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_var {
        void    *mlx;
        void    *win;
		void	*img;
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
	// var.img = mlx_new_image(var.mlx, 200, 200);
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

/* 
-- mlx_put_image_to_window -- 

Puts an image to the given window instance at location (x,y). This is the recommended way to write 
large amounts of graphical data in one go. Do mind that when changing the memory of the locations, 
it will be displayed directly on the window.

Puts an image to the given window.

@param  void *mlx_ptr the mlx instance;
@param  void *win_ptr the window instance;
@param  int  x        the x location of where the image ought to be placed;
@param  int  y        the y location of where the image ought to be placed;
@return int           has no return value (bc).
int     mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);

-- mlx_new_image -- 

Creates a new MLX compatible image. This is the recommended way to buffer the image you are rendering 
to be displayed. It will accept a pointer to your mlx instance and requires a width and height. Will 
return a reference pointer to the image.

Creates a new MLX compatible image.

@param  void *mlx_ptr the mlx instance pointer;
@param  int  width    the width of the image to be created;
@param  int  height   the height of the image to be created;
@return void *        the image instance reference.

void    *mlx_new_image(void *mlx_ptr,int width,int height);
*/