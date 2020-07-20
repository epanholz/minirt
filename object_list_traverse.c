/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list_traverse.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/01 12:43:17 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/20 20:34:38 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"	

t_sph		*return_sphere(t_minirt *minirt)
{
	t_sph			*sphere;
	t_object_list	*current;

	current = minirt->var.o_head;
		while (current)
	{
		if (current->object_type == SPH)
		{
			sphere = current->scene_object;
			remove_object_node(&minirt->var.o_head, SPH);
			return (sphere);
		}
		current = current->next;
	}
	return (NULL);
}
