/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:18:12 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/14 21:56:48 by aceauses         ###   ########.fr       */
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


void put_pixels(t_game *game, int x, int drawStart, int drawEnd, int lineHeight, int which_side, int side, double wallX)
{
	// double texWidth = 64;
    // double texHeight = 64;
	double maxLineHeight = HEIGHT * 10; // Set a maximum line height limit

    // double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) / lineHeight; // Starting texture coordinate
	double texPos = (drawStart - HEIGHT / 2 + (lineHeight > maxLineHeight ? maxLineHeight / 2 : lineHeight / 2)) / (lineHeight > maxLineHeight ? maxLineHeight : lineHeight); // Starting texture coordinate

    for (int y = drawStart; y < drawEnd; y++)
    {
        double texY = texPos * 64; // Calculate texture Y coordinate
        // texPos += 1.0 / lineHeight; // Increment texture coordinate for next pixel
		texPos += 1.0 / (lineHeight > maxLineHeight ? maxLineHeight : lineHeight);
        int texX = 1;
        if (side == 0) // Left or right side wall
            texX = wallX * 64;
        else // Top or bottom side wall
            texX = wallX * 64;

        // Handle texture wrapping
        texX = (int)texX % (int)64;
        texY = (int)texY % (int)64;

        // Get the texture color
        int texIndex = (texY * 64 + texX) * 4;
		int texture_color = ft_pixel(
			game->texture->sprite[which_side]->pixels[texIndex + 0],
			game->texture->sprite[which_side]->pixels[texIndex + 1],
			game->texture->sprite[which_side]->pixels[texIndex + 2],
			255);
        mlx_put_pixel(game->texture->camera[(game->texture->current_buffer + 1) % NUM_BUFFERS], x, y, texture_color);
    }
}

void	init_ray(t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->deltaDistX = sqrt(1 + (ray->rayDirY * ray->rayDirY) / (ray->rayDirX * ray->rayDirX));
	ray->deltaDistY = sqrt(1 + (ray->rayDirX * ray->rayDirX) / (ray->rayDirY * ray->rayDirY));
}

void	calc_sidedist(t_ray *ray, int *mapX, int *mapY)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - *mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (*mapX + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - *mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (*mapY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

void	refresh_camera(t_game *game)
{
	game->texture->current_buffer = (game->texture->current_buffer + 1) % NUM_BUFFERS;
	mlx_delete_image(game->mlx, game->texture->camera[game->texture->current_buffer]);
	game->texture->camera[game->texture->current_buffer] = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->texture->camera[game->texture->current_buffer], 0, 0);
}

int	calculate_side(t_game *game, int side)
{
	int	which_side;

	which_side = 0;
	if (side == 0) // FOX X-AXIS
	{
		if (game->ray->stepX < 0) // WEST
			which_side = 3;
		else // EAST
			which_side = 1;
	}
	else // FOR Y-AXIS
	{
		if (game->ray->stepY < 0) // SOUTH
			which_side = 2;
		else // NORTH
			which_side = 0;
	}
	return (which_side);
}

int	dda(t_game *game, int *mapX, int *mapY, int *hit, int *side)
{
	while (*hit == 0) //DDA function
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (game->ray->sideDistX < game->ray->sideDistY)
			{
				game->ray->sideDistX += game->ray->deltaDistX;
				*mapX += game->ray->stepX;
				*side = 0;
			}
			else
			{
				game->ray->sideDistY += game->ray->deltaDistY;
				*mapY += game->ray->stepY;
				*side = 1;
			}
			if (game->map[*mapY][*mapX] == '1' && game->map[*mapY][*mapX] != '\0')
			{
				*hit = 1;
				return (calculate_side(game, *side));
			}
		}
	return (0);
}

void	camera(void *param)
{
	t_game *game = (t_game *)param;
	refresh_camera(game);
	for (int x = 0; x < WIDTH; x++)
	{
		init_ray(game->ray, x);
		int mapX = (int)game->ray->posX;
		int mapY = (int)game->ray->posY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		calc_sidedist(game->ray, &mapX, &mapY);
		int which_side = dda(game, &mapX, &mapY, &hit, &side);
		if (side == 0)
			game->ray->perpWallDist = (game->ray->sideDistX - game->ray->deltaDistX);
		else
			game->ray->perpWallDist = (game->ray->sideDistY - game->ray->deltaDistY);
		game->ray->perpWallDist *= cos(atan2(game->ray->rayDirY, game->ray->rayDirX) - atan2(game->ray->dirY, game->ray->dirX));
		int lineHeight = (int)(HEIGHT / game->ray->perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		double wallX; //where exactly the wall was hit
		if(side == 0)
			wallX = game->ray->posY + game->ray->perpWallDist * game->ray->rayDirY;
		else
			wallX = game->ray->posX + game->ray->perpWallDist * game->ray->rayDirX;
		wallX -= floor((wallX));
		put_pixels(game, x, drawStart, drawEnd, lineHeight, which_side, side, wallX);
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
