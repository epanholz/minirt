/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 16:51:35 by epanholz      #+#    #+#                 */
/*   Updated: 2020/06/18 13:12:32 by epanholz      ########   odam.nl         */
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
	if (m->scene.ambient_light == 1)
		ft_error(INVAL);
	m->scene.ambient_light = 1;
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
			ft_error(INVAL);
	if ((s[m->utils.i] == '0' || s[m->utils.i] == '1') && s[m->utils.i + 1] == '.' && 
		s[m->utils.i + 2] >='0' && s[m->utils.i + 2] <= '9')
		m->utils.i = m->utils.i + 3;
	else
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
	brightness = ft_atod(s, m, FLOAT);
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

void		check_plane(char *s, int p, t_minirt *m)
{
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_norm_vec(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
			ft_error(INVAL);
}

void		check_sphere(char *s, int p, t_minirt *m)
{
	double diameter;

	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	diameter = ft_atod(s, m, FLOAT);
	if (diameter < 0)
		ft_error(INVAL);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
			ft_error(INVAL);
}


void		check_square(char *s, int p, t_minirt *m)
{
	double side;

	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_norm_vec(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	side = ft_atod(s, m, FLOAT);
	if (side < 0)
		ft_error(INVAL);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
			ft_error(INVAL);
}

void		check_cylinder(char *s, int p, t_minirt *m)
{
	double	diameter;
	double	height;

	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_norm_vec(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	diameter = ft_atod(s, m, FLOAT);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	height = ft_atod(s, m, FLOAT);
	if (height < 0 || diameter < 0)
		ft_error(INVAL);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
			ft_error(INVAL);
}

void		check_triangle(char *s, int p, t_minirt *m)
{
	m->utils.i = p;
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_xyz_point(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	check_rgb(s, m);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
			ft_error(INVAL);
}