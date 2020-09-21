/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scene_loop.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:38:58 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/21 14:16:33 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_arg(char *arg, int p, t_minirt *minirt)
{
	if (arg[p] == 'R' && arg[p + 1] == ' ')
		get_res(arg, p + 1, minirt);
	else if (arg[p] == 'A' && arg[p + 1] == ' ')
		get_ambient_light(arg, p + 1, minirt);
	else if (arg[p] == 'c' && arg[p + 1] == ' ')
		add_camera(&minirt->var.c_head, get_camera(arg, p + 1, minirt));
	else if (arg[p] == 'l' && arg[p + 1] == ' ')
		add_light(&minirt->var.l_head, get_light(arg, p + 1, minirt));
	else if (arg[p] == 'p' && arg[p + 1] == 'l' && arg[p + 2] == ' ')
		add_object(&minirt->var.o_head, PLA, get_plane(arg, p + 2, minirt));
	else if (arg[p] == 's' && arg[p + 1] == 'p' && arg[p + 2] == ' ')
		add_object(&minirt->var.o_head, SPH, get_sphere(arg, p + 2, minirt));
	else if (arg[p] == 's' && arg[p + 1] == 'q' && arg[p + 2] == ' ')
		add_object(&minirt->var.o_head, SQU, get_square(arg, p + 2, minirt));
	else if (arg[p] == 'c' && arg[p + 1] == 'y' && arg[p + 2] == ' ')
		add_object(&minirt->var.o_head, CYL, get_cylinder(arg, p + 2, minirt));
	else if (arg[p] == 't' && arg[p + 1] == 'r' && arg[p + 2] == ' ')
		add_object(&minirt->var.o_head, TRI, get_triangle(arg, p + 2, minirt));
	else
		ft_error(INVAL);
}

void		check_map(char *map, t_minirt *minirt)
{
	int				index;

	index = 0;
	make_cam_head(&minirt->var.c_head);
	make_obj_head(&minirt->var.o_head);
	make_img_head(&minirt->var.i_head);
	make_light_head(&minirt->var.l_head);
	while (map[index])
	{
		check_arg(map, index, minirt);
		while (map[index] && map[index] != '\n')
			index++;
		while (map[index] && map[index] == '\n')
			index++;
		minirt->utils.i = 0;
	}
	if (minirt->scene.camera == 0 || minirt->scene.ambient_light == 0 ||
		minirt->scene.res == 0)
		ft_error(INVAL);
	make_scene(minirt);
}
