/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_library2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:22:16 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:22:17 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec_x_d(t_vec3 *v, double x)
{
	t_vec3 result;

	result = (t_vec3){v->x * x, v->y * x, v->z * x};
	return (result);
}

double	vec_pow(t_vec3 *v)
{
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}
