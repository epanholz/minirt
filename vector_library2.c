/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_library2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 17:33:53 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/22 17:34:15 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		vec_x_d(t_vec3 *v, double x)
{
	t_vec3 result;

	result = (t_vec3){v->x * x, v->y * x, v->z * x};
	return (result);
}

double	vec_pow(t_vec3 *v)
{
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}
