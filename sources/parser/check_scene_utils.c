/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:20:06 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/10 18:20:08 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_rgb(char *s, t_minirt *m)
{
	int rbg;

	rbg = 0;
	rbg = ft_atod(s, m, INT);
	if (rbg > 255 || rbg < 0)
		ft_error(INVAL);
	s[m->utils.i] == ',' ? m->utils.i++ : ft_error(INVAL);
	rbg = ft_atod(s, m, INT);
	if (rbg > 255 || rbg < 0)
		ft_error(INVAL);
	s[m->utils.i] == ',' ? m->utils.i++ : ft_error(INVAL);
	rbg = ft_atod(s, m, INT);
	if (rbg > 255 || rbg < 0)
		ft_error(INVAL);
}

void		check_xyz_point(char *s, t_minirt *m)
{
	double check;

	check = 0;
	check = ft_atod(s, m, DOUBLE);
	s[m->utils.i] == ',' ? m->utils.i++ : ft_error(INVAL);
	check = ft_atod(s, m, DOUBLE);
	s[m->utils.i] == ',' ? m->utils.i++ : ft_error(INVAL);
	check = ft_atod(s, m, DOUBLE);
}

void		check_norm_vec(char *s, t_minirt *m)
{
	double check;

	check = 0;
	check = ft_atod(s, m, DOUBLE);
	if (check > 1 || check < -1)
		ft_error(INVAL);
	s[m->utils.i] == ',' ? m->utils.i++ : ft_error(INVAL);
	check = ft_atod(s, m, DOUBLE);
	if (check > 1 || check < -1)
		ft_error(INVAL);
	s[m->utils.i] == ',' ? m->utils.i++ : ft_error(INVAL);
	check = ft_atod(s, m, DOUBLE);
	if (check > 1 || check < -1)
		ft_error(INVAL);
}
