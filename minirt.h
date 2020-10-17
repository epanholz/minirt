/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/10 18:19:27 by epanholz      #+#    #+#                 */
/*   Updated: 2020/10/17 18:16:08 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>

typedef enum		e_type
{
	INT, DOUBLE
}					t_type;

typedef enum		e_error
{
	INVAL, MALLOC, READ, WRITE, OPEN,
	ARG, RT, INPUT
}					t_error;

typedef enum		e_objects
{
	PLA = 1, SPH, SQU, CYL, TRI
}					t_objects;

typedef struct		s_bmp_file
{
	unsigned char	bitmap_type;
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bmp_file;

typedef	struct		s_bmp_info
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bmp_info;

typedef struct		s_bitmap
{
	t_bmp_file	file;
	t_bmp_info	info;
	void		*buff;
}					t_bitmap;

typedef	struct		s_vec3
{
	double	x;
	double	y;
	double	z;
}					t_vec3;

typedef struct		s_ray_utils
{
	double	asp_rat;
	int		pixy;
	int		pixx;
	double	camy;
	double	camx;
}					t_ray_utils;

typedef struct		s_ray
{
	t_vec3		orig;
	t_vec3		dir;
	t_ray_utils	u;
}					t_ray;

typedef struct		s_color
{
	double	r;
	double	g;
	double	b;
}					t_color;

typedef	struct		s_cam
{
	t_vec3	view_point;
	t_vec3	norm_vec;
	int		fov;
}					t_cam;

typedef	struct		s_light
{
	t_vec3	light_point;
	double	light_b;
	t_color	color;
}					t_light;

typedef	struct		s_pla
{
	t_vec3	view_point;
	t_vec3	norm_vec;
	int		r;
	int		g;
	int		b;
}					t_pla;

typedef	struct		s_sph
{
	t_vec3	sp_center;
	double	diameter;
	int		r;
	int		g;
	int		b;
}					t_sph;

typedef	struct		s_squ
{
	t_vec3	sq_center;
	t_vec3	norm_vec;
	double	side;
	int		r;
	int		g;
	int		b;
}					t_squ;

typedef	struct		s_cyl
{
	t_vec3	center;
	t_vec3	norm_vec;
	double	diameter;
	double	height;
	int		r;
	int		g;
	int		b;
}					t_cyl;

typedef	struct		s_tri
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	int		r;
	int		g;
	int		b;
}					t_tri;

typedef	struct		s_matrix
{
	t_vec3	row1;
	t_vec3	row2;
	t_vec3	row3;
	t_vec3	row4;
}					t_matrix;

typedef struct		s_object_list
{
	int		object_type;
	void	*scene_object;
	void	*next;
}					t_object_list;

typedef struct		s_img_list
{
	int		img_index;
	void	*img;
	char	*addr;
	void	*next;
}					t_img_list;

typedef struct		s_camera_list
{
	int		cam_index;
	t_cam	*cam;
	void	*next;
}					t_camera_list;

typedef struct		s_light_list
{
	int		light_index;
	t_light	*light;
	void	*next;
}					t_light_list;

typedef struct		s_hit
{
	int		object;
	int		hit;
	t_vec3	surface_norm;
	t_vec3	hit_p;
	double	t1;
	double	t2;
	t_color	col;
}					t_hit;

typedef	t_hit		(t_function)();

typedef struct		s_lookup
{
	int			index;
	t_function	*func;
}					t_lookup;

typedef struct		s_utils
{
	int	i;
	int	sign;
}					t_utils;

typedef struct		s_cyl_utils
{
	double	dot1;
	double	dot2;
	double	dot3;
	double	dot4;
}					t_cyl_utils;

typedef struct		s_tri_utils
{
	t_vec3	norm_temp;
	t_vec3	a;
	t_vec3	b;
	t_vec3	n;
	t_vec3	edge0;
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	c0;
	t_vec3	c1;
	t_vec3	c2;
	t_vec3	temp;
	t_vec3	p;
	t_vec3	t0;
	t_vec3	t1;
	t_vec3	t2;
	double	t;
	double	d;
}					t_tri_utils;

typedef struct		s_squ_utils
{
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	v3;
	t_vec3	temp1;
	t_vec3	temp2;
	t_tri	t1;
	t_tri	t2;
	double	r;
}					t_squ_utils;

typedef struct		s_scene
{
	int		res;
	int		ambient_light;
	int		camera;
	int		save;
	double	res_x;
	double	res_y;
	double	alight_r;
	t_color	a_color;
}					t_scene;

typedef	struct		s_list
{
	t_object_list	*o_head;
	t_camera_list	*c_head;
	t_img_list		*i_head;
	t_light_list	*l_head;
}					t_list;

typedef struct		s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_mlx;

typedef	struct		s_minirt
{
	t_scene	scene;
	t_mlx	mlx;
	t_list	list;
	t_utils	utils;
}					t_minirt;

void				ft_error(int mod);
void				ft_delay(void);
void				my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
int					rgbt(int t, int r, int g, int b);
int					ft_strlen(char *s);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strjoin(char *s1, char *s2);
char				*read_file(int fd, char *temp);
void				check_arg(char *arg, int p, t_minirt *minirt);
void				check_scene(char *arg, t_minirt *minirt);
void				get_res(char *s, int p, t_minirt *m);
void				get_ambient_light(char *s, int p, t_minirt *m);
t_cam				*get_camera(char *s, int p, t_minirt *m);
t_light				*get_light(char *s, int p, t_minirt *m);
t_pla				*get_plane(char *s, int p, t_minirt *m);
t_sph				*get_sphere(char *s, int p, t_minirt *m);
t_squ				*get_square(char *s, int p, t_minirt *m);
t_cyl				*get_cylinder(char *s, int p, t_minirt *minirt);
t_tri				*get_triangle(char *s, int p, t_minirt *minirt);
double				ft_atod(char *s, t_minirt *m, int mod);
double				ft_atod_loop(char *s, t_minirt *m, int mod);
void				check_rgb(char *s, t_minirt *m);
void				check_xyz_point(char *s, t_minirt *m);
void				check_norm_vec(char *s, t_minirt *m);
void				check_camera(char *s, int p, t_minirt *m);
void				check_alight(char *s, int p, t_minirt *m);
void				check_light(char *s, int p, t_minirt *m);
void				check_plane(char *s, int p, t_minirt *m);
void				check_sphere(char *s, int p, t_minirt *m);
void				check_square(char *s, int p, t_minirt *m);
void				check_cylinder(char *s, int p, t_minirt *m);
void				check_triangle(char *s, int p, t_minirt *m);
void				make_obj_head(t_object_list **head);
void				add_object(t_object_list **head, int type, void *scene);
void				delete_object_list(t_object_list **head);
void				make_cam_head(t_camera_list **head);
void				add_cam(t_camera_list **head, t_cam *cam);
void				make_img_head(t_img_list **head);
void				add_img(t_img_list **head, void	*image, char *address);
void				delete_img_list(t_img_list **head);
void				make_light_head(t_light_list **head);
void				add_light(t_light_list **head, t_light *light);
void				delete_cam_list(t_camera_list **head);
void				delete_light_list(t_light_list **head);
t_cam				*return_cam(t_minirt *minirt, int index);
t_vec3				vec_plus(t_vec3 *v1, t_vec3 *v2);
double				vec_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3				vec_sub(t_vec3 *v1, t_vec3 *v2);
t_vec3				vec_normalize(t_vec3 *vec3);
t_vec3				vec_x_d(t_vec3 *v, double x);
t_vec3				cross_prod(t_vec3 *v1, t_vec3 *v2);
double				vec_pow(t_vec3 *v);
int					key_hook(int keycode, t_minirt *minirt);
int					close_button(t_minirt *minirt);
void				change_image(t_minirt *minirt);
void				make_scene(t_minirt *minirt);
t_hit				init_hit(void);
t_hit				intersect_sphere(t_ray *ray, t_sph *sphere);
t_hit				intersect_triangle(t_ray *ray, t_tri *triangle);
t_hit				intersect_plane(t_ray *ray, t_pla *plane);
t_hit				intersect_square(t_ray *ray, t_squ *square);
t_hit				intersect_cylinder(t_ray *ray, t_cyl *cyl);
t_hit				find_hit(t_minirt *minirt, t_ray *ray);
void				find_hit_light(t_minirt *minirt, t_ray *ray,
					double l, t_hit *hit_p);
void				calc_color(t_minirt *minirt, t_hit *hit);
t_vec3				apply_matrix(t_matrix matrix, t_vec3	vec3);
t_vec3				setcam(t_vec3 from, t_vec3 to, t_vec3 norm_vec);
t_matrix			lookat_matrix(t_vec3 from, t_vec3 to);
void				create_images(t_minirt *minirt);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				write_bitmap(t_minirt *minirt, char *img_addr);

#endif
