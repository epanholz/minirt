/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/25 13:42:12 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		check_save(char *str)
{
	const char	cmp[6] = "--save";
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] != cmp[i])
			return (1);
		i++;
	}
	if (i <= 5)
		return (1);
	return (0);
}

static int		check_rt(char *str)
{
	const char	rt[3] = ".rt";
	int			len1;
	int			len2;

	len1 = ft_strlen(str) - 1;
	len2 = 2;
	while (len2)
	{
		if (str[len1] != rt[len2])
			return (1);
		len1--;
		len2--;
	}
	return (0);
}

static void		init_minirt(t_minirt *minirt)
{
	minirt->scene.res = 0;
	minirt->scene.save = 0;
	minirt->scene.ambient_light = 0;
	minirt->scene.camera = 0;
	minirt->list.c_head = NULL;
	minirt->list.o_head = NULL;
	minirt->list.i_head = NULL;
	minirt->list.l_head = NULL;
}

static void		delete_lists(t_minirt *minirt)
{
	delete_cam_list(&minirt->list.c_head);
	delete_object_list(&minirt->list.o_head);
	delete_light_list(&minirt->list.l_head);
	delete_img_list(&minirt->list.i_head);
}

int				main(int ac, char **av)
{
	t_minirt	*minirt;

	minirt = (t_minirt*)malloc(sizeof(t_minirt));
	init_minirt(minirt);
	if (ac == 3 || ac == 2)
	{
		if (ac == 3)
		{
			if (check_save(av[2]) == 1)
				ft_error(ARG);
			minirt->scene.save = 1;
			ft_save();
		}
		if (check_rt(av[1]) == 1)
			ft_error(RT);
		check_scene(av[1], minirt);
	}
	else
		ft_error(INPUT);
	delete_lists(minirt);
	free(minirt);
	exit(0);
}
