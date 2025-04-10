
#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_xyz
{
	float x;
	float y;
	float z;
} t_xyz;

typedef struct s_camera
{
	t_xyz coordinatesOfViewpoint;
	t_xyz normOrientVec;
	int FOV;

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

//error
void error_exit(char *error, t_minirt **data);
void free_and_set_to_null(char **str);

//basic utils
int	is_whitespace(char c);
int ft_strcmp(char *s1, char *s2);

#endif
