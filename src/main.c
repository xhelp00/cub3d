#include "../include/so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define WIDTH 1280
#define HEIGHT 960

static mlx_image_t* img;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true)))
		return(EXIT_FAILURE);

	//img = mlx_new_image(mlx, 64, 64);
	mlx_texture_t *wall = mlx_load_png("./pics/redbrick.png");
	img = mlx_texture_to_image(mlx, wall);
	//memset(img->pixels, 255, img->width * img->height * sizeof(int));
	mlx_image_to_window(mlx, img, 0, 0);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}