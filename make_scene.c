/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/18 16:08:42 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_lookup	g_lookup_table[] = {
	{SPH, &intersect_sphere},
	{TRI, &intersect_triangle},
	{PLA, &intersect_plane},
	{SQU, &intersect_square},
	{CYL, &intersect_cylinder}
};

t_hit				solve_quadratic(double a, double b, double c, t_hit hit)
{
	double discr;
	
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (hit);
	else if (discr == 0)
	{
		hit.hit = 1;
		hit.t1 = -b / (2 * a);
	}
	else if (discr > 0)
	{
		hit.hit = 1;
		hit.t1 = (-b + sqrt(discr)) / (2 * a);
		hit.t2 = (-b - sqrt(discr)) / (2 * a);
	}
	return (hit);
	//https://www.programiz.com/c-programming/examples/quadratic-roots
}

t_hit					init_hit(void)
{
	t_hit	hit;

	hit.object = 0;
	hit.hit = -1;
	hit.t1 = INFINITY;
	hit.t2 = INFINITY;
	hit.surface_norm = (t_vec3){0, 0, 0};
	hit.hit_p = (t_vec3){0, 0, 0};
	hit.col = (t_color){0, 0, 0};
	return (hit);
}


t_hit		get_hit_cyl(t_ray *ray, t_cyl *cyl, t_hit hit)
{
	t_vec3	temp1;
	t_vec3	dot_temp[3];
	t_vec3	base[2];
	double	dotproduct[4];
	double	ret;
	t_vec3		surf_norm[3];

	ret = INFINITY;

	temp1 = vec_x_d(&cyl->norm_vec, cyl->height / 2);
	base[0] = vec_sub(&cyl->center, &temp1);
	base[1] = vec_plus(&cyl->center, &temp1);
	dot_temp[0] = vec_x_d(&ray->dir, hit.t1);
	dot_temp[1] = vec_plus(&ray->orig, &dot_temp[0]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[0]);
	dotproduct[0] = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[1]);
	dotproduct[1] = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	dot_temp[0] = vec_x_d(&ray->dir, hit.t2);
	dot_temp[1] = vec_plus(&ray->orig, &dot_temp[0]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[0]);
	dotproduct[2] = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[1]);
	dotproduct[3] = vec_dot(&cyl->norm_vec, &dot_temp[2]);

	if (hit.hit == 1)
	{
		if (hit.t1 > 1e-6 && dotproduct[0] > 0.0 && dotproduct[1] < 0.0)
			ret = hit.t1;
		if (hit.t2 > 1e-6 && dotproduct[2] > 0.0 && dotproduct[3] < 0.0)
		{
			if (ret != INFINITY)
				ret = fmin(hit.t1, hit.t2);
			else
				ret = hit.t2;
		}
		if (ret > 1e-6)
		{
			hit.t1 = ret;
			surf_norm[0] = vec_x_d(&ray->dir, -1);
			surf_norm[1] = vec_plus(&ray->orig, &surf_norm[0]);
			surf_norm[2] = vec_sub(&surf_norm[1], &cyl->center);
			hit.surface_norm = vec_normalize(&surf_norm[2]);
		}
	}
	return (hit);
}

t_hit					intersect_cylinder(t_ray *ray, t_cyl *cyl)
{
	t_hit		hit;
	t_vec3		dist;
	t_vec3		temp[4];
	t_vec3		norm_temp;
	double		dot[2];
	double		radius;
	double		abc[3];
	

	hit = init_hit();
	hit.object = CYL;
	hit.col = (t_color){cyl->r, cyl->g, cyl->b};
	if (vec_pow(&cyl->norm_vec) != 0)
		cyl->norm_vec = vec_normalize(&cyl->norm_vec);
	radius = cyl->diameter / 2;
	dist = vec_sub(&ray->orig, &cyl->center);
	dot[0] = vec_dot(&ray->dir, &cyl->norm_vec);
	temp[0] = vec_x_d(&cyl->norm_vec, dot[0]);
	dot[1] = vec_dot(&dist, &cyl->norm_vec);
	temp[1] = vec_x_d(&cyl->norm_vec, dot[1]);

	temp[2] = vec_sub(&ray->dir, &temp[0]);
	abc[0] = vec_pow(&temp[2]);

	temp[3] = vec_sub(&dist, &temp[1]);
	abc[1] = 2.0 * vec_dot(&temp[2], &temp[3]);

	abc[2] = vec_pow(&temp[3]) - (radius * radius);


	hit = solve_quadratic(abc[0], abc[1], abc[2], hit);
	hit = get_hit_cyl(ray, cyl, hit);
	if (hit.hit == 1)
	{
		norm_temp = vec_x_d(&ray->dir, hit.t1 - 10 * 1e-6);
		hit.hit_p = vec_plus(&ray->orig, &norm_temp);
	}
	//t_vec3		surf_norm[3];
	// if (hit.hit == 1)
	// {
	// 	surf_norm[0] = vec_x_d(&ray->dir, -1);
	// 	surf_norm[1] = vec_plus(&ray->orig, &surf_norm[0]);
	// 	surf_norm[2] = vec_sub(&surf_norm[1], &cyl->center);
	// 	hit.surface_norm = vec_normalize(&surf_norm[2]);
	// }
	return(hit);


	// t_hit		hit;
	// t_vec3		source;
	// t_vec3		cross_norm[2];
	// t_vec3		vu;
	// t_vec3		vo;
	// t_vec3		norm_temp;
	// t_vec3		cyl_dir_inv;
	// double		radius;
	// double		len;
	// double		dist[2];
	// double		t;
	// double 		s;

	// hit = init_hit();
	// hit.col = (t_color){cyl->r, cyl->g, cyl->b};
	// 	if (vec_pow(&cyl->norm_vec) != 0)
	// 	cyl->norm_vec = vec_normalize(&cyl->norm_vec);
	// if (cyl->norm_vec.x == 0 && cyl->norm_vec.y == 0 && cyl->norm_vec.z == 0)
	// 	cyl->norm_vec = (t_vec3){0, 1, 0};
	// radius = cyl->diameter / 2;
	// cyl_dir_inv = vec_x_d(&cyl->norm_vec, -1);
	// source = vec_sub(&ray->orig, &cyl->center);
	// cross_norm[0] = cross_prod(&ray->dir, &cyl->norm_vec);
	// cross_norm[1] = cross_prod(&ray->dir, &cyl_dir_inv);
	// len = sqrt(pow(cross_norm[0].x, 2) + pow(cross_norm[0].y, 2) + pow(cross_norm[0].z, 2));
	// dist[0] = vec_dot(&source, &cross_norm[0]);
	// dist[1] = vec_dot(&source, &cross_norm[1]);
	// if (dist[0] <= radius)
	// {
	// 	vu = cross_prod(&source, &cyl->norm_vec);
	// 	t = -vec_dot(&vu, &cross_norm[0]) / len;
	// 	vo = cross_prod(&cross_norm[0], &cyl->norm_vec);
	// 	s = fabs(sqrt(radius * radius - dist[0] * dist[0]) / vec_dot(&ray->dir, &vo));
	// 	hit.t1 = t - s;
	// 	hit.t2 = t + s;

	// 	// double denom, denom2, t5, t6;
	// 	// t_vec3	length;
	// 	// t_vec3	dir2;
	// 	// dir2 = vec_x_d(&cyl->norm_vec, -1);
	// 	// denom = vec_dot(&cyl->norm_vec, &ray->dir);
	// 	// denom2 = vec_dot(&dir2, &ray->dir);
	// 	// length = vec_sub(&cyl->center, &ray->orig);
	// 	// t5 = vec_dot(&length, &cyl->norm_vec) / denom;
	// 	// t6 = vec_dot(&length, &dir2) / denom2;
	// 	// if (t5 > hit.t2 || t6 < hit.t1)
	// 	// 	return (hit);

	// 	double		t2;
	// 	double		dc, dw;
	// 	dc = vec_dot(&cyl->norm_vec, &ray->dir);
	// 	dw = vec_dot(&cyl->norm_vec, &ray->orig) + dist[0];
	// 	if (dc == 0.0 && dw >= 0.0)
	// 		return (hit);
	// 	else
	// 	{
	// 		t2 = - dw / dc;
	// 		if (dc >= 0.0)
	// 		{
	// 			if (t2 > hit.t1 && t2 < hit.t2)
	// 				hit.t2 = t2;
	// 			if (t2 < hit.t1)
	// 				return(hit);
	// 		}
	// 		else
	// 		{
	// 			if (t2 > hit.t1 && t2 < hit.t2)
	// 				hit.t1 = t2;
	// 			if (t2 > hit.t2)
	// 				return (hit);
	// 		}
	// 	}
	// 	dc = vec_dot(&cyl_dir_inv, &ray->dir);
	// 	dw = vec_dot(&cyl_dir_inv, &ray->orig) + dist[1];
	// 	if (dc == 0.0 && dw >= 0.0)
	// 		return (hit);
	// 	else
	// 	{
	// 		t2 = - dw / dc;
	// 		if (dc >= 0.0)
	// 		{
	// 			if (t2 > hit.t1 && t2 < hit.t2)
	// 				hit.t2 = t2;
	// 			if (t2 < hit.t1)
	// 				return(hit);
	// 		}
	// 		else
	// 		{
	// 			if (t2 > hit.t1 && t2 < hit.t2)
	// 				hit.t1 = t2;
	// 			if (t2 > hit.t2)
	// 				return (hit);
	// 		}
	// 	}
	// 	if (hit.t1 > hit.t2)
	// 		return(hit);

	// 	norm_temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
	// 	hit.hit_p = vec_plus(&ray->orig, &norm_temp);
	// 	hit.hit = 1;
	// 	//hit = get_hit_cyl(ray, cyl, hit);
	// 	t_vec3		surf_norm[3];
	// 	surf_norm[0] = vec_x_d(&ray->dir, -1);
	// 	surf_norm[1] = vec_plus(&ray->orig, &surf_norm[0]);
	// 	surf_norm[2] = vec_sub(&surf_norm[1], &cyl->center);
	// 	hit.surface_norm = vec_normalize(&surf_norm[2]);
	// }
	// return (hit);
}

t_hit					intersect_triangle(t_ray *ray, t_tri *triangle)
{
	t_hit		hit;
	t_vec3		norm_temp;
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
	double		t;
	double		D;

	hit = init_hit();
	hit.col = (t_color){triangle->r, triangle->g, triangle->b};
	A = vec_sub(&triangle->p2, &triangle->p1);
	B = vec_sub(&triangle->p3, &triangle->p1);
	N = cross_prod(&A, &B);
	N = vec_normalize(&N);
	if (fabs(vec_dot(&N, &ray->dir)) < 0.000001)
		return (hit);
	D = vec_dot(&N, &triangle->p1);
	t = -((vec_dot(&N, &ray->orig) - D) / vec_dot(&N, &ray->dir));
	if (t < 0)
		return (hit);
	temp = vec_x_d(&ray->dir, t);
	p = vec_plus(&ray->orig, &temp);
	edge0 = vec_sub(&triangle->p2, &triangle->p1);
	edge1 = vec_sub(&triangle->p3, &triangle->p2);
	edge2 = vec_sub(&triangle->p1, &triangle->p3);
	C0 = vec_sub(&p, &triangle->p1);
	C1 = vec_sub(&p, &triangle->p2);
	C2 = vec_sub(&p, &triangle->p3);
	t0 = cross_prod(&edge0, &C0);
	t1 = cross_prod(&edge1, &C1);
	t2 = cross_prod(&edge2, &C2);
	if (vec_dot(&N, &t0) < 0 || vec_dot(&N, &t1) < 0 || vec_dot(&N, &t2) < 0)
		return (hit);
	hit.object = TRI;
	hit.t1 = t;
	hit.hit = 1;
	hit.surface_norm = N;
	norm_temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
	hit.hit_p = vec_plus(&ray->orig, &norm_temp);
	return (hit);
}

t_hit					intersect_square(t_ray *ray, t_squ *square)
{
	t_hit		hit[2];
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;
	t_vec3		v3;
	t_vec3		temp[2];
	t_tri		t1;
	t_tri		t2;
	double		r;
	t_matrix	c2w;

	hit[0] = init_hit();
	hit[0].col = (t_color){square->r, square->g, square->b};
	r = square->side / 2;
	c2w = lookat_matrix(square->sq_center, vec_plus(&square->sq_center, &square->norm_vec));
	c2w = (t_matrix){vec_x_d(&c2w.row1, r), vec_x_d(&c2w.row2, r), c2w.row3, c2w.row4};
	temp[0] = vec_plus(&square->sq_center, &c2w.row2);
	temp[1] = vec_sub(&square->sq_center, &c2w.row2);
	hit[0].object = 0;
	v0 = (t_vec3){c2w.row1.x - r, c2w.row1.y + r, c2w.row1.z};
	v1 = (t_vec3){c2w.row2.x - r, c2w.row2.y - r, c2w.row2.z};
	v2 = (t_vec3){c2w.row3.x + r, c2w.row3.y - r, c2w.row3.z};
	v3 = (t_vec3){c2w.row4.x + r, c2w.row4.y + r, c2w.row4.z};
	t1 = (t_tri){vec_sub(&temp[0], &c2w.row1), vec_plus(&temp[1], &c2w.row1), vec_sub(&temp[1], &c2w.row1), square->r, square->g, square->b};
	t2 = (t_tri){vec_plus(&temp[0], &c2w.row1), t1.p1, t1.p2, square->r, square->g, square->b};
	hit[1] = intersect_triangle(ray, &t1);
	if (hit[1].hit == 1)
		return (hit[1]);
	hit[1] = intersect_triangle(ray, &t2);
	if (hit[1].hit == 1)
		return (hit[1]);
	return (hit[0]);
}

t_hit				intersect_plane(t_ray *ray, t_pla *plane)
{
	t_hit		hit;
	t_vec3		length;
	double		denom;
	double		t;
	t_vec3		norm_temp;
	t_vec3		temp;

	hit = init_hit();
	hit.col = (t_color){plane->r, plane->g, plane->b};
	denom = vec_dot(&plane->norm_vec, &ray->dir);
	if (denom > 1e-6)
	{
		length = vec_sub(&plane->view_point, &ray->orig);
		t = vec_dot(&length, &plane->norm_vec) / denom;
		if (t >= 0)
		{
			hit.object = PLA;
			hit.surface_norm = plane->norm_vec;
			temp = vec_x_d(&ray->dir, t);
			norm_temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
			hit.hit_p = vec_plus(&ray->orig, &norm_temp);
			hit.hit = 1;
			hit.t1 = t;
			return (hit);
		}
	}
	return (hit);
}

static void			check_sph_inter(t_hit *hit)
{
	double	tempp;

	if (hit->t1 > hit->t2)
	{
		tempp = hit->t1;
		hit->t1 = hit->t2;
		hit->t2 = tempp;
	}
	if (hit->t1 < 0)
	{
		hit->t1 = hit->t2;
		if (hit->t1 < hit->t2)
			hit->hit = 0;
	}
}

t_hit				intersect_sphere(t_ray *ray, t_sph *sphere)
{
	t_hit		hit;
	t_vec3		p;
	t_vec3		length1;
	t_vec3		temp2;
	t_vec3		temp3;
	t_vec3		norm_temp;
	t_vec3		fuck[2];
	double		t;
	double		x;
	double		y;

	hit = init_hit();
	hit.col = (t_color){sphere->r, sphere->g, sphere->b};
	length1 = vec_sub(&sphere->sp_center, &ray->orig);
	t = vec_dot(&length1, &ray->dir);
	if (t < 0)
		return (hit);
	temp2 = vec_x_d(&ray->dir, t);
	p = vec_plus(&ray->orig, &temp2);
	temp3 = vec_sub(&sphere->sp_center, &p);
	y = vec_dot(&length1, &length1) - t * t;
	if (y > (sphere->diameter / 2) * (sphere->diameter / 2))
		return (hit);
	x = sqrt(((sphere->diameter / 2) * (sphere->diameter / 2)) - y);
	hit.object = SPH;
	hit.t1 = t - x;
	hit.t2 = t + x;
	hit.hit = 1;
	norm_temp = vec_x_d(&ray->dir, hit.t1 - 10 * 1e-6);
	hit.hit_p = vec_plus(&ray->orig, &norm_temp);
	fuck[0] = vec_x_d(&ray->dir, hit.t1);
	fuck[1] = vec_plus(&ray->orig, &fuck[0]);
	hit.surface_norm = vec_sub(&fuck[1], &sphere->sp_center);
	check_sph_inter(&hit);
	return (hit);
}

void				find_hit_light(t_minirt *minirt, t_ray *ray, double l, t_hit *hit_p)
{
	t_hit			hit[2];
	t_object_list	*current;
	int				i;
	t_function		*func;

	hit[0] = init_hit();
	i = 0;
	current = minirt->var.o_head;
	while (current)
	{
		while (i < 5)
		{
			if (g_lookup_table[i].index == current->object_type)
			{
				func = g_lookup_table[i].func;
				hit[1] = (*func)(ray, current->scene_object);
				if (hit[1].hit == 1 && (hit[1].t1 < l && hit[1].t1 > 0))
				{
					hit_p->hit = 1;
					return ;
				}
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	hit_p->hit = 0;
}

t_hit				find_hit(t_minirt *minirt, t_ray *ray)
{
	t_hit			hit[2];
	t_object_list	*current;
	int				i;
	t_function		*func;

	hit[0] = init_hit();
	i = 0;
	current = minirt->var.o_head;
	while (current)
	{
		while (i < 5)
		{
			if (g_lookup_table[i].index == current->object_type)
			{
				func = g_lookup_table[i].func;
				hit[1] = (*func)(ray, current->scene_object);
				if (hit[1].hit == 1 && hit[1].t1 < hit[0].t1)
					hit[0] = hit[1];
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	return (hit[0]);
}

void				generate_ray(t_minirt *minirt)
{
	t_cam			*cam;
	t_ray			*ray;
	t_hit			hit;
	t_img_list		*current;
	double			aspect_ratio;
	int				pixely;
	int				pixelx;
	double			camy;
	double			camx;

	current = minirt->var.i_head;
	ray = (t_ray*)malloc(sizeof(t_ray));
	aspect_ratio = minirt->scene.res_x / minirt->scene.res_y;
	while (current)
	{
		pixelx = 0;
		pixely = 0;
		camy = 0;
		camx = 0;
		cam = return_cam(minirt, current->img_index);
		ray->orig = cam->view_point;
		minirt->var.img = current->img;
		minirt->var.addr = current->addr;
		while (pixely < minirt->scene.res_y)
		{
			camy = (1 - 2 * ((pixely + 0.5) / minirt->scene.res_y)) * tan(cam->fov / 2 * M_PI / 180);
			while (pixelx < minirt->scene.res_x)
			{
				camx = (2 * ((pixelx + 0.5) / minirt->scene.res_x) - 1) * tan(cam->fov / 2 * M_PI / 180) * aspect_ratio;
				ray->dir = (t_vec3){camx, camy, -1};
				ray->dir = vec_normalize(&ray->dir);
				ray->dir = setcam(ray->dir, cam->view_point, cam->norm_vec);
				ray->dir = vec_normalize(&ray->dir);
				hit = find_hit(minirt, ray);
				if (hit.hit == 1)
				{
					calc_color(minirt, &hit);
					my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0, hit.col.r, hit.col.g, hit.col.b));
				}
				else
					my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0, 0, 0, 0));
				pixelx++;
			}
			pixelx = 0;
			pixely++;
		}
		current = current->next;
	}
}

void				make_scene(t_minirt *minirt)
{
	t_bitmap	*bitmap;
	t_img_list	*current;
	int			x;
	int			y;

	x = minirt->scene.res_x;
	y = minirt->scene.res_y;
	minirt->var.mlx = mlx_init();
	mlx_get_screen_size(minirt->var.mlx, &x, &y);
	minirt->scene.res_x = (minirt->scene.res_x > x) ? x : minirt->scene.res_x;
	minirt->scene.res_y = (minirt->scene.res_y > y) ? y : minirt->scene.res_y;
	create_images(minirt);
	generate_ray(minirt);
	current = minirt->var.i_head;
	if (minirt->scene.save == 1)
	{
		bitmap = initialize_bitmap(minirt->scene.res_x, minirt->scene.res_y);
		fill_bmp_buff(bitmap, minirt, current->addr);
		write_bitmap_to_file(bitmap);
	}
	else
	{
		minirt->var.win = mlx_new_window(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y, "Scene Window");
		mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, current->img, 0, 0);
		// delete_object_list(&minirt->var.o_head);
		// delete_cam_list(&minirt->var.c_head);
		mlx_hook(minirt->var.win, 17, 0L, close_button, minirt);
		mlx_key_hook(minirt->var.win, change_image, minirt);
		mlx_loop(minirt->var.mlx);
	}
}
