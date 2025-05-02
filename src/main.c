/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:13:57 by aalbrech          #+#    #+#             */
/*   Updated: 2025/05/02 13:33:25 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void	init_mlx(t_minirt *mlx)
{
	mlx->image_ptr = NULL;
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	if (!(mlx->image_ptr))
		error_exit("Failed to create image");
	if (mlx_image_to_window(mlx->mlx_ptr, mlx->image_ptr, 0, 0) == -1)
		error_exit("Failed to put image to window");
}

void	key_input(void *ptr)
{
	mlx_t	*mlx;

	mlx = ptr;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	main(int argc, char **argv)
{
	t_minirt	*data;

	if (argc != 2)
		error_exit("Wrong amount of arguments. Ex: ./miniRT file.rt");
	store_pointer(0, NULL);
	data = tracked_malloc(sizeof(t_minirt));
	if (!data)
		error_exit("Memory allocation failed");
	ft_bzero(data, sizeof(t_minirt));
	setup_scene_description(argv[1], data);
	data->mlx_ptr = mlx_init(IMG_WIDTH, IMG_HEIGHT, "miniRT", true);
	if (!(data->mlx_ptr))
		error_exit("Failed to init mlx");
	store_pointer(1, data->mlx_ptr);
	init_mlx(data);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	raytracer(data);
	mlx_loop_hook(data->mlx_ptr, key_input, data->mlx_ptr);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
	tracked_free_all();
	return (0);
}
