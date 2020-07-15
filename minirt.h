/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 18:50:02 by epanholz      #+#    #+#                 */
/*   Updated: 2020/07/15 20:58:00 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
MY FILES
test_main.c 
read_file.c 
get_scene.c 
check_scene.c
check_scene_utils.c 
object_list.c 
*/

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>

typedef enum		e_type
{
	INT,FLOAT
}					t_type;

typedef enum		e_error
{
	INVAL, MALLOC, READ
}					t_error;

typedef enum		e_objects
{
	CAM = 1, LIGHT, PLA, SPH,
	SQU, CYL, TRI
}					t_objects;


typedef	struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct	s_ray{
        t_vec3 start;
        t_vec3 dir;
}				t_ray;

typedef struct  	s_var 
{
    void			*mlx;
    void			*win;
	void			*img;
	char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
}              		t_var;

typedef struct  	s_utils 
{
	int				i;
	int				sign;
}               	t_utils;

typedef struct 		s_scene 
{
	int				res;
	int				ambient_light;
	int				camera;
	int				res_x;
	int				res_y;
	double			l_ratio;
	int				l_r;
	int				l_b;
	int				l_g;
}					t_scene;

typedef	struct		s_cam
{
	t_vec3			view_point;
	t_vec3			norm_vec;
	int				fov;
}					t_cam;

typedef	struct		s_light
{
	t_vec3			light_point;
	double			light_b;
	int				r;
	int				b;
	int				g;
}					t_light;

typedef	struct		s_pla
{
	t_vec3			view_point;
	t_vec3			norm_vec;
	int				r;
	int				b;
	int				g;
}					t_pla;

typedef	struct		s_sph
{
	t_vec3			sp_center;
	double			diameter;
	int				r;
	int				b;
	int				g;
}					t_sph;

typedef	struct		s_squ
{
	t_vec3			sq_center;
	t_vec3			norm_vec;
	double			side;
	int				r;
	int				b;
	int				g;
}					t_squ;

typedef	struct		s_cyl
{
	t_vec3			view_point;
	t_vec3			norm_vec;
	double			diameter;
	double			height;
	int				r;
	int				b;
	int				g;
}					t_cyl;

typedef	struct		s_tri
{
	t_vec3			p1;
	t_vec3			p2;
	t_vec3			p3;
	int				r;
	int				b;
	int				g;
}					t_tri;

typedef	struct		s_minirt 
{
	t_scene			scene;
	t_var			var;
	t_utils			utils;
}					t_minirt;

typedef struct		s_object_list
{
	int				object_type;
	void			*scene_object;
	void			*next;
}					t_object_list;

typedef struct		s_img_list
{
	int				img_index;
	void			*img;
	char			*addr;
	void			*next;
}					t_img_list;	

typedef struct		s_camera_list
{
	int				cam_index;
	t_cam			*cam;
	void			*next;
}					t_camera_list;	

void		ft_error(int mod);
int			ft_strlen(char *s);
char 		*ft_memcpy(char *dst, const char *src, int len);
char 		*ft_strjoin(char *s1, char *s2);
char		*read_file(int fd, char *temp);
void		check_map(char *map, t_minirt *minirt);
void		check_arg(char *arg, int p, t_minirt *minirt, t_object_list **head);
void		check_cam(char *arg, int p, t_minirt *minirt, t_camera_list **cam_head);
double		ft_atod(char *s, t_minirt *m, int mod);
double		ft_atod_loop(char *s, t_minirt *m, int mod);
void		check_rgb(char *s, t_minirt *m);
void		check_xyz_point(char *s, t_minirt *m);
void		check_norm_vec(char *s, t_minirt *m);
void		check_camera(char *s, int p, t_minirt *m);
void		check_alight(char *s, int p, t_minirt *m);
void		check_light(char *s, int p, t_minirt *m);
void		check_plane(char *s, int p, t_minirt *m);
void		check_sphere(char *s, int p, t_minirt *m);
void		check_square(char *s, int p, t_minirt *m);
void		check_cylinder(char *s, int p, t_minirt *m);
void		check_triangle(char *s, int p, t_minirt *m);
void		get_res(char *s, int p, t_minirt *m);
void		get_ambient_light(char *s, int p, t_minirt *m);
void		make_head(t_object_list **head);
void		add_object(t_object_list **head, int type, void *scene);
void		retrieve_cam(void	*scene_object);
void		retrieve_light(void	*scene_object);
void		retrieve_plane(void	*scene_object);
void		retrieve_sphere(void *scene_object);
void		retrieve_square(void *scene_object);
void		retrieve_cylinder(void *scene_object);
void		retrieve_triangle(void *scene_object);
void		traverse_list(t_object_list **head);
t_vec3		vectorPlus(t_vec3 *v1, t_vec3 *v2);
float		vectorDot(t_vec3 *v1, t_vec3 *v2);
t_vec3		vectorSub(t_vec3 *v1, t_vec3 *v2);
t_vec3		vec_normalize(t_vec3 *vec3, float N);
t_vec3  	vec3(int x, int y, int z);
int			close_key(int keycode, t_minirt *minirt);
int			close_button(void);
void		make_cam_head(t_camera_list **head);
void		add_camera(t_camera_list **head, t_cam *cam);
void		traverse_cam_list(t_camera_list **head);
void		make_scene(t_minirt *minirt);
void        my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
int			rgbt(int t, int r, int g, int b);

#endif