/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 15:39:14 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/22 15:56:31 by pani_zino     ########   odam.nl         */
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
	denom = vec_dot(&plane->norm_vec, &ray->dir);
	if (denom > 1e-6)
	{
		temp = vec_sub(&plane->view_point, &ray->orig);
		t = vec_dot(&temp, &plane->norm_vec) / denom;
		if (t >= 0)
		{
			hit.object = PLA;
			hit.surface_norm = plane->norm_vec;
			temp = vec_x_d(&ray->dir, t - 10 * 1e-6);
			hit.hit_p = vec_plus(&ray->orig, &temp);
			hit.hit = 1;
			hit.t1 = t;
			return (hit);
		}
	}
	return (hit);
}
