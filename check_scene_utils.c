/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 16:51:35 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/10 11:02:46 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_atod_check(char *s, t_minirt *m, int mod)
{
	int i;

	i = 0;
	m->utils.sign = m->utils.i;
	if (s[i] == '-')
	{
		i++;
		m->utils.i++;
	}
	if (s[i] < '0' || s[i] > '9')
		ft_error(INVAL);
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '.' && mod == INT)
		ft_error(INVAL);
}

double		ft_atod(char *s, t_minirt *m, int mod)
{
	double	ret;
	double	x;
	int		j;

	ret = 0;
	x = 0;
	j = 0;
	ft_atod_check(s + m->utils.i, m, mod);
	while (s[m->utils.i] && s[m->utils.i] >= '0' && s[m->utils.i] <= '9')
	{
		ret = ret * 10 + s[m->utils.i] - '0';
		m->utils.i++;
	}
	if (s[m->utils.i] == '.')
	{
		m->utils.i++;
		while (s[m->utils.i] && s[m->utils.i] >= '0' && s[m->utils.i] <= '9')
		{
			x = x * 10 + s[m->utils.i] - '0';
			m->utils.i++;
			j++;
		}
		x = x * (pow(0.1, j));
	}
	return (s[m->utils.sign] == '-' ? -1 * (ret + x) : ret + x);
}

double		ft_atod_loop(char *s, t_minirt *m, int mod)
{
	double	ret;

	while ((s[m->utils.i] < '0' || s[m->utils.i] > '9')
		&& s[m->utils.i] != '-' && s[m->utils.i])
		m->utils.i++;
	ret = ft_atod(s, m, mod);
	return (ret);
}

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
