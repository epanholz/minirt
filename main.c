/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/22 12:26:45 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_save(char *str)
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

int		check_rt(char *str)
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

void	init_minirt(t_minirt *minirt)
{
	minirt->scene.res = 0;
	minirt->scene.save = 0;
	minirt->scene.ambient_light = 0;
	minirt->scene.camera = 0;
	minirt->var.c_head = NULL;
	minirt->var.o_head = NULL;
	minirt->var.i_head = NULL;
	minirt->var.l_head = NULL;
}

int		main(int ac, char **av)
{
	t_minirt	*minirt;
	int			fd;
	char		*buff;

	minirt = (t_minirt*)malloc(sizeof(t_minirt));
	init_minirt(minirt);
	buff = NULL;
	if (ac == 3 || ac == 2)
	{
		if (ac == 3)
		{
			if (check_save(av[2]) == 1)
				ft_error(ARG);
			minirt->scene.save = 1;
			write(1, "\n𝚜𝚊𝚟𝚒𝚗𝚐 𝚋𝚒𝚝𝚖𝚊𝚙 ..\n\n", 56);
		}
		if (check_rt(av[1]) == 1)
			ft_error(RT);
		fd = open(av[1], O_RDONLY);
		buff = read_file(fd, buff);
		check_map(buff, minirt);
	}
	else
		ft_error(INPUT);
	delete_cam_list(&minirt->var.c_head);
	delete_object_list(&minirt->var.o_head);
	delete_light_list(&minirt->var.l_head);
	delete_img_list(&minirt->var.i_head);
	free(minirt);
	exit(0);
}
