/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:52:50 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/20 18:11:22 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	calculate_texpos(t_game *game)
{
	return ((game->ray->drawStart - HEIGHT / 2 + game->ray->lineHeight / 2)
		/ game->ray->lineHeight);
}

int	calculate_tex_y(double texpos)
{
	int	result;

	result = (int)(texpos * 64) % 64;
	return (result);
}

int	calculate_tex_x(double wallX, int side)
{
	int	result;

	result = (int)(wallX * 64) % 64;
	(void)side;
	return (result);
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

int	calculate_tex_index(int texX, int texY)
{
	int	texindex;

	texX = clamp(texX, 0, 64 - 1);
	texY = clamp(texY, 0, 64 - 1);
	texindex = texY * 64 + texX;
	return (texindex * 4);
}

int	get_texture_color(t_game *game, int texindex)
{
	int	which_side;
	int	r;
	int	g;
	int	b;

	which_side = game->ray->which_side;
	r = game->texture->sprite[which_side]->pixels[texindex + 0];
	g = game->texture->sprite[which_side]->pixels[texindex + 1];
	b = game->texture->sprite[which_side]->pixels[texindex + 2];
	return (ft_pixel(r, g, b, 255));
}

void	init_ray(t_ray *ray, int x)
{
	ray->camerax = 2 * x / (double)WIDTH - 1;
	ray->raydirx = ray->dirX + ray->planeX * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	ray->deltadistx = sqrt(1 + (ray->raydiry * ray->raydiry) / (ray->raydirx
				* ray->raydirx));
	ray->deltadisty = sqrt(1 + (ray->raydirx * ray->raydirx) / (ray->raydiry
				* ray->raydiry));
	ray->hitted = 0;
}

void	put_pixels(t_game *game, int x, int side, double wallX)
{
	int		y;
	double	texpos;
	int		texture_color;

	y = game->ray->drawStart;
	texpos = calculate_texpos(game);
	while (y < game->ray->drawEnd)
	{
		texture_color = get_texture_color(game,
				calculate_tex_index(calculate_tex_x(wallX, side),
					calculate_tex_y(texpos)));
		mlx_put_pixel(game->texture->camera[(game->texture->current_buffer + 1)
			% NUM_BUFFERS], x, y, texture_color);
		y++;
		texpos += 1.0 / game->ray->lineHeight;
	}
}

void	calc_sidedist(t_ray *ray, int *mapX, int *mapY)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - *mapX) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (*mapX + 1.0 - ray->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - *mapY) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (*mapY + 1.0 - ray->posy) * ray->deltadisty;
	}
}

void	refresh_camera(t_game *game)
{
	game->texture->current_buffer = (game->texture->current_buffer + 1)
		% NUM_BUFFERS;
	mlx_delete_image(game->mlx,
		game->texture->camera[game->texture->current_buffer]);
	game->texture->camera[game->texture->current_buffer] = mlx_new_image(game->mlx,
			WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx,
		game->texture->camera[game->texture->current_buffer], 0, 0);
}
