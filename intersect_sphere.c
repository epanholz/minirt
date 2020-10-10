/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_sphere.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:56 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:20:57 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		check_sph_inter(t_hit *hit)
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

static void		set_hit_sphere(t_ray *ray, t_hit *hit,
					t_vec3 sphere_center, double x)
{
	t_vec3		temp[2];
	double		t;

	t = hit->t1;
	hit->object = SPH;
	hit->t1 = t - x;
	hit->t2 = t + x;
	hit->hit = 1;
	temp[0] = vec_x_d(&ray->dir, hit->t1 - 10 * 1e-6);
	hit->hit_p = vec_plus(&ray->orig, &temp[0]);
	temp[0] = vec_x_d(&ray->dir, hit->t1);
	temp[1] = vec_plus(&ray->orig, &temp[0]);
	hit->surface_norm = vec_sub(&temp[1], &sphere_center);
}

t_hit			intersect_sphere(t_ray *ray, t_sph *sphere)
{
	t_hit		hit;
	t_vec3		p;
	t_vec3		length;
	t_vec3		temp[2];
	double		txy[3];

	hit = init_hit();
	hit.col = (t_color){sphere->r, sphere->g, sphere->b};
	length = vec_sub(&sphere->sp_center, &ray->orig);
	txy[0] = vec_dot(&length, &ray->dir);
	if (txy[0] < 0)
		return (hit);
	temp[0] = vec_x_d(&ray->dir, txy[0]);
	p = vec_plus(&ray->orig, &temp[0]);
	txy[2] = vec_dot(&length, &length) - txy[0] * txy[0];
	if (txy[2] > (sphere->diameter / 2) * (sphere->diameter / 2))
		return (hit);
	txy[1] = sqrt(((sphere->diameter / 2) * (sphere->diameter / 2)) - txy[2]);
	hit.t1 = txy[0];
	set_hit_sphere(ray, &hit, sphere->sp_center, txy[1]);
	check_sph_inter(&hit);
	return (hit);
}
