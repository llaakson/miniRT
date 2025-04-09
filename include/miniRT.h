
#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_minirt
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*image_ptr;
} t_minirt;

#endif
