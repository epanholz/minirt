/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 18:50:02 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/17 23:34:35 by pani_zino     ########   odam.nl         */
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
	INT,DOUBLE
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

typedef struct	s_bmp_file_header 
{
    unsigned char	bitmap_type;     // 2 bytes
    int             file_size;          // 4 bytes
    short           reserved1;          // 2 bytes
    short           reserved2;          // 2 bytes
    unsigned int    offset_bits;        // 4 bytes
}				t_bmp_file_header;

typedef	struct	s_bmp_info_header
{
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    unsigned int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
}				t_bmp_info_header;

typedef struct	s_bitmap
{
	t_bmp_file_header	file;
	t_bmp_info_header	info;
	void				*buff;
}				t_bitmap;


typedef	struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_ray{
        t_vec3 orig;
        t_vec3 dir;
}					t_ray;

typedef struct		s_color
{
	int			r;
	int			g;
	int			b;
}					t_color;

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
	t_color			color;
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

typedef	struct		s_matrix43
{
	t_vec3			row1;
	t_vec3			row2;
	t_vec3			row3;
	t_vec3			row4;
}					t_matrix43;

typedef struct		s_object_list
{
	int				index;
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

typedef struct		s_light_list
{
	int				light_index;
	t_light			*light;
	void			*next;
}					t_light_list;

typedef struct		s_hit
{
	int				object;
	int				hit;
	t_vec3			surface_norm;
	t_vec3			hit_p;
	t_vec3			hit_p_new;
	double			t1;
	double			t2;
	t_color			color;
}					t_hit;

typedef	t_hit	(t_function)();

typedef struct		s_lookup
{
	int				index;
	t_function		*func;

}					t_lookup;

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
	int				save;
	double			res_x;
	double			res_y;
	double			a_light_ratio;
	t_color			a_color;
}					t_scene;

typedef struct  	s_var 
{
    void			*mlx;
    void			*win;
	void			*img;
	char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
	t_object_list	*o_head;
	t_camera_list	*c_head;
	t_img_list		*i_head;
	t_light_list	*l_head;
}              		t_var;

typedef	struct		s_minirt 
{
	t_scene			scene;
	t_var			var;
	t_utils			utils;
}					t_minirt;

void		ft_error(int mod);
void        my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color);
int			rgbt(int t, int r, int g, int b);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_(int trgb);
int			ft_strlen(char *s);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char 		*ft_strjoin(char *s1, char *s2);
char		*read_file(int fd, char *temp);
void		check_map(char *map, t_minirt *minirt);
void		check_arg(char *arg, int p, t_minirt *minirt);
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
void		remove_object_node(t_object_list **head, int type);
void 		delete_object_list(t_object_list **head);
void 		delete_cam_list(t_camera_list **head);
void		retrieve_cam(void	*scene_object);
void		retrieve_light(void	*scene_object);
void		retrieve_plane(void	*scene_object);
void		retrieve_sphere(void *scene_object);
void		retrieve_square(void *scene_object);
void		retrieve_cylinder(void *scene_object);
void		retrieve_triangle(void *scene_object);
t_sph		*return_sphere(t_minirt *minirt);
t_cam		*return_cam(t_minirt *minirt, int index);
t_light		*return_light(t_minirt *minirt, int index);
void		traverse_list(t_object_list **head);
t_vec3		vectorPlus(t_vec3 *v1, t_vec3 *v2);
double		vectorDot(t_vec3 *v1, t_vec3 *v2);
t_vec3		vectorSub(t_vec3 *v1, t_vec3 *v2);
t_vec3		vec_normalize(t_vec3 *vec3);
t_vec3 		vec_x_d(t_vec3 *v, double x);
t_vec3		crossProduct(t_vec3 *v1, t_vec3 *v2);
t_vec3  	vec3(double x, double y, double z);
double		vec_distance(t_vec3 *v1, t_vec3 *v2);
double		vec3_pow(t_vec3 *v);
int			close_key(int keycode, t_minirt *minirt);
int			close_button(void);
void		make_cam_head(t_camera_list **head);
void		add_camera(t_camera_list **head, t_cam *cam);
void		make_img_head(t_img_list **head);
void		add_img(t_img_list **head, void	*image, char *address);
void		make_light_head(t_light_list **head);
void		add_light(t_light_list **head, t_light *light);
void		traverse_cam_list(t_camera_list **head);
void		traverse_light_list(t_light_list **head);
void		traverse_img_list(t_img_list **head);
void		make_scene(t_minirt *minirt);
t_hit		intersect_sphere(t_ray *ray, t_sph *sphere);
t_hit		intersect_triangle(t_ray *ray, t_tri *triangle);
t_hit		intersect_plane(t_ray *ray, t_pla *plane);
t_hit		intersect_square(t_ray *ray, t_squ *square);
t_vec3		setsquare(t_vec3 pos, t_vec3 norm_vec);
t_hit		find_hit(t_minirt *minirt, t_ray *ray);
void		find_hit_light(t_minirt *minirt, t_ray *ray, double l, t_hit *hit_p);
void		find_hit_light2(t_minirt *minirt, t_ray *ray, t_hit *hit_p);
void		calc_color(t_minirt *minirt, t_hit *hit);
t_color		apply_color(t_color c1, t_color c2, double	ratio);
void		generate_ray(t_minirt *minirt);
t_vec3		apply_matrix(t_matrix43 matrix, t_vec3	vec3);
t_vec3		setcam(t_vec3 from, t_vec3 to, t_vec3 norm_vec);
t_matrix43	lookat_matrix(t_vec3 from, t_vec3 to);
void		create_images(t_minirt *minirt);
int			change_image(int keycode, t_minirt *minirt);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
t_bitmap	*initialize_bitmap(int width, int heigth);
int			fill_bmp_buff(t_bitmap *bmp, t_minirt *minirt, char *img_addr);
int			write_bitmap_to_file(t_bitmap *bmp, t_minirt *minirt, char *img_addr);


#endif