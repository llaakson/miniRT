
#include "../include/miniRT.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int ft_put_pixel(t_minirt *mlx)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	x = 0;
	//looping throught the whole image and painting every image one by one
	while(y < HEIGHT)
	{
		while(x < WIDTH)
		{
			// Should we calculate here the color for each pixel and put it in the image 
			// or calculate the colors in array and the call the array here
			color = ft_pixel(
				y % 0xFF, // R
				y % 0xFF, // G
				x % 0xFF, // B
				y % 0xFF  // A
			);
			//paints single pixel in the image in the chosen coordinates
			mlx_put_pixel(mlx->image_ptr, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int ft_render(t_minirt *mlx)
{
	mlx->image_ptr = NULL;
	// Allocates memory for one image that is size of the entire screen
	if (!(mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT)))
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
	ft_put_pixel(mlx);
	return (0);
}
void key_input(void *param)
{
	
	mlx_t *mlx = param;
	//Closes the windows with escape
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int main(void)
{
	t_minirt mlx;

	if (!(mlx.mlx_ptr = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		ft_printf("Error\n");
		return (1);
	}
	//Creates the image and fills all of it's pixels of chosen color
	ft_render(&mlx);
	//calls key function when key is pressed
	mlx_loop_hook(mlx.mlx_ptr, key_input, mlx.mlx_ptr);

	mlx_loop(mlx.mlx_ptr);
	mlx_terminate(mlx.mlx_ptr);

	return (0);
}
