/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:51 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/15 21:09:26 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit				intersect_plane(t_ray *ray, t_pla *plane)
{
	t_hit		hit;
	t_vec3		temp;
	double		denom;
	double		t;

	hit = init_hit();
	hit.col = (t_color){plane->r, plane->g, plane->b};
	hit.surface_norm = vec_x_d(&plane->norm_vec, -1);
	denom = vec_dot(&hit.surface_norm, &ray->dir);
	temp = vec_sub(&plane->view_point, &ray->orig);
	t = vec_dot(&temp, &hit.surface_norm) / denom;
	if (t >= 0)
	{
		hit.object = PLA;
		temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
		hit.hit_p = vec_plus(&ray->orig, &temp);
		hit.hit = 1;
		hit.t1 = t;
		return (hit);
	}
	return (hit);
}

// t_hit				intersect_plane(t_ray *ray, t_pla *plane)
// {
// 	t_hit		hit;
// 	t_vec3		temp;
// 	double		denom;
// 	double		t;

// 	hit = init_hit();
// 	hit.col = (t_color){plane->r, plane->g, plane->b};
// 	hit.surface_norm = vec_x_d(&plane->norm_vec, -1);
// 	denom = vec_dot(&hit.surface_norm, &ray->dir);
// 	if (denom > 1e-6)
// 	{
// 		temp = vec_sub(&plane->view_point, &ray->orig);
// 		t = vec_dot(&temp, &hit.surface_norm) / denom;
// 		if (t >= 0)
// 		{
// 			hit.object = PLA;
// 			temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
// 			hit.hit_p = vec_plus(&ray->orig, &temp);
// 			hit.hit = 1;
// 			hit.t1 = t;
// 			return (hit);
// 		}
// 	}
// 	return (hit);
// }
