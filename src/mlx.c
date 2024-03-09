/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:18:12 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/09 17:53:22 by aceauses         ###   ########.fr       */
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
				150  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
		for (uint32_t y = image->height / 2; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				game->texture->floor->red, // R
				game->texture->floor->green, // G
				game->texture->floor->blue, // B
				150  // A
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
		// mlx_delete_image(game->mlx, game->texture->camera);
		// game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		// mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		if (game->distance <= 0.010000)
			return;
		printf("game->ray->distH: %f\n", game->ray->distH);
		game->distance -= 0.05;
		game->distance_jos += 0.05;
		printf("W pressed distance: %f\n", game->distance);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		// mlx_delete_image(game->mlx, game->texture->camera);
		// game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		// mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		if (game->distance >= 0.65)
			return;
		game->distance += 0.05;
		game->distance_jos -= 0.05;
	}
}

void put_pixels(mlx_image_t *image, int x, int drawStart, int drawEnd, size_t color)
{
	for (int y = drawStart; y < drawEnd; y++)
	{
		// int *convert = malloc(sizeof(int) * texturee->height);
		// for (int i = 0; i < texturee->height; i += 1)
		// {
			// int convert = ft_pixel(colors[y], colors[y + 1], colors[y + 2], colors[y + 3]);
		mlx_put_pixel(image, x, y, color);
	}
}

void	camera(void *param)
{
	t_game *game = (t_game *)param;
	game->texture->current_buffer = (game->texture->current_buffer + 1) % NUM_BUFFERS; // 2
	mlx_delete_image(game->mlx, game->texture->camera[game->texture->current_buffer]); // 2
	game->texture->camera[game->texture->current_buffer] = mlx_new_image(game->mlx, WIDTH, HEIGHT); // 2
	mlx_image_to_window(game->mlx, game->texture->camera[game->texture->current_buffer], 0, 0); // 2
	for (int x = 0; x < WIDTH; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		double rayDirX = game->ray->dirX + game->ray->planeX * cameraX;
		double rayDirY = game->ray->dirY + game->ray->planeY * cameraX;
		printf("rayDirX: %f, rayDirY: %f\n", rayDirX, rayDirY);
		//which box of the map we're in
		int mapX = (int)game->ray->posX;
		int mapY = (int)game->ray->posY;
		printf("mapX: %d, mapY: %d\n", mapX, mapY);
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0) // Another function
		{
			stepX = -1;
			sideDistX = (game->ray->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->ray->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->ray->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->ray->posY) * deltaDistY;
		}
		while (hit == 0) //DDA function
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map[mapY][mapX] == '1' && game->map[mapY][mapX] != '\0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// Correct for fish-eye effect
		perpWallDist *= cos(atan2(rayDirY, rayDirX) - atan2(game->ray->dirY, game->ray->dirX));
		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		size_t color = ft_pixel(255, 0, 0, 255);
			
		put_pixels(game->texture->camera[(game->texture->current_buffer + 1) % NUM_BUFFERS], x, drawStart, drawEnd, color);
	}
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game->mlx)
	{
		printf("Error\nmlx_init failed\n");
		return ;
	}
	game->texture->background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(game->mlx, game->texture->background, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return;
	}
	game->texture->camera[(game->texture->current_buffer + 1) % NUM_BUFFERS] = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->texture->camera[(game->texture->current_buffer + 2) % NUM_BUFFERS] = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->texture->camera[(game->texture->current_buffer + 1) % NUM_BUFFERS], 0, 0);
	mlx_image_to_window(game->mlx, game->texture->camera[(game->texture->current_buffer + 2) % NUM_BUFFERS], 0, 0);
	// DrawWalls(game);
	mlx_loop_hook(game->mlx, fill_background, game);
	mlx_loop_hook(game->mlx, &camera, game);
	mlx_loop_hook(game->mlx, &controls, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
