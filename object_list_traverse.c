/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list_traverse.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/01 12:43:17 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/22 21:10:48 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"	

t_sph		*return_sphere(t_minirt *minirt)
{
	t_sph			*sphere;
	t_object_list	*current;

	sphere = (t_sph*)malloc(sizeof(t_sph));
	sphere = NULL;
	current = minirt->var.o_head;
	while (current)
	{
		if (current->object_type == SPH)
		{
			sphere = current->scene_object;
			//remove_object_node(&minirt->var.o_head, SPH);
			return (sphere);
		}
		current = current->next;
	}
	return (NULL);
}

t_cam		*return_cam(t_minirt *minirt, int index)
{
	t_cam			*cam;
	t_camera_list	*current;

	current = minirt->var.c_head;
	while (current)
	{
		if (current->cam_index == index)
		{
			cam = current->cam;
			return (cam);
		}
		current = current->next;
	}
	return (NULL);
}