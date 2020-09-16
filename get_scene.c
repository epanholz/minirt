/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 17:58:22 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/16 14:37:38 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		get_res(char *s, int p, t_minirt *m)
{
	if (m->scene.res == 1)
		ft_error(INVAL);
	m->scene.res = 1;
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
		ft_error(INVAL);
	m->scene.res_x = ft_atod(s, m, DOUBLE);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
		ft_error(INVAL);
	m->scene.res_y = ft_atod(s, m, DOUBLE);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
		ft_error(INVAL);
}

void		get_ambient_light(char *s, int p, t_minirt *m)
{
	check_alight(s, p, m);
	m->utils.i = p;
	m->scene.alight_r = ft_atod_loop(s, m, DOUBLE);
	m->scene.a_color = (t_color){ft_atod_loop(s, m, INT),
		ft_atod_loop(s, m, INT), ft_atod_loop(s, m, INT)};
}

t_cam		*get_camera(char *s, int p, t_minirt *m)
{
	t_cam	*cam;

	cam = (t_cam*)malloc(sizeof(t_cam));
	check_camera(s, p, m);
	m->scene.camera++;
	m->utils.i = p;
	cam->view_point.x = ft_atod_loop(s, m, DOUBLE);
	cam->view_point.y = ft_atod_loop(s, m, DOUBLE);
	cam->view_point.z = ft_atod_loop(s, m, DOUBLE);
	cam->norm_vec.x = ft_atod_loop(s, m, DOUBLE);
	cam->norm_vec.y = ft_atod_loop(s, m, DOUBLE);
	cam->norm_vec.z = ft_atod_loop(s, m, DOUBLE);
	cam->fov = ft_atod_loop(s, m, INT);
	return (cam);
}

t_light		*get_light(char *s, int p, t_minirt *m)
{
	t_light		*light;

	light = (t_light*)malloc(sizeof(t_light));
	check_light(s, p, m);
	m->utils.i = p;
	light->light_point.x = ft_atod_loop(s, m, DOUBLE);
	light->light_point.y = ft_atod_loop(s, m, DOUBLE);
	light->light_point.z = ft_atod_loop(s, m, DOUBLE);
	light->light_b = ft_atod_loop(s, m, DOUBLE);
	light->color = (t_color){ft_atod_loop(s, m, INT),
		ft_atod_loop(s, m, INT), ft_atod_loop(s, m, INT)};
	return (light);
}
