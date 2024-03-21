/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:54:18 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/21 17:30:38 by rmitache         ###   ########.fr       */
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

void	calculate_wall_distances(t_game *game, int side)
{
	if (side == 0)
		game->ray->perpwalldist \
			= (game->ray->sidedistx - game->ray->deltadistx);
	else
		game->ray->perpwalldist \
			= (game->ray->sidedisty - game->ray->deltadisty);
	game->ray->perpwalldist *= cos(atan2(game->ray->raydiry \
		, game->ray->raydirx) - atan2(game->ray->diry, game->ray->dirx));
	if (game->ray->perpwalldist < 0.1000)
		game->ray->perpwalldist = 0.0900;
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
