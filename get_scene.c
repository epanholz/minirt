/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 17:58:22 by epanholz      #+#    #+#                 */
/*   Updated: 2020/05/31 19:50:54 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"		

void		ft_error(int mod)
{
	if (mod == INVAL)
		write(1, "Error\nInvalid map!", 19);
	if (mod == MALLOC)
		write(1, "Error\nMalloc failed!", 21);
	if (mod == READ)
		write(1, "Error\nRead failed!", 19);
	exit(1);
}

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
	m->scene.r1 = ft_atod(s, m, INT);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
			ft_error(INVAL);
	m->scene.r2 = ft_atod(s, m, INT);
	while (s[m->utils.i] && s[m->utils.i] == ' ')
		m->utils.i++;
	if (s[m->utils.i] != '\n' && s[m->utils.i] != '\0')
			ft_error(INVAL);
}

t_alight	*get_ambient_light(char *s, int p, t_minirt *m)
{
	t_alight	*alight;

	alight = (t_alight*)malloc(sizeof(t_alight));

	check_alight(s, p, m);
	m->utils.i = p;

	alight->light_b = ft_atod_loop(s, m, FLOAT);
	alight->r= ft_atod_loop(s, m, INT);
	alight->b= ft_atod_loop(s, m, INT);
	alight->g= ft_atod_loop(s, m, INT);
	
	printf("%0.1f, %d, %d, %d ", alight->light_b, alight->r, alight->b, alight->g);
	return(alight);
}

t_cam		*get_camera(char *s, int p, t_minirt *m)
{
	t_cam	*cam;

	cam = (t_cam*)malloc(sizeof(t_cam));
	check_camera(s, p, m);
	m->utils.i = p;

	cam->view_point.x = ft_atod_loop(s, m, FLOAT);
	cam->view_point.y = ft_atod_loop(s, m, FLOAT);
	cam->view_point.z = ft_atod_loop(s, m, FLOAT);
	cam->norm_vec.x = ft_atod_loop(s, m, FLOAT);
	cam->norm_vec.y = ft_atod_loop(s, m, FLOAT);
	cam->norm_vec.z = ft_atod_loop(s, m, FLOAT);
	cam->fov = ft_atod_loop(s, m, INT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d ", cam->view_point.x, cam->view_point.y, cam->view_point.z, cam->norm_vec.x, cam->norm_vec.y, cam->norm_vec.z, cam->fov);
	return(cam);
}

t_light		*get_light(char *s, int p, t_minirt *m)
{
	t_light		*light;

	light = (t_light*)malloc(sizeof(t_light));
	check_light(s, p, m);
	m->utils.i = p;

	light->light_point.x = ft_atod_loop(s, m, FLOAT);
	light->light_point.y = ft_atod_loop(s, m, FLOAT);
	light->light_point.z = ft_atod_loop(s, m, FLOAT);
	light->light_b = ft_atod_loop(s, m, FLOAT);
	light->r = ft_atod_loop(s, m, INT);
	light->g = ft_atod_loop(s, m, INT);
	light->b = ft_atod_loop(s, m, INT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d ", light->light_point.x, light->light_point.y, light->light_point.z, light->light_b, light->r, light->g, light->b);
	return(light);
}

t_pla		*get_plane(char *s, int p, t_minirt *m)
{
	t_pla *plane;

	plane = (t_pla*)malloc(sizeof(t_pla));
	check_plane(s, p, m);
	m->utils.i = p;

	plane->view_point.x = ft_atod_loop(s, m, FLOAT);
	plane->view_point.y = ft_atod_loop(s, m, FLOAT);
	plane->view_point.z = ft_atod_loop(s, m, FLOAT);
	plane->norm_vec.x = ft_atod_loop(s, m, FLOAT);
	plane->norm_vec.y = ft_atod_loop(s, m, FLOAT);
	plane->norm_vec.z = ft_atod_loop(s, m, FLOAT);
	plane->r = ft_atod_loop(s, m, INT);
	plane->g = ft_atod_loop(s, m, INT);
	plane->b = ft_atod_loop(s, m, INT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d ", plane->view_point.x, plane->view_point.y, plane->view_point.z, plane->norm_vec.x, plane->norm_vec.y, plane->norm_vec.z, plane->r, plane->g, plane->b);
	return(plane);
}

t_sph		*get_sphere(char *s, int p, t_minirt *m)
{
	t_sph *sphere;

	sphere = (t_sph*)malloc(sizeof(t_sph));
	check_sphere(s, p, m);
	m->utils.i = p;

	sphere->sp_center.x = ft_atod_loop(s, m, FLOAT);
	sphere->sp_center.y = ft_atod_loop(s, m, FLOAT);	
	sphere->sp_center.z = ft_atod_loop(s, m, FLOAT);
	sphere->diameter = ft_atod_loop(s, m, FLOAT);
	sphere->r = ft_atod_loop(s, m, INT);
	sphere->g = ft_atod_loop(s, m, INT);
	sphere->b = ft_atod_loop(s, m, INT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d ", sphere->sp_center.x, sphere->sp_center.y, sphere->sp_center.z, sphere->diameter, sphere->r, sphere->g, sphere->b);

	return(sphere);
}


t_squ		*get_square(char *s, int p, t_minirt *m)
{
	t_squ *square;

	square = (t_squ*)malloc(sizeof(t_squ));
	check_square(s, p, m);
	m->utils.i = p;

	// 7 floating points and rgb
	square->sq_center.x = ft_atod_loop(s, m, FLOAT);
	square->sq_center.y = ft_atod_loop(s, m, FLOAT);
	square->sq_center.z = ft_atod_loop(s, m, FLOAT);
	square->norm_vec.x = ft_atod_loop(s, m, FLOAT);
	square->norm_vec.y = ft_atod_loop(s, m, FLOAT);
	square->norm_vec.z = ft_atod_loop(s, m, FLOAT);
	square->side = ft_atod_loop(s, m, FLOAT);
	square->r = ft_atod_loop(s, m, FLOAT);
	square->g = ft_atod_loop(s, m, FLOAT);
	square->b = ft_atod_loop(s, m, FLOAT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d ", square->sq_center.x, square->sq_center.y, square->sq_center.z, square->norm_vec.x, square->norm_vec.y, square->norm_vec.z, square->side, square->r, square->g, square->b);

	return(square);
}

t_cyl		*get_cylinder(char *s, int p, t_minirt *minirt)
{
	t_cyl *cylinder;

	cylinder = (t_cyl*)malloc(sizeof(t_cyl));
	check_cylinder(s, p, minirt);
	minirt->utils.i = p;

	// 8 floating points and rgb
	cylinder->view_point.x = ft_atod_loop(s, minirt, FLOAT);
	cylinder->view_point.y = ft_atod_loop(s, minirt, FLOAT);
	cylinder->view_point.z = ft_atod_loop(s, minirt, FLOAT);
	cylinder->norm_vec.x = ft_atod_loop(s, minirt, FLOAT);
	cylinder->norm_vec.y = ft_atod_loop(s, minirt, FLOAT);
	cylinder->norm_vec.z = ft_atod_loop(s, minirt, FLOAT);
	cylinder->diameter = ft_atod_loop(s, minirt, FLOAT);
	cylinder->height = ft_atod_loop(s, minirt, FLOAT);
	cylinder->r = ft_atod_loop(s, minirt, INT);
	cylinder->g = ft_atod_loop(s, minirt, INT);
	cylinder->b = ft_atod_loop(s, minirt, INT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d ", cylinder->view_point.x, cylinder->view_point.y, cylinder->view_point.z, cylinder->norm_vec.x , cylinder->norm_vec.y, cylinder->norm_vec.z, cylinder->diameter, cylinder->height,  cylinder->r, cylinder->g, cylinder->b);

	return(cylinder);
}

t_tri		*get_triangle(char *s, int p, t_minirt *minirt)
{
	t_tri	*triangle;

	triangle = (t_tri*)malloc(sizeof(t_tri));
	check_triangle(s, p, minirt);
	minirt->utils.i = p;

	// 9 floating points and rgb
	triangle->p1.x = ft_atod_loop(s, minirt, FLOAT);
	triangle->p1.y = ft_atod_loop(s, minirt, FLOAT);
	triangle->p1.z = ft_atod_loop(s, minirt, FLOAT);
	triangle->p2.x = ft_atod_loop(s, minirt, FLOAT);
	triangle->p2.y = ft_atod_loop(s, minirt, FLOAT);
	triangle->p2.z = ft_atod_loop(s, minirt, FLOAT);
	triangle->p3.x = ft_atod_loop(s, minirt, FLOAT);
	triangle->p3.y = ft_atod_loop(s, minirt, FLOAT);
	triangle->p3.z = ft_atod_loop(s, minirt, FLOAT);
	triangle->r = ft_atod_loop(s, minirt, INT);
	triangle->g = ft_atod_loop(s, minirt, INT);
	triangle->b = ft_atod_loop(s, minirt, INT);

	printf("%0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d ", triangle->p1.x, triangle->p1.y, triangle->p1.z, triangle->p2.x, triangle->p2.y, triangle->p2.z, triangle->p3.x, triangle->p3.y, triangle->p3.z, triangle->r, triangle->g, triangle->b); 

	return(triangle);
}
	

void		check_arg(char *arg, int p, t_minirt *minirt, t_object_list **head)
{
	// (void)head;

	if (arg[p] == 'R' && arg[p + 1] == ' ')
		get_res(arg, p + 1, minirt);
		
	// else if (arg[p] == 'A' && arg[p + 1] == ' ')
	// 	get_ambient_light(arg, p + 1, minirt);
	// else if (arg[p] == 'c' && arg[p + 1] == ' ')
	// 	get_camera(arg, p + 1, minirt);
	// else if (arg[p] == 'l')
	// 	get_light(arg, p + 1, minirt);
	// else if (arg[p] == 'p' && arg[p + 1] == 'l')
	// 	get_plane(arg, p + 2, minirt);
	// else if (arg[p] == 's' && arg[p + 1] == 'p')
	// 	get_sphere(arg, p + 2, minirt);
	// else if (arg[p] == 's' && arg[p + 1] == 'q')
	// 	get_square(arg, p + 2, minirt);
	//lse if (arg[p] == 's' && arg[p + 1] == 'q')
	//	get_square(arg, p + 2, minirt);
	//else if (arg[p] == 't' && arg[p + 1] == 'r')
	//	get_triangle(arg, p + 2, minirt);


	else if (arg[p] == 'A' && arg[p + 1] == ' ')
		add_object(head, ALIGHT, get_ambient_light(arg, p + 1, minirt));
	else if (arg[p] == 'c' && arg[p + 1] == ' ')
		add_object(head, CAM, get_camera(arg, p + 1, minirt));
	else if (arg[p] == 'l')
		add_object(head, LIGHT, get_light(arg, p + 1, minirt));
	else if (arg[p] == 'p' && arg[p + 1] == 'l')
		add_object(head, PLA, get_plane(arg, p + 2, minirt));
	else if (arg[p] == 's' && arg[p + 1] == 'p')
		add_object(head, SPH, get_sphere(arg, p + 2, minirt));
	else if (arg[p] == 's' && arg[p + 1] == 'q')
		add_object(head, SQU, get_square(arg, p + 2, minirt));
	else if (arg[p] == 'c' && arg[p + 1] == 'y')
		add_object(head, CYL, get_cylinder(arg, p + 2, minirt));
	else if (arg[p] == 't' && arg[p + 1] == 'r')
		add_object(head, TRI, get_triangle(arg, p + 2, minirt));
	else
		ft_error(INVAL);
}

void		check_map(char *map, t_minirt *minirt)
{
	int				index;
	t_object_list 	*head;

	head = NULL;
	index = 0;
	make_head(&head);
	while (map[index])
	{
		check_arg(map, index, minirt, &head);
		while (map[index] && map[index] != '\n')
			index++;
		while (map[index] && map[index] == '\n')
			index++;
		minirt->utils.i = 0;
	}
}