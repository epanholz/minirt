/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_loop.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 20:34:47 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/25 13:42:50 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_lookup	g_lookup_table[] = {
	{SPH, &intersect_sphere},
	{TRI, &intersect_triangle},
	{PLA, &intersect_plane},
	{SQU, &intersect_square},
	{CYL, &intersect_cylinder}
};

t_hit					init_hit(void)
{
	t_hit	hit;

	hit.object = 0;
	hit.hit = -1;
	hit.t1 = INFINITY;
	hit.t2 = INFINITY;
	hit.surface_norm = (t_vec3){0, 0, 0};
	hit.hit_p = (t_vec3){0, 0, 0};
	hit.col = (t_color){0, 0, 0};
	return (hit);
}

void					find_hit_light(t_minirt *minirt, t_ray *ray,
										double l, t_hit *hit_p)
{
	t_hit			hit[2];
	t_object_list	*current;
	int				i;
	t_function		*func;

	hit[0] = init_hit();
	i = 0;
	current = minirt->list.o_head;
	while (current)
	{
		while (i < 5)
		{
			if (g_lookup_table[i].index == current->object_type)
			{
				func = g_lookup_table[i].func;
				hit[1] = (*func)(ray, current->scene_object);
				if (hit[1].hit == 1 && (hit[1].t1 < l && hit[1].t1 > 0))
					return ;
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	hit_p->hit = 0;
}

t_hit					find_hit(t_minirt *minirt, t_ray *ray)
{
	t_hit			hit[2];
	t_object_list	*current;
	int				i;
	t_function		*func;

	hit[0] = init_hit();
	i = 0;
	current = minirt->list.o_head;
	while (current)
	{
		while (i < 5)
		{
			if (g_lookup_table[i].index == current->object_type)
			{
				func = g_lookup_table[i].func;
				hit[1] = (*func)(ray, current->scene_object);
				if (hit[1].hit == 1 && hit[1].t1 < hit[0].t1)
					hit[0] = hit[1];
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	return (hit[0]);
}
