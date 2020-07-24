/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/24 23:19:36 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_lookup		G_lookup_table[] = {
	{SPH, &intersect_sphere},
	{TRI, &intersect_triangle}
};

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

t_hit	intersect_triangle(t_ray *ray, t_tri *triangle)
{
	//ray->dir = (t_vec3){camx, camy, -1};
	t_hit		hit;
	t_vec3		A;
	t_vec3		B;
	t_vec3		N;
	t_vec3		edge0;
	t_vec3		edge1;
	t_vec3		edge2;
	t_vec3		C0;
	t_vec3		C1;
	t_vec3		C2;
	t_vec3		temp;
	t_vec3		p;
	t_vec3		t0;
	t_vec3		t1;
	t_vec3		t2;
	float		t;
	float		D;

	hit.hit = -1;
	hit.t1 = INFINITY;
	hit.t2 = 0;
	hit.r = triangle->r;
	hit.g = triangle->g;
	hit.b = triangle->b;
	A = vectorSub(&triangle->p2, &triangle->p1);
	B = vectorSub(&triangle->p3, &triangle->p1);

	N = crossProduct(&A, &B);
	//N = vec_normalize(&N);
	if (fabs(vectorDot(&N, &ray->dir)) == 0)
		return(hit);
	D = vectorDot(&N, &triangle->p1);
	t = -((vectorDot(&N, &ray->orig) - D) / vectorDot(&N, &ray->dir));
	if (t < 0)
		return(hit);
	temp = vecFloat(&ray->dir, t);
	p = vectorPlus(&ray->orig, &temp);
	edge0 = vectorSub(&triangle->p2, &triangle->p1);
	edge1 = vectorSub(&triangle->p3, &triangle->p2);
	edge2 = vectorSub(&triangle->p1, &triangle->p3);
	C0 = vectorSub(&p, &triangle->p1);
	C1 = vectorSub(&p, &triangle->p2);
	C2 = vectorSub(&p, &triangle->p3);
	t0 = crossProduct(&edge0, &C0);
	t1 = crossProduct(&edge1, &C1);
	t2 = crossProduct(&edge2, &C2);
	if (vectorDot(&N, &t0) < 0 || vectorDot(&N, &t1) < 0 || vectorDot(&N, &t2) < 0)
		return(hit);
	hit.t1 = t;
	hit.hit = 1;
	return(hit);
}

t_hit	intersect_sphere(t_ray *ray, t_sph *sphere)
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

	t_hit		hit;
	t_vec3		p;
	t_vec3		length1;
	t_vec3		temp2;
	t_vec3		temp3;
	float		t;	
	float		x;
	float		y;


	hit.hit = -1;
	hit.t1 = INFINITY;
	hit.t2 = 0;
	hit.r = sphere->r;
	hit.g = sphere->g;
	hit.b = sphere->b;
	//length of a vector -> sqrt of vectordot with the same vector
	//multiply float with vector -> float * x, float * y, float *z
	length1 = vectorSub(&sphere->sp_center, &ray->orig);
	t = vectorDot(&length1, &ray->dir);
	temp2 = vecFloat(&ray->dir, t);
	p = vectorPlus(&ray->orig, &temp2);
	temp3 = vectorSub(&sphere->sp_center, &p);
	y = sqrt(vectorDot(&temp3, &temp3));
	if (y > (sphere->diameter / 2))
		return(hit);
	x = (sphere->diameter / 2) - y;
	hit.t1 = t - x;
	hit.t2 = t + x;
	hit.hit = 1;
	return (hit);
	//cast shadow ray
}

t_hit	find_hit(t_minirt *minirt, t_ray *ray)
{
	t_hit			hit[2];
	t_object_list	*current;
	int 			i;
	t_function		*func;

	hit[0].t1 = INFINITY;
	hit[0].t2 = 0;
	i = 0;
	current = minirt->var.o_head;
	while (current)
	{
		while (i < 2)
		{
			if (G_lookup_table[i].index == current->object_type)
			{
				func = G_lookup_table[i].func;
				hit[1] = (*func)(ray, current->scene_object);
				if (hit[1].hit == 1  && hit[1].t1 < hit[0].t1)
					hit[0] = hit[1];

			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	return(hit[0]);
}

// t_hit	*find_hit(t_minirt *minirt, t_ray *ray)
// {
// 	t_hit			*hit;
// 	t_object_list	*current;
// 	float			t_temp;

// 	hit = (t_hit*)malloc(sizeof(t_hit));
// 	hit->t1 = INFINITY;
// 	hit->t2 = 0;
// 	current = minirt->var.o_head;
// 	while (current)
// 	{
// 		if (current->object_type == SPH)
// 		{
// 			t_temp = intersect_sphere(ray, current->scene_object, hit, 0);
// 			if (t_temp < hit->t1 && t_temp != -1)
// 			{
// 				hit->t1 = intersect_sphere(ray, current->scene_object, hit, 1);
// 				hit->t2 = 1;
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return(hit);
// }

void	generate_ray(t_minirt *minirt)
{
//	t_sph		*sphere;
	t_cam		*cam;
	t_ray		*ray;
	t_hit		hit;
	float		aspect_ratio;
	int			pixely;
	int 		pixelx;
	float		camy;
	float		camx;

	//sphere = return_sphere(minirt);
	ray = (t_ray*)malloc(sizeof(t_ray));
	aspect_ratio = minirt->scene.res_x / minirt->scene.res_y;
	pixelx = 0;
	pixely = 0;
	camy = 0;
	camx = 0;
	cam = return_cam(minirt, 1);
	//printf("\n[SPH in scene file] %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", sphere->sp_center.x, sphere->sp_center.y, sphere->sp_center.z, sphere->diameter, sphere->r, sphere->g, sphere->b);
	//printf("[CAM in scene file] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d\n\n", cam->view_point.x, cam->view_point.y, cam->view_point.z, cam->norm_vec.x, cam->norm_vec.y, cam->norm_vec.z, cam->fov);
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
			if (hit.hit == 1)
				my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,hit.r,hit.g,hit.b));
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
	//my_mlx_pixel_put(minirt, 200, 200, rgbt(0,255,182,193));
	generate_ray(minirt);
	mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, minirt->var.img, 0, 0);
	// delete_object_list(&minirt->var.o_head);
	// delete_cam_list(&minirt->var.c_head);
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