/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_library.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 12:21:15 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/21 15:52:33 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		vec_normalize(t_vec3 *vec3)
{
	t_vec3	temp;
	double	length;

	length = sqrt(vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
	temp = (t_vec3){vec3->x / length, vec3->y / length, vec3->z / length};
	return (temp);
}

t_vec3		vec_sub(t_vec3 *v1, t_vec3 *v2)
{
	return ((t_vec3){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z});
}

t_vec3		vec_plus(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 result;

	result = (t_vec3){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
	return (result);
}

t_vec3		cross_prod(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	new;

	new.x = v1->y * v2->z - v1->z * v2->y;
	new.y = v1->z * v2->x - v1->x * v2->z;
	new.z = v1->x * v2->y - v1->y * v2->x;
	return (new);
}

double		vec_dot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

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
