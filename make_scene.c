/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/04 20:50:06 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_lookup		G_lookup_table[] = {
	{SPH, &intersect_sphere},
	{TRI, &intersect_triangle},
	{PLA, &intersect_plane},
	{SQU, &intersect_square}
};

t_matrix43	lookat_matrix(t_vec3 from, t_vec3 to)
{
	t_matrix43	cam2world;
	t_vec3		norm_vec;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;
	t_vec3		temp;

	norm_vec = vectorSub(&to, &from);
	norm_vec = vec_normalize(&norm_vec);
	if (norm_vec.x == 0.0 && norm_vec.z == 0.0 && fabs(norm_vec.y) == 1.0)
	{
		cam2world.row1 = norm_vec.y == 1.0 ? vec3(1.0,0.0,0.0) : vec3(0.0,0.0,1.0);
		cam2world.row2 = norm_vec.y == 1.0 ? vec3(0.0,0.0,1.0) : vec3(1.0,0.0,0.0);
		cam2world.row3 = norm_vec.y == 1.0 ? vec3(0.0,1.0,0.0) : vec3(0.0,-1.0,0.0);
		return(cam2world);
	}

	temp = vec3(0,1,0);
	forward = vectorSub(&from, &to);
	forward = vec_normalize(&forward);
	right = crossProduct(&temp, &forward);
	up = crossProduct(&forward, &right);

	cam2world.row1 = right;
	cam2world.row2 = up;
	cam2world.row3 = forward;
	cam2world.row4 =(t_vec3){0,0,0};

	return(cam2world);
}

t_vec3	apply_matrix(t_matrix43 matrix, t_vec3	vec3)
{
	t_vec3	new;
	new.x = vec3.x * matrix.row1.x + vec3.y * matrix.row2.x + vec3.z * matrix.row3.x;
	new.y = vec3.x * matrix.row1.y + vec3.y * matrix.row2.y + vec3.z * matrix.row3.y;
	new.z = vec3.x * matrix.row1.z + vec3.y * matrix.row2.z + vec3.z * matrix.row3.z;
	return	(new);
}

t_vec3	setcam(t_vec3 from, t_vec3 to, t_vec3 norm_vec)
{
	t_matrix43	c2w;

	if (norm_vec.x == 0 && norm_vec.y == 0 && norm_vec.z == 0 )
		return(from);
	c2w = lookat_matrix(to, vectorPlus(&to, &norm_vec));
	return (apply_matrix(c2w, from));
}

t_vec3	setsquare(t_vec3 pos, t_vec3 norm_vec)
{
	t_matrix43	c2w;

	c2w = lookat_matrix(pos, norm_vec);
	return (apply_matrix(c2w, pos));
}

t_hit	intersect_triangle(t_ray *ray, t_tri *triangle)
{
	//ray->dir = (t_vec3){camx, camy, -1};
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

	hit.object = 0;
	hit.hit = -1;
	hit.t1 = INFINITY;
	hit.t2 = INFINITY;
	hit.surface_norm = (t_vec3){0,0,0};
	hit.hit_p = (t_vec3){0,0,0};
	hit.color = (t_color){triangle->r, triangle->g, triangle->b};

	A = vectorSub(&triangle->p2, &triangle->p1);
	B = vectorSub(&triangle->p3, &triangle->p1);
	N = crossProduct(&A, &B);
	N = vec_normalize(&N);
	if (fabs(vectorDot(&N, &ray->dir)) < 0.000001)
		return(hit);
	D = vectorDot(&N, &triangle->p1);
	t = -((vectorDot(&N, &ray->orig) - D) / vectorDot(&N, &ray->dir));
	if (t < 0)
		return(hit);
	temp = vec_x_d(&ray->dir, t);
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
	hit.object = TRI;
	hit.t1 = t;
	hit.hit = 1;
	hit.surface_norm = N;
	hit.hit_p = p;
	norm_temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
	hit.hit_p_new = vectorPlus(&ray->orig, &norm_temp);	
	return(hit);
}

t_hit	intersect_square(t_ray *ray, t_squ *square)
{
	t_hit		hit[2];
	//t_vec3		new_pos;
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;
	t_vec3		v3;

	t_vec3		temp[2];

	t_tri		t1;
	t_tri		t2;
	
	double		r;
	t_matrix43	c2w;

	r = square->side / 2;
	c2w = lookat_matrix(square->sq_center, vectorPlus(&square->sq_center, &square->norm_vec));
	c2w = (t_matrix43){vec_x_d(&c2w.row1, r), vec_x_d(&c2w.row2, r), c2w.row3, c2w.row4};
	temp[0] = vectorPlus(&square->sq_center, &c2w.row2);
	temp[1] = vectorSub(&square->sq_center, &c2w.row2);

	hit[0].object = 0;
	hit[0].hit = -1;
	hit[0].t1 = INFINITY;
	hit[0].t2 = 0;
	hit[0].surface_norm = (t_vec3){0,0,0};
	hit[0].hit_p = (t_vec3){0,0,0};
	hit[0].color = (t_color){square->r, square->g, square->b};
	//new_pos = apply_matrix(c2w, square->sq_center);
	
	v0 = (t_vec3){c2w.row1.x - r, c2w.row1.y + r, c2w.row1.z};
	v1 = (t_vec3){c2w.row2.x - r, c2w.row2.y - r, c2w.row2.z};
	v2 = (t_vec3){c2w.row3.x + r, c2w.row3.y - r, c2w.row3.z};
	v3 = (t_vec3){c2w.row4.x + r, c2w.row4.y + r, c2w.row4.z};
	// t1.p1 = v0;
	// t1.p2 = v1;
	// t1.p3 = v3;
	// t1.r = square->r;
	// t1.g = square->g;
	// t1.b = square->b;
	// t2.p1 = v1;
	// t2.p2 = v2;
	// t2.p3 = v3;
	// t2.r = square->r;
	// t2.g = square->g;
	// t2.b = square->b;

	t1 = (t_tri){vectorSub(&temp[0], &c2w.row1), vectorPlus(&temp[1], &c2w.row1), vectorSub(&temp[1], &c2w.row1), square->r, square->g, square->b};
	t2 = (t_tri){vectorPlus(&temp[0],&c2w.row1), t1.p1, t1.p2, square->r, square->g, square->b};
	hit[1] = intersect_triangle(ray, &t1);
	if (hit[1].hit == 1)
			return (hit[1]);
	hit[1] = intersect_triangle(ray, &t2);
	if (hit[1].hit == 1)
		return(hit[1]);
	return(hit[0]);
}

t_hit	intersect_plane(t_ray *ray, t_pla *plane)
{
	/*
	You know a point (x1,y1,z1) and normal vector (a,b,c). Then equation of plane should be:
	a(x-x1)+b(y-y1)+c(z-z1) = 0;	

	if (abs(denom) > 0.0001f) // your favorite epsilon
	{
		double t = (center - ray.origin).dot(normal) / denom;
		if (t >= 0) return true; // you might want to allow an epsilon here too
	}

	bool intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, double &t) 
	{ 
		// assuming vectors are all normalized
		double denom = dotProduct(n, l); 
		if (denom > 1e-6) { 
			Vec3f p0l0 = p0 - l0; 
			t = dotProduct(p0l0, n) / denom; 
			return (t >= 0); 
		} 
	
		return false; 
	} 

	*/
	t_hit		hit;
	t_vec3		length;
	double		denom;
	double		t;
	t_vec3		norm_temp;
	t_vec3		temp;
	
	hit.object = 0;
	hit.hit = -1;
	hit.t1 = INFINITY;
	hit.t2 = 0;
	hit.surface_norm = (t_vec3){0,0,0};
	hit.hit_p = (t_vec3){0,0,0};
	hit.color = (t_color){plane->r, plane->g, plane->b};
	
	denom = vectorDot(&plane->norm_vec, &ray->dir);
	if (denom > 1e-6)
	{
		length = vectorSub(&plane->view_point, &ray->orig);
		t = vectorDot(&length, &plane->norm_vec) / denom;
		if (t >= 0)
		{
			hit.object = PLA;
			hit.surface_norm = plane->norm_vec;
			temp = vec_x_d(&ray->dir, t);
			hit.hit_p = vectorPlus(&ray->orig, &temp);
			norm_temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
			hit.hit_p_new = vectorPlus(&ray->orig, &norm_temp);	
			hit.hit = 1;
			hit.t1 = t;
			return (hit);
		}
	}
	return (hit);
}

t_hit	intersect_sphere(t_ray *ray, t_sph *sphere)
{
	t_hit		hit;
	t_vec3		p;
	t_vec3		length1;
	t_vec3		temp2;
	t_vec3		temp3;
	t_vec3		norm_temp;
	double		t;	
	double		x;
	double		y;

	hit.object = 0;
	hit.hit = -1;
	hit.surface_norm = (t_vec3){0,0,0};
	hit.hit_p = (t_vec3){0,0,0};
	hit.t1 = INFINITY;
	hit.t2 = 0;
	hit.color = (t_color){sphere->r, sphere->g, sphere->b};
	length1 = vectorSub(&sphere->sp_center, &ray->orig);
	t = vectorDot(&length1, &ray->dir);
	if (t < 0)
		return(hit);
	temp2 = vec_x_d(&ray->dir, t);
	p = vectorPlus(&ray->orig, &temp2);
	temp3 = vectorSub(&sphere->sp_center, &p);
	y = sqrt(vectorDot(&temp3, &temp3));
	if (y > (sphere->diameter / 2))
		return(hit);
	x = (sphere->diameter / 2) - y;
	hit.object = SPH;
	hit.t1 = t - x;
	hit.t2 = t + x;
	hit.hit = 1;
	norm_temp = vec_x_d(&ray->dir, hit.t1 - 10 * 1e-6);
	hit.hit_p_new = vectorPlus(&ray->orig, &norm_temp);
	hit.surface_norm = vectorSub(&p, &sphere->sp_center);
	//hit.surface_norm = vec_x_d(&hit.surface_norm, -1);
	//hit.surface_norm = vec_normalize(&hit.surface_norm);
	hit.hit_p = p;
	return (hit);
	//cast shadow ray
}

void	find_hit_light2(t_minirt *minirt, t_ray *ray, t_hit *hit_p)
{
	t_hit			hit;
	t_object_list	*current;
	int 			i;
	t_function		*func;

	hit.hit = 0;
	hit.t1 = INFINITY;
	hit.t2 = 0;
	hit.hit_p = (t_vec3){0,0,0};
	hit.surface_norm = (t_vec3){0,0,0};
	i = 0;
	current = minirt->var.o_head;
	while (current)
	{
		while (i < 4)
		{
			if (G_lookup_table[i].index == current->object_type)
			{
				func = G_lookup_table[i].func;
				hit= (*func)(ray, current->scene_object);
				if (hit.hit == 1)
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


void	find_hit_light(t_minirt *minirt, t_ray *ray, double l, t_hit *hit_p)
{
	t_hit			hit[2];
	t_object_list	*current;
	int 			i;
	t_function		*func;

	hit[0].hit = 0;
	hit[0].t1 = INFINITY;
	hit[0].t2 = 0;
	hit[0].hit_p = (t_vec3){0,0,0};
	hit[0].surface_norm = (t_vec3){0,0,0};
	i = 0;
	current = minirt->var.o_head;
	while (current)
	{
		while (i < 4)
		{
			if (G_lookup_table[i].index == current->object_type)
			{
				func = G_lookup_table[i].func;
				hit[1] = (*func)(ray, current->scene_object);
				if (hit[1].hit == 1  && (hit[1].t1 < l && hit[1].t1 > 0))
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

t_hit	find_hit(t_minirt *minirt, t_ray *ray)
{
	t_hit			hit[2];
	t_object_list	*current;
	int 			i;
	t_function		*func;

	hit[0].hit = 0;
	hit[0].t1 = INFINITY;
	hit[0].t2 = 0;
	hit[0].hit_p = (t_vec3){0,0,0};
	hit[0].surface_norm = (t_vec3){0,0,0};
	i = 0;
	current = minirt->var.o_head;
	while (current)
	{
		while (i < 4)
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

void	generate_ray(t_minirt *minirt)
{
	t_cam			*cam;
	t_ray			*ray;
	t_hit			hit;
	t_img_list		*current;
	double			aspect_ratio;
	int				pixely;
	int 			pixelx;
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
			while(pixelx < minirt->scene.res_x)
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
					my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,hit.color.r,hit.color.g,hit.color.b));
				}
				else
					my_mlx_pixel_put(minirt, pixelx, pixely, rgbt(0,0,0,0));
				pixelx++;
			}
			pixelx = 0;
			pixely++;
		}
		current = current->next;
	}
}

void	make_scene(t_minirt *minirt)
{
	t_img_list	*current;

	minirt->var.mlx = mlx_init();
	minirt->var.win = mlx_new_window(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y, "Scene Window");
	// minirt->var.img = mlx_new_image(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y);
	// minirt->var.addr = mlx_get_data_addr(minirt->var.img, &minirt->var.bits_per_pixel, &minirt->var.line_length, &minirt->var.endian);
	//my_mlx_pixel_put(minirt, 200, 200, rgbt(0,255,182,193));
	create_images(minirt);
	traverse_img_list(&minirt->var.i_head);
	generate_ray(minirt);
	current = minirt->var.i_head;
	mlx_put_image_to_window(minirt->var.mlx, minirt->var.win, current->img, 0, 0);
	// delete_object_list(&minirt->var.o_head);
	// delete_cam_list(&minirt->var.c_head);
	mlx_hook(minirt->var.win, 17, 0L, close_button, minirt);
	//mlx_key_hook(minirt->var.win, close_key, minirt);
	mlx_key_hook(minirt->var.win, change_image, minirt);
	mlx_loop(minirt->var.mlx);
}

/* 

l 0,0,-1 0.5 137,214,224
l 0,0,-3 1 137,214,224
c 0,0,0 0,0,-1 90
c 1,1,1 0,0,-1 90
sp 0,2,-5 2 224,202,222
sp 0,0,-20 6 202,202,224
pl -2,-5,-20 0,-1,0 97,68,110
tr 2.,0.,-5. 2.,2.,-5. 0.,0.,-5. 109,129,140
tr 10.0,20.0,-10.0      10.0,10.0,-20.0   20.0,10.0,-10.0 88,162,191
sq -2,-2,-7 0,0,1 3 159,227,177


R 700 700
A 0.3 224,202,222

l 2,3.5,3 0.5 137,214,224
l -2,3.5,3 0.5 255,0,0

c 0,0,0 0,0,-1 90
c 1,1,1 0,0,-1 90

sp 0,2,-5 2 224,202,222
sp 0,0,-20 6 202,202,224

pl -2,-5,-20 0,-1,0 97,68,110

tr 2.,0.,-5. 2.,2.,-5. 0.,0.,-5. 109,129,140
tr 10.0,20.0,-10.0      10.0,10.0,-20.0   20.0,10.0,-10.0 88,162,191

sq -2,-2,-7 0,0,1 3 159,227,177

FUN SCENE 

l 2,3.5,3 0.5 137,214,224
l 0,0,-1 0.5 137,214,224
c 0,0,0 0,0,-1 90
c 1,1,1 0,0,-1 90
sp 0,2,-5 2 224,202,222
sp 0,0,-20 6 202,202,224
pl -2,-5,-20 0,-1,0 97,68,110
tr 2.,0.,-5. 2.,2.,-5. 0.,0.,-5. 109,129,140
tr 10.0,20.0,-10.0      10.0,10.0,-20.0   20.0,10.0,-10.0 88,162,191
sq -2,-2,-7 0,0,1 3 159,227,177
*/


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