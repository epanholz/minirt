/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_objects.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:21 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:20:23 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pla		*get_plane(char *s, int p, t_minirt *m)
{
	t_pla *plane;

	plane = (t_pla*)malloc(sizeof(t_pla));
	check_plane(s, p, m);
	m->utils.i = p;
	plane->view_point.x = ft_atod_loop(s, m, DOUBLE);
	plane->view_point.y = ft_atod_loop(s, m, DOUBLE);
	plane->view_point.z = ft_atod_loop(s, m, DOUBLE);
	plane->norm_vec.x = ft_atod_loop(s, m, DOUBLE);
	plane->norm_vec.y = ft_atod_loop(s, m, DOUBLE);
	plane->norm_vec.z = ft_atod_loop(s, m, DOUBLE);
	plane->r = ft_atod_loop(s, m, INT);
	plane->g = ft_atod_loop(s, m, INT);
	plane->b = ft_atod_loop(s, m, INT);
	return (plane);
}

t_sph		*get_sphere(char *s, int p, t_minirt *m)
{
	t_sph *sphere;

	sphere = (t_sph*)malloc(sizeof(t_sph));
	check_sphere(s, p, m);
	m->utils.i = p;
	sphere->sp_center.x = ft_atod_loop(s, m, DOUBLE);
	sphere->sp_center.y = ft_atod_loop(s, m, DOUBLE);
	sphere->sp_center.z = ft_atod_loop(s, m, DOUBLE);
	sphere->diameter = ft_atod_loop(s, m, DOUBLE);
	sphere->r = ft_atod_loop(s, m, INT);
	sphere->g = ft_atod_loop(s, m, INT);
	sphere->b = ft_atod_loop(s, m, INT);
	return (sphere);
}

t_squ		*get_square(char *s, int p, t_minirt *m)
{
	t_squ *square;

	square = (t_squ*)malloc(sizeof(t_squ));
	check_square(s, p, m);
	m->utils.i = p;
	square->sq_center.x = ft_atod_loop(s, m, DOUBLE);
	square->sq_center.y = ft_atod_loop(s, m, DOUBLE);
	square->sq_center.z = ft_atod_loop(s, m, DOUBLE);
	square->norm_vec.x = ft_atod_loop(s, m, DOUBLE);
	square->norm_vec.y = ft_atod_loop(s, m, DOUBLE);
	square->norm_vec.z = ft_atod_loop(s, m, DOUBLE);
	square->side = ft_atod_loop(s, m, DOUBLE);
	square->r = ft_atod_loop(s, m, DOUBLE);
	square->g = ft_atod_loop(s, m, DOUBLE);
	square->b = ft_atod_loop(s, m, DOUBLE);
	return (square);
}

t_cyl		*get_cylinder(char *s, int p, t_minirt *minirt)
{
	t_cyl *cylinder;

	cylinder = (t_cyl*)malloc(sizeof(t_cyl));
	check_cylinder(s, p, minirt);
	minirt->utils.i = p;
	cylinder->center.x = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->center.y = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->center.z = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->norm_vec.x = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->norm_vec.y = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->norm_vec.z = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->diameter = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->height = ft_atod_loop(s, minirt, DOUBLE);
	cylinder->r = ft_atod_loop(s, minirt, INT);
	cylinder->g = ft_atod_loop(s, minirt, INT);
	cylinder->b = ft_atod_loop(s, minirt, INT);
	return (cylinder);
}

t_tri		*get_triangle(char *s, int p, t_minirt *minirt)
{
	t_tri	*triangle;

	triangle = (t_tri*)malloc(sizeof(t_tri));
	check_triangle(s, p, minirt);
	minirt->utils.i = p;
	triangle->p1.x = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p1.y = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p1.z = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p2.x = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p2.y = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p2.z = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p3.x = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p3.y = ft_atod_loop(s, minirt, DOUBLE);
	triangle->p3.z = ft_atod_loop(s, minirt, DOUBLE);
	triangle->r = ft_atod_loop(s, minirt, INT);
	triangle->g = ft_atod_loop(s, minirt, INT);
	triangle->b = ft_atod_loop(s, minirt, INT);
	return (triangle);
}
