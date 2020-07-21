/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/21 22:37:01 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix43	*make_matrix(t_cam *cam)
{
	t_matrix43	*cam2world;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;
	t_vec3		temp;

	cam2world = (t_matrix43*)malloc(sizeof(t_matrix43));
	temp = vec3(0,1,0);
	forward = vectorSub(&cam->view_point, &cam->norm_vec);
	forward = vec_normalize(&forward);
	right = crossProduct(&temp, &forward);
	up = crossProduct(&forward, &right);

	cam2world->row1 = right;
	cam2world->row2 = up;
	cam2world->row3 = forward;
	cam2world->row4 = vec3(0,0,0);

	return(cam2world);
}

t_vec3	setcam(t_vec3 from, t_cam *cam)
{
	t_vec3 		new;
	t_matrix43	*c2w;

	// if (dest->cam_vals.norm_vec.x == 0 && dest->cam_vals.norm_vec.y == 0 && dest->cam_vals.norm_vec.z == 0 )
	// 	return(from);
	c2w = make_matrix(cam);
	new.x = from.x * c2w->row1.x + from.y * c2w->row2.x + from.z * c2w->row3.x;
	new.y = from.x * c2w->row1.y + from.y * c2w->row2.y + from.z * c2w->row3.y;
	new.z = from.x * c2w->row1.z + from.y * c2w->row2.z + from.z * c2w->row3.z;
	return (new);
}

int		intersect_sphere(t_ray *ray, t_minirt *minirt)
{
	t_sph		*sphere;
	t_vec3		dist;
	float		diameter;
	float		radius;	
	float		B;
	float		C;
	float		discr;

	sphere = (t_sph*)malloc(sizeof(t_sph));
	sphere = return_sphere(minirt);
	printf("test %f \n", sphere->diameter);
	diameter = sphere->diameter;
	radius = diameter / 2;
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

void	generate_ray(t_minirt *minirt)
{
	t_cam		*cam;
	t_vec3		dir;
	t_ray		*ray;
	float		aspect_ratio;
	int			pixely;
	int 		pixelx;
	float		camy;
	float		camx;

	ray = (t_ray*)malloc(sizeof(t_ray));
	aspect_ratio = minirt->scene.res_x / minirt->scene.res_y;
	pixelx = 0;
	pixely = 0;
	camy = 0;
	camx = 0;
	cam = return_cam(minirt, 1);
	ray->start = cam->view_point;
	while (pixely <= minirt->scene.res_y)
	{
		//transform camy
		camy = (1 - 2 * ((pixely + 0.5) / minirt->scene.res_y)) * tan(cam->fov / 2 * M_PI / 180);
		while(pixelx <= minirt->scene.res_x)
		{
			//transform camx
			camx = (2 * ((pixelx + 0.5) / minirt->scene.res_x) - 1) * tan(cam->fov / 2 * M_PI / 180) * aspect_ratio;
			dir = vec3(camx, camy, -1);
			dir = vec_normalize(&dir);
			dir = setcam(dir, cam);
			ray->dir = vec_normalize(&dir);
			if (intersect_sphere(ray, minirt) > 0)
				my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,255,182,193));
			else
				my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,0,0,0));
			pixelx++;
		}
		pixelx = 0;
		pixely++;
	}
	

}

void	make_scene(t_minirt *minirt)
{
	minirt->var.mlx = mlx_init();
	minirt->var.win = mlx_new_window(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y, "Scene Window");
	minirt->var.img = mlx_new_image(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y);
	minirt->var.addr = mlx_get_data_addr(minirt->var.img, &minirt->var.bits_per_pixel, &minirt->var.line_length, &minirt->var.endian);
	my_mlx_pixel_put(minirt, 500, 500, rgbt(0,255,182,193));
	// generate_ray(minirt);
	mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, minirt->var.img, 0, 0);
	mlx_hook(minirt->var.win, 17, 0L, close_button, minirt);
	mlx_key_hook(minirt->var.win, close_key, minirt);
	mlx_loop(minirt->var.mlx);
}


// while (y < resx)
// {
// 	transform y;
// 	while (x < resx)
// 	{
// 		transform x;
// 		make vec (x,y,-1);
// 		normalize vec;
// 		camtoworld(vec);
// 		normalize vec again;
				
// 		x++;
// 	}
// 	y++;
// 	x = 0;
// }