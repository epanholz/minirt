/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_list_traverse_test.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/01 12:43:17 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/29 22:17:50 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"	

void		retrieve_cam(void	*scene_object)
{
	t_cam 			*cam;

	cam = scene_object;	
	printf("[CAM] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d\n",  cam->view_point.x, cam->view_point.y, cam->view_point.z, cam->norm_vec.x, cam->norm_vec.y, cam->norm_vec.z, cam->fov);
	
}

void		retrieve_light(void	*scene_object)
{
	t_light 			*light;

	light = scene_object;	
	printf("[LIGHT] %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", light->light_point.x, light->light_point.y, light->light_point.z, light->light_b, light->r, light->g, light->b);
}

void		retrieve_plane(void	*scene_object)
{
	t_pla 			*plane;

	plane = scene_object;	
	printf("[PLA] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", plane->view_point.x, plane->view_point.y, plane->view_point.z, plane->norm_vec.x, plane->norm_vec.y, plane->norm_vec.z, plane->r, plane->g, plane->b);
}

void		retrieve_sphere(void	*scene_object)
{
	t_sph 			*sphere;

	sphere = scene_object;	
	printf("[SPH] %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", sphere->sp_center.x, sphere->sp_center.y, sphere->sp_center.z, sphere->diameter, sphere->r, sphere->g, sphere->b);
}

void		retrieve_square(void	*scene_object)
{
	t_squ 			*square;

	square = scene_object;	
	printf("[SQU] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", square->sq_center.x, square->sq_center.y, square->sq_center.z, square->norm_vec.x, square->norm_vec.y, square->norm_vec.z, square->side, square->r, square->g, square->b);
}

void		retrieve_cylinder(void	*scene_object)
{
	t_cyl			*cylinder;

	cylinder = scene_object;	
	printf("[CYL] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", cylinder->view_point.x, cylinder->view_point.y, cylinder->view_point.z, cylinder->norm_vec.x , cylinder->norm_vec.y, cylinder->norm_vec.z, cylinder->diameter, cylinder->height,  cylinder->r, cylinder->g, cylinder->b);
}

void		retrieve_triangle(void	*scene_object)
{
	t_tri			*triangle;

	triangle = scene_object;	
	printf("[TRI] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d, %d, %d\n", triangle->p1.x, triangle->p1.y, triangle->p1.z, triangle->p2.x, triangle->p2.y, triangle->p2.z, triangle->p3.x, triangle->p3.y, triangle->p3.z, triangle->r, triangle->g, triangle->b); 
}

void		traverse_list(t_object_list **head)
{
	t_object_list	*current;

	current = *head;
	while (current)
	{
		if (current->object_type == CAM)
			retrieve_cam(current->scene_object);
		if (current->object_type == LIGHT)
			retrieve_light(current->scene_object);
		if (current->object_type == PLA)
			retrieve_plane(current->scene_object);
		if (current->object_type == SPH)
			retrieve_sphere(current->scene_object);
		if (current->object_type == SQU)
			retrieve_square(current->scene_object);
		if (current->object_type == CYL)
			retrieve_cylinder(current->scene_object);
		if (current->object_type == TRI)
			retrieve_triangle(current->scene_object);
		current = current->next;
	}
}

void		traverse_cam_list(t_camera_list **head)
{
	t_camera_list	*current;

	current = *head;
	while (current)
	{
	printf("[CAM %d] %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %d\n",  current->cam_index, current->cam->view_point.x, current->cam->view_point.y, current->cam->view_point.z, current->cam->norm_vec.x, current->cam->norm_vec.y, current->cam->norm_vec.z, current->cam->fov);
	current = current->next;
	}
}

void		traverse_img_list(t_img_list **head)
{
	t_img_list	*current;

	current = *head;
	while (current)
	{
	printf("[IMAGE %d] \n",  current->img_index);
	current = current->next;
	}
}

