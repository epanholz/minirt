/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:21:18 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/17 18:20:41 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color		col_add(t_color c1, t_color c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return (c1);
}

static t_color		apply_color(t_color c1, t_color c2, double ratio)
{
	c1.r *= c2.r * ratio / 255;
	c1.g *= c2.g * ratio / 255;
	c1.b *= c2.b * ratio / 255;
	return (c1);
}

static t_color		apply_light(t_hit *hit, t_light *light, double diffuse)
{
	t_color	temp;
	t_color	light_color;
	t_vec3	dist;
	t_vec3	dist_norm;
	double	dotnormal;
	
	//(void)diffuse;
	light_color = light->color;
	dist = vec_sub(&light->light_point, &hit->hit_p);
	dist_norm = vec_normalize(&dist);
	dotnormal = vec_dot(&hit->surface_norm, &dist_norm);
	if ((dotnormal <= 1e-6 && hit->object == TRI)
		|| (dotnormal <= 1e-6 && hit->object == PLA))
		dotnormal = fabs(dotnormal);
	if (dotnormal <= 1e-6)
		return ((t_color){0, 0, 0});
	temp.r = light->color.r * light->light_b * fmax(0, dotnormal) * diffuse;
	temp.g = light->color.g * light->light_b * fmax(0, dotnormal) * diffuse;
	temp.b = light->color.b * light->light_b * fmax(0, dotnormal) * diffuse;
	temp = (t_color){fmin(temp.r, 255), fmin(temp.g, 255), fmin(temp.b, 255)};
	return (temp);
}

static void			ft_color_help(t_hit *hit, t_color amb)
{
	hit->col = col_add(amb, hit->col);
	hit->col = (t_color){fmin(amb.r, 255), fmin(amb.g, 255), fmin(amb.b, 255)};
}

void				calc_color(t_minirt *m, t_hit *hit)
{
	t_light_list	*current;
	t_color			amb;
	t_ray			ray;
	t_vec3			dir;

	amb = apply_color(hit->col, m->scene.a_color, m->scene.alight_r);
	current = m->list.l_head;
	if (current->light_index == 0)
	{
		ft_color_help(hit, amb);
		return ;
	}
	while (current)
	{
		dir = vec_sub(&current->light->light_point, &hit->hit_p);
		ray.dir = vec_normalize(&dir);
		ray.orig = hit->hit_p;
		hit->hit = 1;
		find_hit_light(m, &ray, sqrt(vec_dot(&dir, &dir) - 10 * 1e-6), hit);
		if (hit->hit == 0)
			amb = col_add(amb,
				apply_light(hit, current->light, 1 - m->scene.alight_r));
		current = current->next;
	}
	hit->col = (t_color){fmin(amb.r, 255), fmin(amb.g, 255), fmin(amb.b, 255)};

	// t_vec3			hit_p;
	// t_color			color;
	// t_light_list	*current;
	// t_vec3			dist;
	// t_ray			ray;
	
	// color = apply_color(hit->col, m->scene.a_color, m->scene.alight_r);
	// hit_p = hit->hit_p;
	// current = m->list.l_head;
	// if (current->light_index == 0)
	// {
	// 	ft_color_help(hit, color);
	// 	return ;
	// }
	// while (current)
	// {
	// 	dist = vec_sub(&current->light->light_point, &hit_p);
	// 	ray.dir = vec_normalize(&dist);
	// 	ray.orig = hit_p;
	// 	find_hit_light(m, &ray, sqrt(vec_dot(&dist, &dist) - 10 * 1e-6), hit);
	// 	if (hit->hit == 0)
	// 		color = col_add(color, apply_light(hit, current->light, 1 - m->scene.alight_r));
	// 	current = current->next;
	// }
	// color = (t_color){fmin(color.r, 255), fmin(color.g, 255),fmin(color.b, 255)};
	// hit->col = color;
}
