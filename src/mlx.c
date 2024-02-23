/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:18:12 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/22 19:27:17 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	fill_background(void* param)
{
	t_game *game = (t_game *)param;
	mlx_image_t *image = game->texture->background;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height / 2; ++y)
		{
			uint32_t color = ft_pixel(
				game->texture->ceiling->red, // R
				game->texture->ceiling->green, // G
				game->texture->ceiling->blue, // B
				100  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
		for (uint32_t y = image->height / 2; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				game->texture->floor->red, // R
				game->texture->floor->green, // G
				game->texture->floor->blue, // B
				100  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		if (game->distance <= 0.010000)
			return;
		game->distance -= 0.05;
		game->distance_jos += 0.05;
		printf("W pressed distance: %f\n", game->distance);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		if (game->distance >= 0.65)
			return;
		game->distance += 0.05;
		game->distance_jos -= 0.05;
	}
}

void	camera(void *param)
{
	t_game *game = (t_game *)param;
	mlx_image_t *image = game->texture->camera;
	int	x = 1;
	int pixelsPerTime = 100;
	for (uint32_t i = 0; i < image->width; i += 100)
	{
		printf("game->distance: %f\n", game->distance);
		for (uint32_t y = (image->height / 2) * game->distance; y < (image->height / 2) * game->distance_jos; ++y)
		{
			for (int p = 0; p < pixelsPerTime; ++p) {
				uint32_t color = ft_pixel(
					255, // R
					255, // G
					255, // B
					200  // A
				);
				mlx_put_pixel(image, i + p, y, color);
			}
		}
		x++;
	}
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game->mlx)
	{
		printf("Error\nmlx_init failed\n");
		exit(1);
	}
	game->texture->background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(game->mlx, game->texture->background, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return;
	}
	game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(game->mlx, game->texture->camera, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return;
	}
	mlx_loop_hook(game->mlx, fill_background, game);
	mlx_loop_hook(game->mlx, camera, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}