/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/20 20:31:14 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		intersect_sphere(t_ray *ray, t_minirt *minirt)
{
	t_sph		*sphere;
	t_vec3		dist;
	float		radius;	
	float		B;
	float		C;
	float		discr;

	sphere = return_sphere(minirt);
	radius = sphere->diameter / 2;
	float A = vectorDot(&ray->dir, &ray->dir); 
	dist = vectorSub(&ray->start, &sphere->sp_center);
	B = 2 * vectorDot(&ray->dir, &dist);
	C = vectorDot(&dist, &dist) - (radius * radius);
	discr = B * B - 4 * A * C;
	if	(discr < 0)
		return (-1);
	else
		return (discr);
		//cast shadow ray
}

void	make_scene(t_minirt *minirt)
{
	minirt->var.mlx = mlx_init();
	minirt->var.win = mlx_new_window(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y, "Scene Window");
	minirt->var.img = mlx_new_image(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y);
	minirt->var.addr = mlx_get_data_addr(minirt->var.img, &minirt->var.bits_per_pixel, &minirt->var.line_length, &minirt->var.endian);
	my_mlx_pixel_put(minirt, 500, 500, rgbt(0,255,182,193));
	mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, minirt->var.img, 0, 0);
	mlx_hook(minirt->var.win, 17, 0L, close_button, minirt);
	mlx_key_hook(minirt->var.win, close_key, minirt);
	mlx_loop(minirt->var.mlx);
}