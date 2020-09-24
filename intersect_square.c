/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_square.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 17:12:31 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/24 14:23:49 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_squ_utils		get_squ_utils(t_squ *square, t_matrix c2w)
{
	t_squ_utils	utils;

	utils.r = square->side / 2;
	utils.temp1 = vec_plus(&square->sq_center, &c2w.row2);
	utils.temp2 = vec_sub(&square->sq_center, &c2w.row2);
	utils.v0 = (t_vec3){c2w.row1.x - utils.r, c2w.row1.y + utils.r, c2w.row1.z};
	utils.v1 = (t_vec3){c2w.row2.x - utils.r, c2w.row2.y - utils.r, c2w.row2.z};
	utils.v2 = (t_vec3){c2w.row3.x + utils.r, c2w.row3.y - utils.r, c2w.row3.z};
	utils.v3 = (t_vec3){c2w.row4.x + utils.r, c2w.row4.y + utils.r, c2w.row4.z};
	utils.t1 = (t_tri){vec_sub(&utils.temp1, &c2w.row1),
					vec_plus(&utils.temp2, &c2w.row1),
					vec_sub(&utils.temp2, &c2w.row1),
					square->r, square->g, square->b};
	utils.t2 = (t_tri){vec_plus(&utils.temp1, &c2w.row1),
					utils.t1.p1, utils.t1.p2, square->r, square->g, square->b};
	return (utils);
}

t_hit					intersect_square(t_ray *ray, t_squ *square)
{
	t_hit		hit[2];
	t_squ_utils	utils;
	t_matrix	c2w;
	double		r;

	r = square->side / 2;
	hit[0] = init_hit();
	hit[0].col = (t_color){square->r, square->g, square->b};
	c2w = lookat_matrix(square->sq_center,
		vec_plus(&square->sq_center, &square->norm_vec));
	c2w = (t_matrix){vec_x_d(&c2w.row1, r),
		vec_x_d(&c2w.row2, r), c2w.row3, c2w.row4};
	utils = get_squ_utils(square, c2w);
	hit[1] = intersect_triangle(ray, &utils.t1);
	if (hit[1].hit == 1)
		return (hit[1]);
	hit[1] = intersect_triangle(ray, &utils.t2);
	if (hit[1].hit == 1)
		return (hit[1]);
	return (hit[0]);
}
