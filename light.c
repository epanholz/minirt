/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:52:15 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:05 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		col_add(t_color c1, t_color c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return (c1);
}

t_color		apply_color(t_color c1, t_color c2, double ratio)
{
	c1.r *= c2.r * ratio / 255;
	c1.g *= c2.g * ratio / 255;
	c1.b *= c2.b * ratio / 255;
	return (c1);
}

t_color		apply_light(t_hit *hit, t_light *light, double diffuse)
{
	t_color	temp;
	t_color	light_color;
	t_vec3	dist;
	t_vec3	dist_norm;
	double	dotnormal;

	temp = hit->col;
	light_color = light->color;
	dist = vec_sub(&light->light_point, &hit->hit_p_new);
	dist_norm = vec_normalize(&dist);
	dotnormal = vec_dot(&hit->surface_norm, &dist_norm);
	if ((dotnormal <= 1e-6 && hit->object == TRI)
		|| (dotnormal <= 1e-6 && hit->object == PLA))
		dotnormal = fabs(dotnormal);
	if (dotnormal <= 1e-6)
		return ((t_color){0, 0, 0});
	temp.r = light->color.r * diffuse * light->light_b * fmax(0, dotnormal);
	temp.g = light->color.g * diffuse * light->light_b * fmax(0, dotnormal);
	temp.b = light->color.b * diffuse * light->light_b * fmax(0, dotnormal);
	temp = (t_color){fmin(temp.r, 255), fmin(temp.g, 255), fmin(temp.b, 255)};
	return (temp);
}

void		calc_color(t_minirt *m, t_hit *hit)
{
	t_light_list	*current;
	t_color			amb;
	t_ray			ray;
	t_vec3			dir;

	amb = apply_color(hit->col, m->scene.a_color, m->scene.alight_r);
	current = m->var.l_head;
	if (current->light_index == 0)
	{
		hit->col = col_add(amb, hit->col);
		return ;
	}
	while (current)
	{
		dir = vec_sub(&current->light->light_point, &hit->hit_p_new);
		ray.dir = vec_normalize(&dir);
		ray.orig = hit->hit_p_new;
		find_hit_light(m, &ray, sqrt(vec_dot(&dir, &dir) - 10 * 1e-6), hit);
		if (hit->hit == 0)
			amb = col_add(amb,
			apply_light(hit, current->light, 1 - m->scene.alight_r));
		current = current->next;
	}
	hit->col = (t_color){fmin(amb.r, 255), fmin(amb.g, 255), fmin(amb.b, 255)};
}