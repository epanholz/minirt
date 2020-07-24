/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_library.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 12:21:15 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/24 21:56:04 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3  vec3(double x, double y, double z)
{
    t_vec3  ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return (ret);
}

t_vec3   vec_normalize(t_vec3 *vec3)
{
	t_vec3	temp;
	double length;

	length = sqrt(vec3->x * vec3->x + vec3->y * vec3->y + vec3->z * vec3->z);
	temp.x = vec3->x / length;
	temp.y = vec3->y / length;
	temp.z = vec3->z / length;
	return(temp);
}

t_vec3 vectorSub(t_vec3 *v1, t_vec3 *v2)
{
	return (vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

t_vec3 vectorPlus(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
    return (result);
}

t_vec3	crossProduct(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	new;

	new.x = v1->y * v2->z - v1->z * v2->y;
	new.y = v1->z * v2->x - v1->x * v2->z;
	new.z = v1->x * v2->y - v1->y * v2->x;
	return (new);
}

float vectorDot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3 vecFloat(t_vec3 *v, float x)
{
	t_vec3 result = {v->x * x, v->y * x, v->z * x};
	return (result);
}