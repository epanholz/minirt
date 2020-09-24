/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 14:40:21 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/24 15:10:01 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		render(t_minirt *minirt, t_ray *ray)
{
	t_hit	hit;

	hit = find_hit(minirt, ray);
	if (hit.hit == 1)
	{
		calc_color(minirt, &hit);
		my_mlx_pixel_put(minirt, ray->u.pixx, ray->u.pixy,
			rgbt(0, hit.col.r, hit.col.g, hit.col.b));
	}
	else
		my_mlx_pixel_put(minirt, ray->u.pixx, ray->u.pixy,
			rgbt(0, 0, 0, 0));
}

static void		shoot_ray(t_minirt *minirt, t_ray *ray, t_cam *cam)
{
	while (ray->u.pixy < minirt->scene.res_y)
	{
		ray->u.camy = (1 - 2 * ((ray->u.pixy + 0.5) / minirt->scene.res_y)) *
			tan(cam->fov / 2 * M_PI / 180);
		while (ray->u.pixx < minirt->scene.res_x)
		{
			ray->u.camx = (2 * ((ray->u.pixx + 0.5) / minirt->scene.res_x) - 1)
				* tan(cam->fov / 2 * M_PI / 180) * ray->u.asp_rat;
			ray->dir = (t_vec3){ray->u.camx, ray->u.camy, -1};
			ray->dir = vec_normalize(&ray->dir);
			ray->dir = setcam(ray->dir, cam->view_point, cam->norm_vec);
			ray->dir = vec_normalize(&ray->dir);
			render(minirt, ray);
			ray->u.pixx++;
		}
		ray->u.pixx = 0;
		ray->u.pixy++;
	}
}

static void		generate_ray(t_minirt *minirt)
{
	t_cam			*cam;
	t_ray			*ray;
	t_img_list		*current;

	current = minirt->var.i_head;
	ray = (t_ray*)malloc(sizeof(t_ray));
	if (ray == NULL)
		ft_error(MALLOC);
	ray->u.asp_rat = minirt->scene.res_x / minirt->scene.res_y;
	while (current)
	{
		ray->u.pixx = 0;
		ray->u.pixy = 0;
		ray->u.camy = 0;
		ray->u.camx = 0;
		cam = return_cam(minirt, current->img_index);
		ray->orig = cam->view_point;
		minirt->var.img = current->img;
		minirt->var.addr = current->addr;
		shoot_ray(minirt, ray, cam);
		current = current->next;
	}
	free(ray);
}

void			make_scene(t_minirt *minirt)
{
	t_img_list	*current;
	int			x;
	int			y;

	x = minirt->scene.res_x;
	y = minirt->scene.res_y;
	minirt->var.mlx = mlx_init();
	mlx_get_screen_size(minirt->var.mlx, &x, &y);
	minirt->scene.res_x = (minirt->scene.res_x > x) ? x : minirt->scene.res_x;
	minirt->scene.res_y = (minirt->scene.res_y > y) ? y : minirt->scene.res_y;
	create_images(minirt);
	generate_ray(minirt);
	current = minirt->var.i_head;
	if (minirt->scene.save == 1)
		write_bitmap(minirt, current->addr);
	else
	{
		minirt->var.win = mlx_new_window(minirt->var.mlx, minirt->scene.res_x,
			minirt->scene.res_y, "Scene Window");
		mlx_put_image_to_window(minirt->var.mlx, minirt->var.win,
			current->img, 0, 0);
		mlx_hook(minirt->var.win, 17, 0, close_button, minirt);
		mlx_key_hook(minirt->var.win, key_hook, minirt);
		mlx_loop(minirt->var.mlx);
	}
}
