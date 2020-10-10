/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:21:29 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:21:32 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix				lookat_matrix(t_vec3 from, t_vec3 to)
{
	t_matrix	cam2world;
	t_vec3		norm_vec;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;

	norm_vec = vec_sub(&to, &from);
	norm_vec = vec_normalize(&norm_vec);
	if (norm_vec.x == 0.0 && norm_vec.z == 0.0 && fabs(norm_vec.y) == 1.0)
	{
		cam2world.row1 = norm_vec.y == 1.0 ? (t_vec3){1.0, 0.0, 0.0} :
			(t_vec3){0.0, 0.0, 1.0};
		cam2world.row2 = norm_vec.y == 1.0 ? (t_vec3){0.0, 0.0, 1.0} :
			(t_vec3){1.0, 0.0, 0.0};
		cam2world.row3 = norm_vec.y == 1.0 ? (t_vec3){0.0, 1.0, 0.0} :
			(t_vec3){0.0, -1.0, 0.0};
		return (cam2world);
	}
	forward = vec_sub(&from, &to);
	forward = vec_normalize(&forward);
	right = cross_prod(&(t_vec3){0, 1, 0}, &forward);
	up = cross_prod(&forward, &right);
	cam2world = (t_matrix){right, up, forward, (t_vec3){0, 0, 0}};
	return (cam2world);
}

t_vec3					apply_matrix(t_matrix matrix, t_vec3 vec3)
{
	t_vec3	new;

	new.x = vec3.x * matrix.row1.x + vec3.y * matrix.row2.x
		+ vec3.z * matrix.row3.x;
	new.y = vec3.x * matrix.row1.y + vec3.y * matrix.row2.y
		+ vec3.z * matrix.row3.y;
	new.z = vec3.x * matrix.row1.z + vec3.y * matrix.row2.z
		+ vec3.z * matrix.row3.z;
	return (new);
}

t_vec3					setcam(t_vec3 from, t_vec3 to, t_vec3 norm_vec)
{
	t_matrix	c2w;

	if (norm_vec.x == 0 && norm_vec.y == 0 && norm_vec.z == 0)
		return (from);
	c2w = lookat_matrix(to, vec_plus(&to, &norm_vec));
	return (apply_matrix(c2w, from));
}
