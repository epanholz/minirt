/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_triangle.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 14:29:40 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/25 16:18:26 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tri_utils		get_tri_variables(t_ray *ray, t_tri *tri)
{
	t_tri_utils	utils;

	utils.a = vec_sub(&tri->p2, &tri->p1);
	utils.b = vec_sub(&tri->p3, &tri->p1);
	utils.n = cross_prod(&utils.a, &utils.b);
	utils.n = vec_normalize(&utils.n);
	utils.d = vec_dot(&utils.n, &tri->p1);
	utils.t = -((vec_dot(&utils.n, &ray->orig) - utils.d)
		/ vec_dot(&utils.n, &ray->dir));
	utils.temp = vec_x_d(&ray->dir, utils.t);
	utils.p = vec_plus(&ray->orig, &utils.temp);
	utils.edge0 = vec_sub(&tri->p2, &tri->p1);
	utils.edge1 = vec_sub(&tri->p3, &tri->p2);
	utils.edge2 = vec_sub(&tri->p1, &tri->p3);
	utils.c0 = vec_sub(&utils.p, &tri->p1);
	utils.c1 = vec_sub(&utils.p, &tri->p2);
	utils.c2 = vec_sub(&utils.p, &tri->p3);
	utils.t0 = cross_prod(&utils.edge0, &utils.c0);
	utils.t1 = cross_prod(&utils.edge1, &utils.c1);
	utils.t2 = cross_prod(&utils.edge2, &utils.c2);
	return (utils);
}

t_hit					intersect_triangle(t_ray *ray, t_tri *tri)
{
	t_hit		hit;
	t_tri_utils	utils;

	hit = init_hit();
	hit.col = (t_color){tri->r, tri->g, tri->b};
	utils = get_tri_variables(ray, tri);
	if (fabs(vec_dot(&utils.n, &ray->dir)) < 0.000001)
		return (hit);
	if (utils.t < 0)
		return (hit);
	if (vec_dot(&utils.n, &utils.t0) < 0 ||
		vec_dot(&utils.n, &utils.t1) < 0 ||
		vec_dot(&utils.n, &utils.t2) < 0)
		return (hit);
	hit.object = TRI;
	hit.t1 = utils.t;
	hit.hit = 1;
	hit.surface_norm = utils.n;
	utils.norm_temp = vec_x_d(&ray->dir, utils.t - 10 * 1e-6);
	hit.hit_p = vec_plus(&ray->orig, &utils.norm_temp);
	return (hit);
}
