/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:21:59 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/19 19:53:41 by epanholz      ########   odam.nl         */
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

	current = minirt->list.i_head;
	ray = (t_ray*)malloc(sizeof(t_ray));
	if (ray == NULL)
		ft_error(MALLOC);
	ray->u.asp_rat = (double)minirt->scene.res_x / (double)minirt->scene.res_y;
	while (current)
	{
		ray->u.pixx = 0;
		ray->u.pixy = 0;
		ray->u.camy = 0;
		ray->u.camx = 0;
		cam = return_cam(minirt, current->img_index);
		ray->orig = cam->view_point;
		minirt->mlx.img = current->img;
		minirt->mlx.addr = current->addr;
		shoot_ray(minirt, ray, cam);
		current = current->next;
	}
	free(ray);
}

static void		res_resize(t_minirt *m)
{
	int			x;
	int			y;

	x = m->scene.res_x;
	y = m->scene.res_y;
	if (m->scene.save != 1)
	{
		mlx_get_screen_size(m->mlx.mlx, &x, &y);
		m->scene.res_x = (m->scene.res_x > x) ? x : m->scene.res_x;
		m->scene.res_y = (m->scene.res_y > y) ? y : m->scene.res_y;
	}
}

void			make_scene(t_minirt *minirt)
{
	t_img_list	*current;

	minirt->mlx.mlx = mlx_init();
	res_resize(minirt);
	create_images(minirt);
	generate_ray(minirt);
	current = minirt->list.i_head;
	if (minirt->scene.save == 1)
		write_bitmap(minirt, current->addr);
	else
	{
		minirt->mlx.win = mlx_new_window(minirt->mlx.mlx, minirt->scene.res_x,
			minirt->scene.res_y, "Scene Window");
		mlx_put_image_to_window(minirt->mlx.mlx, minirt->mlx.win,
			current->img, 0, 0);
		mlx_hook(minirt->mlx.win, 17, 0, close_button, minirt);
		mlx_key_hook(minirt->mlx.win, key_hook, minirt);
		mlx_loop(minirt->mlx.mlx);
	}
}
