/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:52:50 by aceauses          #+#    #+#             */
/*   Updated: 2024/07/09 18:24:24 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	ray->raydirx = ray->dirx + ray->planex * ray->camerax + 0.001;
	ray->raydiry = ray->diry + ray->planey * ray->camerax + 0.001;
	ray->deltadistx = sqrt(1 + (ray->raydiry * ray->raydiry) / (ray->raydirx
				* ray->raydirx));
	ray->deltadisty = sqrt(1 + (ray->raydirx * ray->raydirx) / (ray->raydiry
				* ray->raydiry));
	ray->hitted = 0;
}

void	put_pixels(t_game *game, int x, double wallX)
{
	int		y;
	double	texpos;
	int		texture_color;

	y = game->ray->drawstart;
	mlx_set_instance_depth(game->texture->map_wall->instances, 1);
	texpos = (game->ray->drawstart - HEIGHT / 2 + game->ray->lineheight / 2)
		/ game->ray->lineheight;
	while (y < game->ray->drawend)
	{
		texpos += 1.0 / game->ray->lineheight;
		texture_color = get_texture_color(game,
				calculate_tex_index(calculate_tex(wallX, 'X'),
					calculate_tex(texpos, 'Y')));
		mlx_put_pixel(game->texture->camera[(game->texture->current_buffer + 1)
			% NUM_BUFFERS], x, y, texture_color);
		y++;
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
	mlx_image_t	**tmp;

	tmp = game->texture->camera;
	game->texture->current_buffer = (game->texture->current_buffer + 1)
		% NUM_BUFFERS;
	mlx_delete_image(game->mlx,
		tmp[game->texture->current_buffer]);
	tmp[game->texture->current_buffer] = mlx_new_image(game->mlx,
			WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx,
		game->texture->camera[game->texture->current_buffer], 0, 0);
}
