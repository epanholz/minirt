/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:52:15 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/05 03:55:40 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		color_add(t_color c1, t_color c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return (c1);
}

t_color		apply_color(t_color c1, t_color c2, double	ratio)
{
	c1.r *= c2.r * ratio / 255;
	c1.g *= c2.g * ratio / 255;
	c1.b *= c2.b * ratio / 255;
	return (c1);
}

// t_vec3		get_hit_point(t_ray *ray)
// {
// 	t_vec3		hit_p;
	
// 	//hit_p = get_hit_point(ray);
// 	// dist = vector_sub(&current->light.light_p, &hit_p);
// 	// (*ray)->norm_dir = vec_normalize(&dist);
// 	// (*ray)->orig = hit_p;
// 	//dist_norm = vec_normalize(&dist);

// 	ray->dir = dist_norm;
// 	ray->orig =  vector_x_d(hit->surface_norm, hit->t1 - 10 * 1e-6);
// 	return (hit_p);
// }

t_color	apply_light_tri(t_hit *hit, t_light *light)
{
	t_color	temp;
	t_vec3	dist;
	t_vec3	dist_norm;
	double	dotnormal;
	double	l_intensity;
	double	r2;

	temp = hit->color;
	dist = vectorSub(&light->light_point, &hit->hit_p_new);
	dist_norm = vec_normalize(&dist);
	dotnormal = vectorDot(&hit->surface_norm, &dist_norm);
	if ((dotnormal <= 1e-6 && hit->object == TRI) || (dotnormal <= 1e-6 && hit->object == PLA))
		dotnormal = fabs(dotnormal);
	if (dotnormal <= 1e-6)
		return ((t_color){0,0,0});	
	// if (dotnormal <= 1e-6)
	// 	dotnormal = fabs(dotnormal);
	r2 = vec3_pow(&dist);
	l_intensity = (light->light_b * dotnormal * 1000) / (4.0 * M_PI * r2);
	temp = apply_color(temp, light->color, fmin(1.0, fmax(0.0, l_intensity)));
	// temp.r *= 0.4;
	// temp.r = fmin(temp.r, 255);
	// temp.g *= 0.4;
	// temp.g = fmin(temp.g, 255);
	// temp.b *= 0.4;
	// temp.b = fmin(temp.b, 255);
	return (temp);
}

t_color	apply_light(t_hit *hit, t_light *light, double diffuse)
{
	t_color	temp;
	t_color	light_color;
	t_vec3	dist;
	t_vec3	dist_norm;
	double	shade;
	//double	diffuse;
	double	dotnormal;
	double	l_intensity;
	double	r2;

	temp = hit->color;
	light_color = light->color;
	//diffuse = 1 - (1 - light->light_b);
	dist = vectorSub(&light->light_point, &hit->hit_p_new);
	dist_norm = vec_normalize(&dist);
	dotnormal = vectorDot(&hit->surface_norm, &dist_norm);
	shade = vectorDot(&hit->surface_norm, &light->light_point);
	if ((shade <= 1e-6 && hit->object == TRI) || (shade <= 1e-6 && hit->object == PLA))
		shade = fabs(shade);	
	if (shade <= 1e-6)
		shade = 0;
	if ((dotnormal <= 1e-6 && hit->object == TRI) || (dotnormal <= 1e-6 && hit->object == PLA))
		dotnormal = fabs(dotnormal);
	if (dotnormal <= 1e-6)
		return ((t_color){0,0,0});
	r2 = vec3_pow(&dist);
	l_intensity = (light->light_b * dotnormal * 1000) / (4.0 * M_PI * r2);

	temp.r = light->color.r * diffuse * light->light_b * fmax(0, dotnormal);
	temp.r = fmin(temp.r, 255);
	temp.g = light->color.g * diffuse * light->light_b * fmax(0, dotnormal);
	temp.g = fmin(temp.g, 255);
	temp.b = light->color.b * diffuse * light->light_b * fmax(0, dotnormal);
	temp.b = fmin(temp.b, 255);
	
	// temp.r = light->color.r * diffuse * l_intensity;
	// temp.r = fmin(temp.r, 255);
	// temp.g = light->color.g * diffuse * l_intensity;
	// temp.g = fmin(temp.g, 255);
	// temp.b = light->color.b * diffuse * l_intensity;
	// temp.b = fmin(temp.b, 255);
	return (temp);
}

void	calc_color(t_minirt *minirt, t_hit *hit)
{
	t_light_list	*current;
	//t_hit			hit1;
	t_color			ambient;
	t_ray			ray;
	t_vec3			dir;
	t_light			*light;


	ambient = apply_color(hit->color, minirt->scene.a_color, minirt->scene.a_light_ratio);
	//hit->color = apply_color(hit->color, minirt->scene.a_color, minirt->scene.a_light_ratio);
	current = minirt->var.l_head;
	if (current->light_index == 0)
	{
		hit->color = color_add(ambient, hit->color);
		return ;
	}
	while (current)
	{
		light = current->light;
		dir = vectorSub(&light->light_point, &hit->hit_p_new);
		ray.dir = vec_normalize(&dir);
		ray.orig = hit->hit_p_new;
		//hit->hit_p = vec_x_d(&hit->hit_p, hit->t1 - 10 * 1e-6);
		find_hit_light(minirt, &ray, sqrt(vectorDot(&dir, &dir) - 10 * 1e-6), hit);
		//find_hit_light2(minirt, &ray, hit);
		if (hit->hit == 0)
		{
			ambient = color_add(ambient, apply_light(hit, current->light, 1 - minirt->scene.a_light_ratio));
			//printf("%f\n", current->light->light_b);
		}
		// else
		// 	hit->color = color_add(ambient, (t_color){0,0,0});		
		
		//hit->color = color_add(ambient, apply_light_tri(hit, current->light));
		
		//hit->color = color_add(hit->color, apply_light(hit, current->light));
		
		// if (hit->object == TRI || hit->object == PLA)
		// 	hit->color = color_add(ambient, apply_light_tri(hit, current->light));
		// else
		// 	hit->color = color_add(ambient, apply_light(hit, current->light));
		current = current->next;
	}
	hit->color = (t_color){fmin(ambient.r, 255), fmin(ambient.g, 255),fmin(ambient.b, 255)};
}

// void	calc_color(t_minirt *minirt, t_hit *hit, t_light *light)
// {
// 	t_vec3	l_dir;
// 	t_color	ambient;
// 	t_color light_color;
// 	double	shade;
// 	double	diffuse;	
	
// 	//normalized direction to light
// 	//dot product direction to light and surfacce norm 
// 	//The vector from the hit point to the light, l, I am setting to the light's position minus the hit point's position
// 	//v, the vector from the hit point to the camera, I am getting by simply negating the projected view vector;
// 	//object->color * intensity * fmax(0, surface_normal * light_direction);

// 	ambient = apply_color(hit->color, minirt->scene.a_color, minirt->scene.a_light_ratio);
// 	light_color = apply_color(hit->color, light->color, light->light_b);

// 	diffuse = 1 - (1 - light->light_b);
// 	l_dir = vectorSub(&light->light_point, &hit->hit_p);
// 	l_dir = vec_normalize(&l_dir);
// 	shade = vectorDot(&hit->surface_norm, &light->light_point);
// 	if (shade <= 1e-6 && hit->object != TRI)
// 		shade = 0;
// 	if (shade <= 1e-6 && hit->object == TRI)
// 		shade = fabs(shade);

// 	hit->color.r = ambient.r + (light->color.r * diffuse * light->light_b * shade * fmax(0, vectorDot(&hit->surface_norm,&l_dir)));
// 	hit->color.r = fmin(hit->color.r, 255);
// 	hit->color.g = ambient.g + (light->color.g * diffuse * light->light_b * shade * fmax(0, vectorDot(&hit->surface_norm,&l_dir)));
// 	hit->color.g = fmin(hit->color.g, 255);
// 	hit->color.b = ambient.b + (light->color.b * diffuse * light->light_b * shade * fmax(0, vectorDot(&hit->surface_norm,&l_dir)));
// 	hit->color.b = fmin(hit->color.b, 255);
// }
