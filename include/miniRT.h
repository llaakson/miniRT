
#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include <math.h>

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

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
	t_xyz direction;
} t_ray;

typedef struct s_camera
{
	t_xyz coordinatesOfViewpoint;
	t_xyz normOrientVec; //camera forward
	int FOV;
	//added later
	t_xyz world_up;
	t_xyz right_view;
	float aspect_ratio;
	float FOV_scale;
} t_camera;

typedef struct s_ambientLight
{
	float ambientLightRatio;
	t_xyz RGB;
} t_ambientLight;

typedef struct s_lighting
{
	t_xyz coordinatesOfLightPoint;
	float lightBrightnessRatio;
	t_xyz RGB;
}t_lighting;

typedef struct s_sphere
{
	t_xyz sphereCenter;
	float diameter;
	t_xyz RGB;
	struct s_sphere *next;
	struct s_sphere *prev;
} t_sphere;

typedef struct s_plane
{
	t_xyz pointInPlane;
	t_xyz normNormalVec;
	t_xyz RGB;
	struct s_plane *next;
	struct s_plane *prev;
}t_plane;

typedef struct s_cylinder
{
	t_xyz cylinderCenter;
	t_xyz normVecOfAxis;
	float diameter;
	float height;
	t_xyz RGB;
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
	float rayClosestIntersect;
	t_xyz coorinates;
	t_xyz RGB;
	t_xyz surface_normal;
} t_intersection;

typedef struct s_minirt
{
	t_camera *camera;
	t_ambientLight *ambLight;
	t_lighting *light;
	t_object *objects;
	//mlx_t		*mlx_ptr;
	//mlx_image_t	*image_ptr;
} t_minirt;


//setup scene
int setup_scene_description(char *file, t_minirt *data);
int file_extension_is_rt(char *file);
void set_ambient_light(char *line, int line_i, t_minirt *data);
void set_camera(char *line, int line_i, t_minirt *data);
void set_light(char *line, int line_i, t_minirt *data);
char *get_next_element_info(char *line, int *line_i);
int no_extra_minus_in_str(char *str, int i);
void set_light_ratio(char *element_info, float *light_ratio);
void set_RGB(char *element_info, t_xyz *RGB);
void set_coordinates(char *element_info, t_xyz *coordinates);
void set_normalized_vector(char *element_info, t_xyz *vector);
void set_horizontal_field_of_view_in_degrees(char *element_info, int *FOV);
void set_object_sphere(char *line, int line_i, t_minirt *data);
void set_diameter_or_height(char *element_info, float *measurement);
void set_object_plane(char *line, int line_i, t_minirt *data);
void set_object_cylinder(char *line, int line_i, t_minirt *data);
t_sphere *add_new_sphere_node(t_minirt *data);
t_plane *add_new_plane_node(t_minirt *data);
t_cylinder *add_new_cylinder_node(t_minirt *data);

//error
void error_exit(char *error);
void free_2d_array(char ***arr);

//basic utils
int	is_whitespace(char c);
int ft_strcmp(char *s1, char *s2);
float ft_atof(char *str, float *result);

//tracked malloc
void* tracked_malloc(size_t size);
void tracked_free(void* ptr);
void tracked_free_all(void);
void track_pointer(void* ptr);

//vector math
t_xyz vec_add(t_xyz one, t_xyz two);
t_xyz vec_subtract(t_xyz one, t_xyz two);
t_xyz vec_scale(t_xyz vec, float scale);
float vec_dot(t_xyz one, t_xyz two);
t_xyz vec_cross(t_xyz one, t_xyz two);
float vec_length(t_xyz vec);
t_xyz vec_normalize(t_xyz vec);

//raytracing
void raytracer(t_minirt *data);

//intersection
t_intersection intersect(t_minirt *data, t_ray ray);
void loop_intersect_spheres(t_sphere *spheres, t_ray ray, t_intersection *intersection);
void loop_intersect_planes(t_plane *planes, t_ray ray, t_intersection *intersection);
float quadratic_equation(float a, float b, float c);
float intersect_plane(t_plane *plane, t_ray ray);



//DELETE!
void print_elements_of_rt_file(t_minirt *data);

#endif
