/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:28:53 by epanholz      #+#    #+#                 */
/*   Updated: 2020/09/21 15:19:31 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_save(char *str)
{
	const char	cmp[] = "--save";
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
			{
				printf("Error\nWrong second argument!\n");
				return (0);
			}
			minirt->scene.save = 1;
			printf("\nsaving ..\n\n");
		}
		fd = open(av[1], O_RDONLY);
		buff = read_file(fd, buff);
		check_map(buff, minirt);
	}
	else
		printf("\nError\nWrong input duh ..\n\n");
	delete_cam_list(&minirt->var.c_head);	
	delete_object_list(&minirt->var.o_head);
	delete_light_list(&minirt->var.l_head);
	delete_img_list(&minirt->var.i_head);
	free(minirt);
	system("leaks minirt");
	exit(0);
}
