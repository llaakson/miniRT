
#include "../include/miniRT.h"

void key_input(void *param)
{
	
	mlx_t *mlx = param;
	//Closes the windows with escape
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		ft_printf("Error\n");
		return (1);
	}

	//calls key function when key is pressed
	mlx_loop_hook(mlx, key_input, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (0);
}
