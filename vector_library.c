/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_library.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 12:21:15 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/20 22:35:05 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3  vec3(int x, int y, int z)
{
    t_vec3  ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return (ret);
}

t_vec3   vec_normalize(t_vec3 *vec3)
{
	float N;

	N = sqrt(vectorDot(vec3, vec3));
	t_vec3 result = {vec3->x / N, vec3->y / N, vec3->z / N};
    return(result);
}

t_vec3 vectorSub(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return (result);
}

t_vec3 vectorPlus(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 result = {v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
    return (result);
}

t_vec3	crossProduct(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	result = {v1->y * v2->z - v1->z * v2->y, v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x};
	return (result);
}

float vectorDot(t_vec3 *v1, t_vec3 *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

