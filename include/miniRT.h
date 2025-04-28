
#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <math.h>
#include <float.h> //can include? for limits
#include <limits.h>

#define IMG_WIDTH 2560
#define IMG_HEIGHT 1440

typedef struct s_mallocs
{
    void* ptr;
    struct s_mallocs* next;
} t_mallocs;

typedef struct s_xyz
{
	float x;
	float y;
	float z;
} t_xyz;

typedef struct s_ray
{
	t_xyz origin;
	t_xyz dir;
} t_ray;

typedef struct s_camera
{
	t_xyz coordinates;
	t_xyz orientation; //camera forward
	int FOV;
	//added later
	t_xyz world_up;
	t_xyz right_view;
	float aspect_ratio;
	float FOV_scale;
} t_camera;

typedef struct s_ambientLight
{
	float ratio;
	t_xyz rgb;
} t_ambientLight;

typedef struct s_lighting
{
	t_xyz coordinates;
	float ratio;
	t_xyz rgb;
}t_lighting;

typedef struct s_sphere
{
	t_xyz center;
	float diameter;
	t_xyz rgb;
	struct s_sphere *next;
	struct s_sphere *prev;
} t_sphere;

typedef struct s_plane
{
	t_xyz point_in_plane;
	t_xyz orientation;
	t_xyz rgb;
	struct s_plane *next;
	struct s_plane *prev;
}t_plane;

typedef struct s_cylinder
{
	t_xyz center;
	t_xyz orientation;
	float diameter;
	float height;
	t_xyz rgb;
	//added
	int base_or_side_hit;
	//
	struct s_cylinder *next;
	struct s_cylinder *prev;
} t_cylinder;

typedef struct s_object
{
	t_sphere *spheres;
	t_plane *planes;
	t_cylinder *cylinders;
} t_object;

typedef struct s_intersection
{
	t_object object; //be aware of dangling ptrs
	float closest_intersect;
	t_xyz coordinates;
	t_xyz rgb;
	t_xyz surface_normal;
} t_hit;

typedef struct s_minirt
{
	t_camera *camera;
	t_ambientLight *amb_light;
	t_lighting *light;
	t_object *objects;
	mlx_t		*mlx_ptr;
	mlx_image_t	*image_ptr;
} t_minirt;


//setup scene
int setup_scene_description(char *file, t_minirt *data);
int file_extension_is_rt(char *file);
void	check_missing_elements(t_minirt *data);
int	line_has_valid_chars(char *line, int line_i);
void set_ambient_light(char *line, int line_i, t_minirt *data);
void set_camera(char *line, int line_i, t_minirt *data);
void set_light(char *line, int line_i, t_minirt *data);
char *get_next_element_info(char *line, int *line_i);
int no_extra_minus_in_str(char *str, int i);
void set_light_ratio(char *element_info, float *light_ratio);
void set_rgb(char *element_info, t_xyz *rgb);
void set_coordinates(char *element_info, t_xyz *coordinates);
void set_normalized_vector(char *element_info, t_xyz *vector);
void	set_fov(char *element_info, int *FOV);
void set_object_sphere(char *line, int line_i, t_minirt *data);
void set_diameter_or_height(char *element_info, float *measurement);
void set_object_plane(char *line, int line_i, t_minirt *data);
void set_object_cylinder(char *line, int line_i, t_minirt *data);
t_sphere *add_new_sphere_node(t_minirt *data);
t_plane *add_new_plane_node(t_minirt *data);
t_cylinder *add_new_cylinder_node(t_minirt *data);

//error
void error_exit(char *error);
void track_rt_file_fd(int fd);

//basic utils
int	is_whitespace(char c);
int ft_strcmp(char *s1, char *s2);
float ft_atof(char *str, float *result);
int	ft_atoi_overflow_checked(const char *str);

//tracked malloc
void* tracked_malloc(size_t size);
void tracked_free(void* ptr);
void tracked_free_all(void);
void track_pointer(void* ptr);
char	*tracked_realloc(char *str, size_t len);

//vector math
t_xyz vec_add(t_xyz one, t_xyz two);
t_xyz vec_sub(t_xyz one, t_xyz two);
t_xyz vec_scale(t_xyz vec, float scale);
float vec_dot(t_xyz one, t_xyz two);
t_xyz vec_cross(t_xyz one, t_xyz two);
float vec_length(t_xyz vec);
t_xyz vec_normalize(t_xyz vec);

//raytracing
void raytracer(t_minirt *data);

//intersection
t_hit intersect(t_minirt *data, t_ray ray);

float quadratic_equation(float a, float b, float c);
float intersect_plane(t_plane *plane, t_ray ray);
float	intersect_cylinder(t_cylinder *cyl, t_ray ray);
float	intersect_sphere(t_sphere *sphere, t_ray ray);
void set_intersection_data(t_hit *intersect, t_xyz rgb, float closest_hit, t_ray ray);
void set_cyl_intersect_surface_normal(t_cylinder *cyl, t_hit *intersect, t_ray ray);



//DELETE!
void print_elements_of_rt_file(t_minirt *data);

//Shadows and lightning
int calculate_light(t_minirt *data, t_hit intersection);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_xyz clamp_colors(t_xyz color);
t_xyz add_colors(t_xyz color1, t_xyz color2);
t_xyz multiply_color(t_xyz color1, t_xyz color2);
t_xyz multiply_color_intensity(t_xyz color, double multiplier);
void print_color(t_xyz color);
uint32_t mix_color(t_xyz color);
t_xyz divide_color(t_xyz color);

#endif
