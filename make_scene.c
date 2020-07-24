/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/24 02:16:12 by pani_zino     ########   odam.nl         */
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
	cam2world->row4 =(t_vec3){0,0,0};

	return(cam2world);
}

t_vec3	setcam(t_vec3 from, t_cam *cam)
{
	t_vec3 		new;
	t_matrix43	*c2w;

	if (cam->norm_vec.x == 0 && cam->norm_vec.y == 0 && cam->norm_vec.z == 0 )
		return(from);
	c2w = make_matrix(cam);
	new.x = from.x * c2w->row1.x + from.y * c2w->row2.x + from.z * c2w->row3.x;
	new.y = from.x * c2w->row1.y + from.y * c2w->row2.y + from.z * c2w->row3.y;
	new.z = from.x * c2w->row1.z + from.y * c2w->row2.z + from.z * c2w->row3.z;
	return (new);
}

float	intersect_sphere(t_ray *ray, t_sph *sphere, t_hit *hit, int color)
{
	//printf("[SPH in intersect] %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", sphere->sp_center.x, sphere->sp_center.y, sphere->sp_center.z, sphere->diameter, sphere->r, sphere->g, sphere->b);
	//printf("[RAY in intersect] %0.1f, %0.1f, %0.1f\n", ray->dir.x, ray->dir.y, ray->dir.z);

	// t_vec3		length;
	// float		t;	
	// float		x;
	// float		y;
	// float		t1;

	// if (color == 1)
	// {
	// 	hit->r = sphere->r;
	// 	hit->g = sphere->g;
	// 	hit->b = sphere->b;
	// }

	// length = vectorSub(&sphere->sp_center, &ray->orig);
	// t = vectorDot(&length, &ray->dir);
	// if (t < 0)
	// 	return (-1);
	// y = vectorDot(&length, &length) - (t * t);
	// if (y > (sphere->diameter * (sphere->diameter / 2)))
	// 	return (-1);
	// x = sqrt((sphere->diameter * (sphere->diameter* 0.25)) - y);
	// t1 = t - x;
	// return (t1);

	t_vec3		p;
	t_vec3		length1;
	t_vec3		temp2;
	t_vec3		temp3;
	float		t;	
	float		x;
	float		y;
	float		t1;
	float 		t2;

	if (color == 1)
	{
		hit->r = sphere->r;
		hit->g = sphere->g;
		hit->b = sphere->b;
	}
	//length of a vector -> sqrt of vectordot with the same vector
	//multiply float with vector -> float * x, float * y, float *z
	length1 = vectorSub(&sphere->sp_center, &ray->orig);
	t = vectorDot(&length1, &ray->dir);
	temp2 = vecFloat(&ray->dir, t);
	p = vectorPlus(&ray->orig, &temp2);
	temp3 = vectorSub(&sphere->sp_center, &p);
	y = sqrt(vectorDot(&temp3, &temp3));
	if (y > (sphere->diameter / 2))
		return (-1);
	x = (sphere->diameter / 2) - y;
	t1 = t - x;
	t2 = t + x;
	return (t1);
	//cast shadow ray
}

t_hit	*find_hit(t_minirt *minirt, t_ray *ray)
{
	t_hit			*hit;
	t_object_list	*current;

	hit = (t_hit*)malloc(sizeof(t_hit));
	hit->t1 = INFINITY;
	hit->t2 = 0;
	current = minirt->var.o_head;
	while (current)
	{
		if (current->object_type == SPH && (intersect_sphere(ray, current->scene_object, hit, 0) < hit->t1) && (intersect_sphere(ray, current->scene_object, hit, 0) != -1))
		{
			hit->t1 = intersect_sphere(ray, current->scene_object, hit, 1);
			hit->t2 = 1;
		}
		current = current->next;
	}
	return(hit);
}

void	generate_ray(t_minirt *minirt)
{
	t_sph		*sphere;
	t_cam		*cam;
	t_ray		*ray;
	t_hit		*hit;
	float		aspect_ratio;
	int			pixely;
	int 		pixelx;
	float		camy;
	float		camx;

	sphere = return_sphere(minirt);
	ray = (t_ray*)malloc(sizeof(t_ray));
	aspect_ratio = minirt->scene.res_x / minirt->scene.res_y;
	pixelx = 0;
	pixely = 0;
	camy = 0;
	camx = 0;
	cam = return_cam(minirt, 1);
	printf("\n[SPH in scene file] %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", sphere->sp_center.x, sphere->sp_center.y, sphere->sp_center.z, sphere->diameter, sphere->r, sphere->g, sphere->b);
	printf("[CAM in scene file] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d\n\n", cam->view_point.x, cam->view_point.y, cam->view_point.z, cam->norm_vec.x, cam->norm_vec.y, cam->norm_vec.z, cam->fov);
	ray->orig = cam->view_point;
	while (pixely < minirt->scene.res_y)
	{
		//transform camy
		camy = (1 - 2 * ((pixely + 0.5) / minirt->scene.res_y)) * tan(cam->fov / 2 * M_PI / 180);
		while(pixelx < minirt->scene.res_x)
		{
			//transform camx
			camx = (2 * ((pixelx + 0.5) / minirt->scene.res_x) - 1) * tan(cam->fov / 2 * M_PI / 180) * aspect_ratio;
			ray->dir = (t_vec3){camx, camy, -1};
			ray->dir = vec_normalize(&ray->dir);
			ray->dir = setcam(ray->dir, cam);
			ray->dir = vec_normalize(&ray->dir);
			hit = find_hit(minirt, ray);
			if (hit->t2 == 1)
				my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,hit->r,hit->g,hit->b));
			else
				my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,0,0,0));
			// 	my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,255,182,193));
			// else
			// 	my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,0,0,0));
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
	//my_mlx_pixel_put(minirt, 200, 200, rgbt(0,255,182,193));
	generate_ray(minirt);
	mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, minirt->var.img, 0, 0);
	mlx_hook(minirt->var.win, 17, 0L, close_button, minirt);
	mlx_key_hook(minirt->var.win, close_key, minirt);
	mlx_loop(minirt->var.mlx);
}

// FULL SCENE 
// R 700 500
// A 0.2 255,182,193

// c 0,0,0 0,0,-1 90
// sp 0,0,-20 2 255,0,0

// l -40,0,30 0.7 255,255,255
// pl 0,0,0 0,1.0,0 255,0,225
// sq 0,100,40 0,0,1.0 30 42,42,0
// cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
// tr 10,20,10 10,10,20 20,10,10 0,0,255


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