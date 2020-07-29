/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   images.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 21:09:16 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/29 22:22:52 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* 

typedef struct		s_img_list
{
	int				img_index;
	void			*img;
	char			*addr;
	void			*next;
}					t_img_list;	

LEFT AND RIGHT KEY HOOK
KEY: 123
KEY: 124

mlx_key_hook(minirt->var.win, close_key, minirt);

*/

void		create_images(t_minirt *minirt)
{
	int 	i;
	void	*temp_img;
	char	*temp_addr;

	i = 0;
	while (i < minirt->scene.camera)
	{
		temp_img = mlx_new_image(minirt->var.mlx, minirt->scene.res_x, minirt->scene.res_y);
		temp_addr = mlx_get_data_addr(temp_img, &minirt->var.bits_per_pixel, &minirt->var.line_length, &minirt->var.endian);
		add_img(&minirt->var.i_head, temp_img, temp_addr);
		i++;
	}
}