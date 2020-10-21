/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:12 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:20:13 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_camera(char *s, int p, t_minirt *m)
{
	int fov;

	fov = 0;
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_norm_vec(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
		ft_error(INVAL);
	fov = ft_atod(s, m, INT);
	if (fov > 180)
		ft_error(INVAL);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
		ft_error(INVAL);
}

void		check_alight(char *s, int p, t_minirt *m)
{
	double	brightness;

	if (m->scene.ambient_light == 1)
		ft_error(INVAL);
	m->scene.ambient_light = 1;
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
		ft_error(INVAL);
	brightness = ft_atod(s, m, DOUBLE);
	if (brightness > 1 || brightness < 0)
		ft_error(INVAL);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
		ft_error(INVAL);
}

void		check_light(char *s, int p, t_minirt *m)
{
	double brightness;

	brightness = 0;
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
		ft_error(INVAL);
	brightness = ft_atod(s, m, DOUBLE);
	if (brightness > 1 || brightness < 0)
		ft_error(INVAL);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
		ft_error(INVAL);
}
