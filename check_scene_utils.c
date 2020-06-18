/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_scene_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 16:51:35 by epanholz      #+#    #+#                 */
/*   Updated: 2020/05/31 18:48:07 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ft_atod(char *s, t_minirt *m, int mod)
{
	double	ret;
	double	x;
	int 	j;

	m->utils.sign = 1;
	ret = 0;
	x = 0;
	j = 0;
	if (s[m->utils.i] == '-')
	{
		m->utils.i++;
		m->utils.sign = -1;	
	}
	while (s[m->utils.i] && s[m->utils.i] >= '0' && s[m->utils.i] <= '9')
	{
		ret = ret * 10 + s[m->utils.i] - '0';
		m->utils.i++;
	}
	if (s[m->utils.i] == '.')
	{	
		if (mod == INT)
			ft_error(INVAL);
		m->utils.i++;
		while (s[m->utils.i] && s[m->utils.i] >= '0' && s[m->utils.i] <= '9')
		{
			x = x * 10 + s[m->utils.i] - '0';
			m->utils.i++;
			j++;
		}
		x = x * (pow(0.1, j));
	}
	return (m->utils.sign * (ret + x));
}

double		ft_atod_loop(char *s, t_minirt *m, int mod)
{
	double	ret;
	double	x;
	int 	j;

	m->utils.sign = 1;
	ret = 0;
	x = 0;
	j = 0;
	while ((s[m->utils.i] < '0' || s[m->utils.i] > '9') && s[m->utils.i] != '-' && s[m->utils.i])
		m->utils.i++;
	if (s[m->utils.i] == '-')
	{
		m->utils.i++;
		m->utils.sign = -1;	
	}
	while (s[m->utils.i] && s[m->utils.i] >= '0' && s[m->utils.i] <= '9')
	{
		ret = ret * 10 + s[m->utils.i] - '0';
		m->utils.i++;
	}
	if (s[m->utils.i] == '.')
	{	
		if (mod == INT)
			ft_error(INVAL);
		m->utils.i++;
		while (s[m->utils.i] && s[m->utils.i] >= '0' && s[m->utils.i] <= '9')
		{
			x = x * 10 + s[m->utils.i] - '0';
			m->utils.i++;
			j++;
		}
		x = x * (pow(0.1, j));
	}
	return (m->utils.sign * (ret + x));
}


void		check_rgb(char *s, t_minirt *m)
{
	int rbg;

	rbg = 0;
	if (s[m->utils.i] < '0' || s[m->utils.i] > '9')
		ft_error(INVAL);
	rbg = ft_atod(s, m, INT);
	if (rbg > 255 || rbg < 0)
		ft_error(INVAL);
	if (s[m->utils.i] == ',')
		m->utils.i++;
	else
		ft_error(INVAL);
	rbg = ft_atod(s, m, INT);
	if (rbg > 255 || rbg < 0)
		ft_error(INVAL);
	if (s[m->utils.i] == ',')
		m->utils.i++;
	else
		ft_error(INVAL);
	rbg = ft_atod(s, m, INT);
	if (rbg > 255 || rbg < 0)
		ft_error(INVAL);
}

void		check_xyz_point(char *s, t_minirt *m)
{
	double check;

	check = 0;
	if (s[m->utils.i] != '-' && (s[m->utils.i] < '0' || s[m->utils.i] > '9'))
		ft_error(INVAL);
	check = ft_atod(s, m, FLOAT);
	if (s[m->utils.i] == ',')
		m->utils.i++;
	else
		ft_error(INVAL);
	check = ft_atod(s, m, FLOAT);
	if (s[m->utils.i] == ',')
		m->utils.i++;
	else
		ft_error(INVAL);
	check = ft_atod(s, m, FLOAT);
}

void		check_norm_vec(char *s, t_minirt *m)
{
	double check;

	check = 0;
	if (s[m->utils.i] != '-' && (s[m->utils.i] < '0' || s[m->utils.i] > '9'))
		ft_error(INVAL);
	check = ft_atod(s, m, FLOAT);
	if (check > 1 || check < -1)
		ft_error(INVAL);
	if (s[m->utils.i] == ',')
		m->utils.i++;
	else
		ft_error(INVAL);
	check = ft_atod(s, m, FLOAT);
	if (check > 1 || check < -1)
		ft_error(INVAL);
	if (s[m->utils.i] == ',')
		m->utils.i++;
	else
		ft_error(INVAL);
	check = ft_atod(s, m, FLOAT);
	if (check > 1 || check < -1)
		ft_error(INVAL);
}