/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_tracer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 14:54:20 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/03 12:17:50 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct  s_var {
        void    *mlx;
        void    *win;
		void	*img;
		char    *addr;
    	int     bits_per_pixel;
    	int     line_length;
    	int     endian;
}               t_var;

typedef struct 	s_vector {
      float 		x,y,z;
}				t_vector;


typedef struct	s_sphere{
        t_vector 	pos;
        float		radius;
}				t_sphere; 

typedef struct	s_ray{
        t_vector start;
        t_vector dir;
}				t_ray;

/* Subtract two vectors and return the resulting vector */
t_vector vectorSub(t_vector *v1, t_vector *v2){
	t_vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return (result);
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDot(t_vector *v1, t_vector *v2)
{
        return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

bool intersectRaySphere(t_ray *ray, t_sphere *sphere)
{
	/* A = d.d, the vector dot product of the direction */
	float A = vectorDot(&ray->dir, &ray->dir); 
	
	/* We need a vector representing the distance between the start of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	t_vector dist = vectorSub(&ray->start, &sphere->pos);
	
	/* 2d.(p0 - c) */  
	float B = 2 * vectorDot(&ray->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C = vectorDot(&dist, &dist) - (sphere->radius * sphere->radius);
	
	/* Solving the discriminant */
	float discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	if(discr < 0)
		return false;
	else
		return true;
	//if true -> cast shadow ray
}

int		close_key(int keycode, t_var *var)
{
	if (keycode == 53)
	{
    	mlx_destroy_window(var->mlx, var->win);
		mlx_destroy_image(var->mlx, var->img);
		exit(0);
	}
	return (0);
}

int		close_button(t_var *var)
{
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_image(var->mlx, var->img);
	exit(0);
	return (0);
}

int		rgbt(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_var *var, int x, int y, int color)
{
    char    *dst;

    dst = var->addr + (y * var->line_length + x * (var->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
	
	/* Our ray and a sphere */
	t_sphere 	sphere;
	t_ray 		ray;
	t_var 		var;
	
	/* x, y for screen 'resolution' */
	int x,y;	

	/* Intersect ray/sphere or not */
	bool hit;

	/* Position the sphere */
	sphere.pos.x = 200;
	sphere.pos.y = 200;
	sphere.pos.z = 200;

	/* Sphere radius */
	sphere.radius = 50;

	/* Direction of the ray */
	//oriental vector
	ray.dir.x = 0;
	ray.dir.y = 0;
	ray.dir.z = 1;

	/* Start position of the ray, z coordinate */
	ray.start.z = 0;

	/* Iterate over every 'pixel' of our screen
	 * We use a 40x40 virtual ASCII screen for now
	 */

    var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, 500, 500, "teeest");
	mlx_key_hook(var.win, close_key, &var);
	mlx_hook(var.win, 17, 0L, close_button, &var);
	var.img = mlx_new_image(var.mlx, 500, 500);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length, &var.endian);
	for(y=0;y<500;y++){
		/* Set the y-coordinate of the start position of the ray */
		ray.start.y = y; 
		for(x=0;x<500;x++){
			/* Set the x-coordinate of the start position of the ray */
			ray.start.x = x;

			/* Check if the ray intersects with the shpere */
			hit = intersectRaySphere(&ray, &sphere);
			if(hit)
				my_mlx_pixel_put(&var, x, y, rgbt(0,255,182,193));
			else
				my_mlx_pixel_put(&var, x, y, rgbt(0,0,0,0));
		}

	}
	mlx_put_image_to_window(var.mlx, var.win, var.img, 0, 0);
	mlx_loop(var.mlx);
}