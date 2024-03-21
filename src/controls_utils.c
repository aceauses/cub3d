/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:01:11 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/21 12:58:41 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_game *game)
{
	if (game->map[(int)(game->ray->posy + game->ray->diry * 0.1)]
		[(int)game->ray->posx] != '1')
		game->ray->posy += game->ray->diry * 0.1;
	if (game->map[(int)game->ray->posy]
		[(int)(game->ray->posx + game->ray->dirx * 0.1)] != '1')
		game->ray->posx += game->ray->dirx * 0.1;
}

void	move_backward(t_game *game)
{
	if (game->map[(int)(game->ray->posy - game->ray->diry * 0.1)]
	[(int)game->ray->posx] != '1')
		game->ray->posy -= game->ray->diry * 0.1;
	if (game->map[(int)game->ray->posy]
		[(int)(game->ray->posx - game->ray->dirx * 0.1)] != '1')
		game->ray->posx -= game->ray->dirx * 0.1;
}

void	move_left(t_game *game)
{
	if (game->map[(int)(game->ray->posy - game->ray->planey * 0.1)]
		[(int)game->ray->posx] != '1')
		game->ray->posy -= game->ray->planey * 0.1;
	if (game->map[(int)game->ray->posy]
		[(int)(game->ray->posx - game->ray->planex * 0.1)] != '1')
		game->ray->posx -= game->ray->planex * 0.1;
}

void	move_right(t_game *game)
{
	if (game->map[(int)(game->ray->posy + game->ray->planey * 0.1)]
		[(int)game->ray->posx] != '1')
		game->ray->posy += game->ray->planey * 0.1;
	if (game->map[(int)game->ray->posy]
		[(int)(game->ray->posx + game->ray->planex * 0.1)] != '1')
		game->ray->posx += game->ray->planex * 0.1;
}
