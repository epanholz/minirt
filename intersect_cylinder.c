/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_cylinder.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:45 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/16 18:42:17 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit			solve_quadratic(double a, double b, double c, t_hit hit)
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
}

static void				find_hit_cyl(t_ray *ray, t_cyl *cyl,
							t_hit *hit, t_cyl_utils utils)
{
	double	ret;
	t_vec3	surf_norm[3];
	t_vec3	temp;

	ret = INFINITY;
	if (hit->t1 > 1e-6 && utils.dot1 > 0.0 && utils.dot2 < 0.0)
		ret = hit->t1;
	if (hit->t2 > 1e-6 && utils.dot3 > 0.0 && utils.dot4 < 0.0)
	{
		if (ret != INFINITY)
			ret = fmin(hit->t1, hit->t2);
		else
			ret = hit->t2;
	}

	//hit->t1 = ret;

	if (ret == hit->t1)
	{
		// surf_norm[0] = vec_x_d(&ray->dir, -1);
		// surf_norm[1] = vec_plus(&ray->orig, &surf_norm[0]);
		// surf_norm[2] = vec_sub(&surf_norm[1], &cyl->center);
		// hit->surface_norm = vec_normalize(&surf_norm[2]);
		
		t_vec3	hb;
		t_vec3	p;
		t_vec3	t;
		t_vec3	dir;
		double	norm_temp;
		double	r;
		r = cyl->height / 2;
		dir = vec_x_d(&ray->dir, -1);
		t = vec_x_d(&ray->dir, hit->t1);
		p = vec_plus(&ray->orig, &t);
		hb = vec_sub(&p, &cyl->center);
		norm_temp = vec_dot(&hb, &cyl->norm_vec);
		surf_norm[0] = vec_x_d(&cyl->norm_vec, norm_temp);
		surf_norm[1] = vec_sub(&hb, &surf_norm[0]);
		surf_norm[2] = vec_sub(&surf_norm[1], &hb);
		surf_norm[2] = vec_x_d(&surf_norm[2], -1);
		//surf_norm[2] = (t_vec3){surf_norm[1].x / r, surf_norm[1].y / r, surf_norm[1].z / r}; 
		hit->surface_norm = vec_normalize(&surf_norm[2]);

		// t_vec3	vec[3];
		// vec[0] = vec_x_d(&ray->dir, hit->t1);
		// vec[1] = vec_plus(&ray->orig, &vec[0]);
		// vec[2] = vec_sub(&vec[1], &cyl->center);
		// hit->surface_norm = vec_normalize(&vec[2]);
	}
	if (ret == hit->t2)
	{
		t_vec3	hb;
		t_vec3	p;
		t_vec3	t;
		double	norm_temp;
		double	r;
		r = cyl->height / 2;
		t = vec_x_d(&ray->dir, hit->t2);
		p = vec_plus(&ray->orig, &t);
		hb = vec_sub(&p, &cyl->center);
		norm_temp = vec_dot(&hb, &cyl->norm_vec);
		surf_norm[0] = vec_x_d(&cyl->norm_vec, norm_temp);
		surf_norm[1] = vec_sub(&hb, &surf_norm[0]);
		//surf_norm[2] = (t_vec3){surf_norm[1].x / r, surf_norm[1].y / r, surf_norm[1].z / r}; 
		hit->surface_norm = vec_normalize(&surf_norm[1]);

		// t_vec3	vec[3];
		// vec[0] = vec_x_d(&ray->dir, hit->t2);
		// vec[1] = vec_plus(&ray->orig, &vec[0]);
		// vec[2] = vec_sub(&vec[1], &cyl->center);
		// hit->surface_norm = vec_normalize(&vec[2]);
	}
	hit->t1 = ret;
	temp = vec_x_d(&ray->dir, hit->t1 - 10 * 1e-6);
	hit->hit_p = vec_plus(&ray->orig, &temp);
	hit->object = CYL;
}

static t_cyl_utils		get_utils(t_ray *ray, t_cyl *cyl, t_hit hit)
{
	t_cyl_utils	utils;
	t_vec3		temp1;
	t_vec3		dot_temp[3];
	t_vec3		base[2];

	temp1 = vec_x_d(&cyl->norm_vec, cyl->height / 2);
	base[0] = vec_sub(&cyl->center, &temp1);
	base[1] = vec_plus(&cyl->center, &temp1);
	dot_temp[0] = vec_x_d(&ray->dir, hit.t1);
	dot_temp[1] = vec_plus(&ray->orig, &dot_temp[0]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[0]);
	utils.dot1 = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[1]);
	utils.dot2 = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	dot_temp[0] = vec_x_d(&ray->dir, hit.t2);
	dot_temp[1] = vec_plus(&ray->orig, &dot_temp[0]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[0]);
	utils.dot3 = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	dot_temp[2] = vec_sub(&dot_temp[1], &base[1]);
	utils.dot4 = vec_dot(&cyl->norm_vec, &dot_temp[2]);
	return (utils);
}

t_hit					intersect_cylinder(t_ray *ray, t_cyl *cyl)
{
	t_hit		hit;
	t_cyl_utils	utils;
	t_vec3		temp[5];
	double		dot[2];
	double		abc[3];

	hit = init_hit();
	hit.col = (t_color){cyl->r, cyl->g, cyl->b};
	if (vec_pow(&cyl->norm_vec) != 0)
		cyl->norm_vec = vec_normalize(&cyl->norm_vec);
	temp[4] = vec_sub(&ray->orig, &cyl->center);
	dot[0] = vec_dot(&ray->dir, &cyl->norm_vec);
	temp[0] = vec_x_d(&cyl->norm_vec, dot[0]);
	dot[1] = vec_dot(&temp[4], &cyl->norm_vec);
	temp[1] = vec_x_d(&cyl->norm_vec, dot[1]);
	temp[2] = vec_sub(&ray->dir, &temp[0]);
	abc[0] = vec_pow(&temp[2]);
	temp[3] = vec_sub(&temp[4], &temp[1]);
	abc[1] = 2.0 * vec_dot(&temp[2], &temp[3]);
	abc[2] = vec_pow(&temp[3]) - ((cyl->diameter / 2) * (cyl->diameter / 2));
	hit = solve_quadratic(abc[0], abc[1], abc[2], hit);
	utils = get_utils(ray, cyl, hit);
	if (hit.hit == 1)
		find_hit_cyl(ray, cyl, &hit, utils);
	return (hit);
}
