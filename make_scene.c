/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/21 21:02:59 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float		make_matrix(t_minirt *minirt, t_cam *cam)
// {
// 	float	cam2world[4][4];
// 	t_vec3	forward;
// 	t_vec3	right;
// 	t_vec3	up;
// 	t_vec3	temp;

// 	temp = vec3(0,1,0);
// 	forward = vectorSub(&cam->view_point, &cam->norm_vec);
// 	forward = vec_normalize(&forward);
// 	right = crossProduct(&temp, &forward);
// 	up = crossProduct(&forward, &right);

// 	cam2world[0][0] = right.x; 
//     cam2world[0][1] = right.y; 
//     cam2world[0][2] = right.z; 
//     cam2world[1][0] = up.x; 
//     cam2world[1][1] = up.y; 
//     cam2world[1][2] = up.z; 
//     cam2world[2][0] = forward.x; 
//     cam2world[2][1] = forward.y; 
//     cam2world[2][2] = forward.z; 
 
//     cam2world[3][0] = cam->view_point.x; 
//     cam2world[3][1] = cam->view_point.y; 
//     cam2world[3][2] = cam->view_point.z; 

// 	return(cam2world);
// }

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

void	generate_ray(t_minirt *minirt)
{
	t_cam		*cam;
	t_vec3		origin;
	float		aspect_ratio;
	int			pixely;
	int 		pixelx;
	float		camy;
	float		camx;

	aspect_ratio = minirt->scene.res_x / minirt->scene.res_y;
	pixelx = 0;
	pixely = 0;
	camy = 0;
	camx = 0;
	cam = return_cam(minirt, 1);
	while (pixely <= minirt->scene.res_y)
	{
		//transform camy
		camy = (1 - 2 * ((pixely + 0.5) / minirt->scene.res_y)) * tan(cam->fov / 2 * M_PI / 180);
		while(pixelx <= minirt->scene.res_x)
		{
			//transform camx
			camx = (2 * ((pixelx + 0.5) / minirt->scene.res_x) - 1) * tan(cam->fov / 2 * M_PI / 180) * aspect_ratio;
			origin = vec3(camx, camy, -1);
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