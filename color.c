/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:52:15 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/01 22:33:01 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		apply_color(t_color c1, t_color c2, double	ratio)
{
	c1.r *= c2.r * ratio / 255;
	c1.g *= c2.g * ratio / 255;
	c1.b *= c2.b * ratio / 255;

//	hit->color.b * minirt->scene.a_color.b * minirt->scene.a_light_ratio / 255;
	//r = hit->color.r * minirt->scene.l_r * minirt->scene.l_ratio / 255;
	return(c1);
}


void	calc_color(t_minirt *minirt, t_hit *hit, t_light *light)
{
	t_vec3	l_dir;
	t_color	ambient;
	t_color light_color;
	double	shade;
	double	diffuse;	
	double	r2;
	double	r1;
	double	l_power;
	
	//normalized direction to light
	//dot product direction to light and surfacce norm 
	//The vector from the hit point to the light, l, I am setting to the light's position minus the hit point's position
	//v, the vector from the hit point to the camera, I am getting by simply negating the projected view vector;
	//object->color * intensity * fmax(0, surface_normal * light_direction);

	ambient = apply_color(hit->color, minirt->scene.a_color, minirt->scene.a_light_ratio);
	light_color = apply_color(hit->color, light->color, light->light_b);

	diffuse = 1 - (1 - light->light_b);
	r2 = vec_distance(&hit->hit_p, &light->light_point);
	l_dir = vectorSub(&light->light_point, &hit->hit_p);
	l_dir = vec_normalize(&l_dir);
	r1 = vec3_pow(&l_dir);
	shade = vectorDot(&hit->surface_norm, &light->light_point);
	if (shade <= 1e-6)
		shade = 0;
	l_power = (light->light_b * shade * 1000) / (4.0 * M_PI * r1);

	//light_color = apply_color(hit->color, light->color, fmin(1.0, fmax(0.0, l_power)));
	// dotnormal = vectorDot(&ray->hit.hit_normal, &ray->norm_dir);
	// if (dotnormal <= 1e-6)
	// 	return ((t_colors){0,0,0});
	// // l was ALBEDO
	// r2 = vec3_pow(&dist);
	// l_intensity = (light.brightness * dotnormal * 1000) / ( 4.0 * M_PI * r2);
	//new = color_multiply(new , get_c_struct(light.colors), fmin(1.0, fmax(0.0, l_intensity)));
	//t_colors	color_multiply(t_colors c1, t_colors c2, double s)
	//c1.r *= (c2.r * s / 255);

	hit->color.r = ambient.r + (light->color.r * diffuse * light->light_b * shade * fmax(0, vectorDot(&hit->surface_norm,&l_dir)));
	hit->color.r = fmin(hit->color.r, 255);
	hit->color.g = ambient.g + (light->color.g * diffuse * light->light_b * shade * fmax(0, vectorDot(&hit->surface_norm,&l_dir)));
	hit->color.g = fmin(hit->color.g, 255);
	hit->color.b = ambient.b + (light->color.b * diffuse * light->light_b * shade * fmax(0, vectorDot(&hit->surface_norm,&l_dir)));
	hit->color.b = fmin(hit->color.b, 255);

	// hit->color.r = ambient.r + light->color.r;
	// hit->color.r = fmin(hit->color.r, 255);
	// hit->color.g = ambient.g + light->color.g;
	// hit->color.g = fmin(hit->color.g, 255);
	// hit->color.b = ambient.b + light->color.b;
	// hit->color.b = fmin(hit->color.b, 255);
}
