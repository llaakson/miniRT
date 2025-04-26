/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:13:57 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/26 11:22:34 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int ft_render(t_minirt *mlx)
{
	mlx->image_ptr = NULL;
	// Allocates memory for one image that is size of the entire screen
	if (!(mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT)))
	{
		ft_printf("Render error1\n");
		return(1);
	}
	//Puts image in the window at the correct coordinates (Important to not go out of bounds of the window)
	if(mlx_image_to_window(mlx->mlx_ptr, mlx->image_ptr,0,0) == -1)
	{
		ft_printf("Render error2\n");
		return (1);
	}
	//Paints every pixel in the image with random color
	return (0);
}
void key_input(void *param)
{

	mlx_t *mlx = param;
	//Closes the windows with escape
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int main(int argc, char **argv)
{
	t_minirt *data;

	if (argc != 2)
		error_exit("Wrong amount of arguments. Ex: ./miniRT file.rt");
	data = tracked_malloc(sizeof(t_minirt));
	if (!data)
		error_exit("Memory allocation failed");
	ft_bzero(data, sizeof(t_minirt));
	if (!(data->mlx_ptr = mlx_init(IMG_WIDTH, IMG_HEIGHT, "miniRT", true)))
		error_exit("?");
	ft_render(data);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1); //???
	setup_scene_description(argv[1], data);
	print_elements_of_rt_file(data);
	raytracer(data);
	//calls key function when key is pressed
	mlx_loop_hook(data->mlx_ptr, key_input, data->mlx_ptr);

	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
	tracked_free_all();
	return (0);
}
