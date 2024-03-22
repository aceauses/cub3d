/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:54:18 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/22 17:34:06 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	calculate_side(t_game *game, int side)
{
	int	which_side;

	which_side = 0;
	if (side == 0)
	{
		if (game->ray->stepx < 0)
			which_side = 3;
		else
			which_side = 2;
	}
	else
	{
		if (game->ray->stepy < 0)
			which_side = 1;
		else
			which_side = 0;
	}
	return (which_side);
}

int	dda(t_game *game, int *mapX, int *mapY, int *side)
{
	while (game->ray->hitted == 0)
	{
		if (game->ray->sidedistx < game->ray->sidedisty)
		{
			game->ray->sidedistx += game->ray->deltadistx;
			*mapX += game->ray->stepx;
			*side = 0;
		}
		else
		{
			game->ray->sidedisty += game->ray->deltadisty;
			*mapY += game->ray->stepy;
			*side = 1;
		}
		if (game->map[*mapY][*mapX] == '1' && game->map[*mapY][*mapX] != '\0')
		{
			game->ray->hitted = 1;
			return (calculate_side(game, *side));
		}
	}
	return (0);
}

void	calculate_wall_distances(t_game *game, int side, int mapx, int mapy)
{
	if (side == 0)
		game->ray->perpwalldist \
			= fabs((mapx - game->ray->posx + (1 - game->ray->stepx) / 2) \
				/ game->ray->raydirx) + 0.01;
	else
		game->ray->perpwalldist \
			= fabs((mapy - game->ray->posy + (1 - game->ray->stepy) / 2) \
				/ game->ray->raydiry) + 0.01;
	game->ray->perpwalldist *= cos(atan2(game->ray->raydiry \
		, game->ray->raydirx) - atan2(game->ray->diry, game->ray->dirx));
	game->ray->perpwalldist /= cos(atan2(game->ray->raydiry \
		, game->ray->raydirx) - atan2(game->ray->diry, game->ray->dirx));
	game->ray->lineheight = (double)(HEIGHT / game->ray->perpwalldist);
	game->ray->drawstart = -game->ray->lineheight / 2 + HEIGHT / 2;
	if (game->ray->drawstart < 0)
		game->ray->drawstart = 0;
	game->ray->drawend = game->ray->lineheight / 2 + HEIGHT / 2;
	if (game->ray->drawend >= HEIGHT)
		game->ray->drawend = HEIGHT - 1;
}

void	calc_wallx(t_game *game, int side, double *wallX)
{
	if (side == 0)
		*wallX = game->ray->posy + game->ray->perpwalldist * game->ray->raydiry;
	else
		*wallX = game->ray->posx + game->ray->perpwalldist * game->ray->raydirx;
	*wallX -= floor(*wallX);
}
